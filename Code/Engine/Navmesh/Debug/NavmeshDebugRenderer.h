#pragma once
#if KRG_ENABLE_NAVPOWER
#include "../_Module/API.h"
#include "Engine/Render/IRenderer.h"

//-------------------------------------------------------------------------

#if KRG_DEVELOPMENT_TOOLS
namespace KRG::Navmesh
{
    class BfxRenderer;

    //-------------------------------------------------------------------------

    class KRG_ENGINE_NAVMESH_API NavmeshDebugRenderer final : public Render::IRenderer
    {
    public:

        KRG_RENDERER_ID( NavmeshDebugRenderer, Render::RendererPriorityLevel::Debug );

    public:

        void Initialize();
        void Shutdown();
        void RenderWorld( EntityWorld* pWorld ) override final;

    private:

        BfxRenderer* m_pRenderer = nullptr;
    };
}
#else
// TEMP hack for reflector, since it doesnt have the correct PP defines
namespace KRG::Navmesh
{
    class NavmeshDebugRenderer {};
}
#endif
#endif