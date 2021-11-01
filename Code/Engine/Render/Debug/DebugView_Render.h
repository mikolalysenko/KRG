#pragma once

#include "../_Module/API.h"
#include "Engine/Core/Entity/Debug/EntityWorldDebugView.h"
#include "Engine/Core/Imgui/Gizmo.h"

//-------------------------------------------------------------------------

#if KRG_DEVELOPMENT_TOOLS
namespace KRG::Render
{
    class WorldRendererSystem;
    class LightComponent;

    //-------------------------------------------------------------------------

    class KRG_ENGINE_RENDER_API RenderDebugView : public EntityWorldDebugView
    {
        KRG_REGISTER_TYPE( RenderDebugView );

    public:

        RenderDebugView();

    private:

        virtual void Initialize( SystemRegistry const& systemRegistry, EntityWorld const* pWorld ) override;
        virtual void Shutdown() override;
        virtual void DrawWindows( EntityUpdateContext const& context ) override;
        virtual void DrawOverlayElements( EntityUpdateContext const& context ) override;

        void DrawRenderMenu( EntityUpdateContext const& context );
        void DrawLightDebuggerWindow( EntityUpdateContext const& context);

        void DrawDirectionalLightOptions( EntityUpdateContext const& context );
        void DrawSpotLightOptions( EntityUpdateContext const& context );
        void DrawPointLightOptions( EntityUpdateContext const& context );

    private:

        WorldRendererSystem*            m_pWorldRendererSystem = nullptr;
        bool                            m_isLightDebuggerWindowOpen = false;
        LightComponent*                 m_pSelectedComponent = nullptr;
        Transform                       m_componentTransform;
        ImGuiX::Gizmo                   m_gizmo;
    };
}
#endif