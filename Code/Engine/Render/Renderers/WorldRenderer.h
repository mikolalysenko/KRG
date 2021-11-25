#pragma once

#include "Engine/Render/_Module/API.h"
#include "Engine/Core/Entity/EntityWorldSystem.h"
#include "Engine/Render/IRenderer.h"
#include "System/Render/RenderDevice.h"
#include "System/Core/Math/BVH/AABBTree.h"
#include "System/Core/Types/Event.h"
#include "System/Core/Systems/ISystem.h"

//-------------------------------------------------------------------------

namespace KRG::Render
{
    class DirectionalLightComponent;
    class GlobalEnvironmentMapComponent;
    class PointLightComponent;
    class StaticMeshComponent;
    class SkeletalMeshComponent;
    class SkeletalMesh;
    class StaticMesh;
    class Viewport;
    class Material;

    //-------------------------------------------------------------------------

    class KRG_ENGINE_RENDER_API WorldRenderer : public IRenderer
    {
    public:

        KRG_RENDERER_ID( WorldRenderer, Render::RendererPriorityLevel::Game );

    public:

        inline bool IsInitialized() const { return m_initialized; }
        bool Initialize( RenderDevice* pRenderDevice );
        void Shutdown();

        virtual void RenderWorld( RenderTarget const& target, Viewport const& viewport, EntityWorld* pWorld ) override final;

    private:
        enum
        {
            LIGHTING_ENABLE_SUN = (1 << 0),
            LIGHTING_ENABLE_SUN_SHADOW = (1 << 1),
            LIGHTING_ENABLE_SKYLIGHT = (1 << 2),
        };

        enum
        {
            MATERIAL_USE_ALBEDO_TEXTURE = (1 << 0),
            MATERIAL_USE_NORMAL_TEXTURE = (1 << 1),
            MATERIAL_USE_METALNESS_TEXTURE = (1 << 2),
            MATERIAL_USE_ROUGHNESS_TEXTURE = (1 << 3),
            MATERIAL_USE_AO_TEXTURE = (1 << 4),
        };

        enum
        {
            MAX_PUNCTUAL_LIGHTS = 16,
        };

        struct PunctualLight
        {
            Vector m_positionInvRadiusSqr;
            Vector m_dir;
            Vector m_color;
            Vector m_spotAngles;
        };

        struct LightData
        {
            Vector        m_SunDirIndirectIntensity;// TODO: refactor to Float3 and float
            Vector        m_SunColorRoughnessOneLevel;// TODO: refactor to Float3 and float
            Matrix        m_sunShadowMapMatrix;
            uint32        m_lightingFlags;
            uint32        m_numPunctualLights;
            PunctualLight m_punctualLights[MAX_PUNCTUAL_LIGHTS];
        };

        struct Transforms
        {
            Matrix m_worldTransform;
            Matrix m_normalTransform;
            Matrix m_viewprojTransform;
        };

        struct MaterialData
        {
            uint32   m_surfaceFlags;
            float    m_metalness;
            float    m_roughness;
            float    m_normalScaler;
            Vector   m_albedo;
        };

        struct RenderData //TODO: optimize - there should not be per frame updates
        {
            Transforms m_transforms;
            LightData m_lightData;
            CubemapTexture const* m_pSkyboxRadianceTexture;
            CubemapTexture const* m_pSkyboxTexture;
            TVector<StaticMeshComponent const*>& m_staticMeshComponents;
            TVector<SkeletalMeshComponent const*>& m_skeletalMeshComponents;
        };

        void RenderSunShadows( Viewport const& viewport, DirectionalLightComponent* pDirectionalLightComponent, const RenderData& data );
        void RenderStaticMeshes( Viewport const& viewport,  const RenderData& data );
        void RenderSkeletalMeshes( Viewport const& viewport, const RenderData& data );
        void RenderSkybox( Viewport const& viewport, const RenderData& data );

        void SetupRenderStates( Viewport const& viewport, const RenderData& data );

        static void SetupMaterial( RenderContext const& renderContext, PixelShader& pixelShader, const Material* material );

    private:

        bool                                                    m_initialized = false;

        // Render State
        VertexShader                                            m_vertexShaderSkybox;
        PixelShader                                             m_pixelShaderSkybox;
        RenderDevice*                                           m_pRenderDevice = nullptr;
        VertexShader                                            m_vertexShaderStatic;
        VertexShader                                            m_vertexShaderSkeletal;
        PixelShader                                             m_pixelShader;
        PixelShader                                             m_emptyPixelShader;
        BlendState                                              m_blendState;
        RasterizerState                                         m_rasterizerState;
        SamplerState                                            m_bilinearSampler;
        SamplerState                                            m_bilinearClampedSampler;
        SamplerState                                            m_shadowSampler;
        ShaderInputBindingHandle                                m_inputBindingStatic;
        ShaderInputBindingHandle                                m_inputBindingSkeletal;
        PipelineState                                           m_pipelineStateStatic;
        PipelineState                                           m_pipelineStateSkeletal;
        PipelineState                                           m_pipelineStateStaticShadow;
        PipelineState                                           m_pipelineStateSkeletalShadow;
        PipelineState                                           m_pipelineSkybox;
        ComputeShader                                           m_precomputeDFGComputeShader;
        Texture                                                 m_precomputedBRDF;
        Texture                                                 m_shadowMap;
        PipelineState                                           m_pipelinePrecomputeBRDF;
    };
}