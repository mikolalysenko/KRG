//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Animation\_Module\_AutoGenerated\1784585048.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::Animation::AnimationPlayerComponent::PlayMode
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_Animation_AnimationPlayerComponent_PlayMode::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::AnimationPlayerComponent::PlayMode" );
                typeInfo.m_size = sizeof( KRG::Animation::AnimationPlayerComponent::PlayMode );
                typeInfo.m_alignment = alignof( KRG::Animation::AnimationPlayerComponent::PlayMode );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::AnimationPlayerComponent::PlayMode" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int32;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "PlayOnce" ), 0 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Loop" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Posed" ), 2 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_Animation_AnimationPlayerComponent_PlayMode::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::Animation::AnimationPlayerComponent::PlayMode" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::AnimationPlayerComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Animation::AnimationPlayerComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Animation::AnimationPlayerComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Animation::AnimationPlayerComponent> TTypeHelper<KRG::Animation::AnimationPlayerComponent>::StaticTypeHelper;
        }
    }

    void KRG::Animation::AnimationPlayerComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Animation::AnimationPlayerComponent::s_pTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::Animation::AnimationPlayerComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Animation::AnimationPlayerComponent::s_pTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::Animation::AnimationPlayerComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::Animation::AnimationPlayerComponent::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
            if ( resourceLoadingStatus == LoadingStatus::Loading )
            {
                return; // Something is still loading so early-out
            }

            if ( resourceLoadingStatus == LoadingStatus::Failed )
            {
                m_status = EntityComponent::Status::LoadingFailed;
            }
            else
            {
                m_status = EntityComponent::Status::Loaded;
            }
        }
    }
}
