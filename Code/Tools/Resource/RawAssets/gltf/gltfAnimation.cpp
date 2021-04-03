#ifdef _WIN32
#include "gltfAnimation.h"
#include "gltfSceneContext.h"

//-------------------------------------------------------------------------

namespace KRG
{
    namespace RawAssets
    {
        class gltfRawAnimation : public RawAnimation
        {
            friend class gltfAnimationFileReader;
        };

        //-------------------------------------------------------------------------

        class gltfAnimationFileReader
        {
            struct TransformData
            {
                Quaternion m_rotation;
                Vector     m_translation;
                Vector     m_scale;
            };

        public:

            static TUniquePtr<KRG::RawAssets::RawAnimation> ReadAnimation( FileSystem::Path const& sourceFilePath, RawSkeleton const& rawSkeleton, String const& animationName )
            {
                KRG_ASSERT( sourceFilePath.IsValid() && rawSkeleton.IsValid() );

                TUniquePtr<RawAnimation> pAnimation( KRG::New<RawAnimation>( rawSkeleton ) );
                gltfRawAnimation* pRawAnimation = (gltfRawAnimation*) pAnimation.get();

                gltf::gltfSceneContext sceneCtx( sourceFilePath );
                if ( sceneCtx.IsValid() )
                {
                    auto pSceneData = sceneCtx.GetSceneData();

                    if ( pSceneData->animations_count == 0 )
                    {
                        pRawAnimation->LogError( "Could not find any animations in the gltf scene", animationName.c_str() );
                        return pAnimation;
                    }

                    // Get animation node
                    //-------------------------------------------------------------------------

                    cgltf_animation* pAnimationNode = nullptr;

                    if ( animationName.empty() )
                    {
                        pAnimationNode = &pSceneData->animations[0];
                    }
                    else // Try to find the specified animation
                    {
                        for ( auto i = 0; i < pSceneData->animations_count; i++ )
                        {
                            if ( pSceneData->animations[i].name != nullptr && animationName == pSceneData->animations[i].name )
                            {
                                pAnimationNode = &pSceneData->animations[i];
                            }
                        }

                        if ( pAnimationNode == nullptr )
                        {
                            pRawAnimation->LogError( "Could not find requested animation (%s) in gltf scene", animationName.c_str() );
                            return pAnimation;
                        }
                    }

                    KRG_ASSERT( pAnimationNode != nullptr );

                    // Get animation details
                    //-------------------------------------------------------------------------

                    float animationDuration = -1.0f;
                    size_t numFrames = 0;
                    for ( auto s = 0; s < pAnimationNode->samplers_count; s++ )
                    {
                        cgltf_accessor const* pInputAccessor = pAnimationNode->samplers[s].input;
                        KRG_ASSERT( pInputAccessor->has_max );
                        animationDuration = Math::Max( pInputAccessor->max[0], animationDuration );
                        numFrames = Math::Max( pInputAccessor->count, numFrames );
                    }

                    pRawAnimation->m_start = 0.0f;
                    pRawAnimation->m_end = animationDuration;
                    pRawAnimation->m_numFrames = (uint32) numFrames;
                    pRawAnimation->m_samplingFrameRate = animationDuration / numFrames;

                    // Read animation transforms
                    //-------------------------------------------------------------------------

                    ReadAnimationData( sceneCtx, *pRawAnimation, pAnimationNode );
                }
                else
                {
                    pRawAnimation->LogError( "Failed to read gltf file: %s -> %s", sourceFilePath.c_str(), sceneCtx.GetErrorMessage().c_str() );
                }

                return pAnimation;
            }

            static void ReadAnimationData( gltf::gltfSceneContext const& ctx, gltfRawAnimation& rawAnimation, cgltf_animation const* pAnimation )
            {
                KRG_ASSERT( pAnimation != nullptr );

                // Create temporary transform storage
                size_t const numBones = rawAnimation.GetNumBones();
                TVector<TVector<TransformData>> trackData;
                trackData.resize( numBones );
                for ( auto& track : trackData )
                {
                    track.resize( rawAnimation.m_numFrames );
                }

                // Read raw transform data
                //-------------------------------------------------------------------------

                size_t const numFrames = rawAnimation.m_numFrames;
                for ( auto c = 0; c < pAnimation->channels_count; c++ )
                {
                    cgltf_animation_channel const& channel = pAnimation->channels[c];
                    
                    if ( channel.target_node->name == nullptr )
                    {
                        rawAnimation.LogError( "Invalid setup in gltf file, bones have no names" );
                        return;
                    }

                    int32 const boneIdx = rawAnimation.m_skeleton.GetBoneIndex( StringID( channel.target_node->name ) );
                    if ( boneIdx == InvalidIndex )
                    {
                        continue;
                    }

                    KRG_ASSERT( channel.sampler->output->count == numFrames );

                    switch ( channel.target_path )
                    {
                        case cgltf_animation_path_type_rotation:
                        {
                            KRG_ASSERT( channel.sampler->output->type == cgltf_type_vec4 );

                            for ( auto i = 0; i < numFrames; i++ )
                            {
                                Float4 rotation;
                                cgltf_accessor_read_float( channel.sampler->output, i, &rotation.m_x, 4 );
                                trackData[boneIdx][i].m_rotation = Quaternion( rotation );
                            }
                        }
                        break;

                        case cgltf_animation_path_type_translation:
                        {
                            KRG_ASSERT( channel.sampler->output->type == cgltf_type_vec3 );

                            for ( auto i = 0; i < numFrames; i++ )
                            {
                                Float3 translation;
                                cgltf_accessor_read_float( channel.sampler->output, i, &translation.m_x, 3 );
                                trackData[boneIdx][i].m_translation = translation;
                            }
                        }
                        break;

                        case cgltf_animation_path_type_scale:
                        {
                            KRG_ASSERT( channel.sampler->output->type == cgltf_type_vec3 );

                            for ( auto i = 0; i < numFrames; i++ )
                            {
                                Float3 scale;
                                cgltf_accessor_read_float( channel.sampler->output, i, &scale.m_x, 3 );
                                trackData[boneIdx][i].m_scale = scale;
                            }
                        }
                        break;
                    }
                }

                // Create matrices from raw gltf data
                //-------------------------------------------------------------------------

                rawAnimation.m_tracks.resize( rawAnimation.GetNumBones() );
                for ( auto boneIdx = 0u; boneIdx < numBones; boneIdx++ )
                {
                    rawAnimation.m_tracks[boneIdx].m_transforms.resize( rawAnimation.m_numFrames );
                    for ( auto f = 0u; f < rawAnimation.m_numFrames; f++ )
                    {
                        TransformData const& transformData = trackData[boneIdx][f];
                        rawAnimation.m_tracks[boneIdx].m_transforms[f] = Transform( transformData.m_rotation, transformData.m_translation, transformData.m_scale );

                        // Correct the up-axis for all root transform
                        if ( boneIdx == 0 )
                        {
                            rawAnimation.m_tracks[boneIdx].m_transforms[f] = ctx.ApplyUpAxisCorrection( rawAnimation.m_tracks[boneIdx].m_transforms[f] );
                        }
                    }
                }
            }
        };
    }

    //-------------------------------------------------------------------------

    namespace gltf
    {
        TUniquePtr<KRG::RawAssets::RawAnimation> ReadAnimation( FileSystem::Path const& animationFilePath, RawAssets::RawSkeleton const& rawSkeleton, String const& takeName )
        {
            return RawAssets::gltfAnimationFileReader::ReadAnimation( animationFilePath, rawSkeleton, takeName );
        }
    }
}
#endif