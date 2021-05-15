#pragma once
#include "Tools/Editor/EditorTool.h"
#include "System/DevTools/ThirdParty/imgui/imgui_internal.h"

//-------------------------------------------------------------------------

namespace KRG::Editor
{
    class KRG_TOOLS_EDITOR_API TabWell : public TEditorTool<EditorModel>
    {
    public:

        using TEditorTool::TEditorTool;

    private:

        virtual char const* const GetName() { return "Open Files"; }
        virtual void FrameStartUpdate( UpdateContext const& context, Render::ViewportManager& viewportManager ) override;
    };
}