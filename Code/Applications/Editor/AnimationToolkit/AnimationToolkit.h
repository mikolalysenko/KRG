#pragma once

#include "AnimationToolkit_DataBrowser.h"
#include "Applications/Editor/Editor/EditorToolkit.h"
#include "Applications/Editor/Common/TabWell.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Tools
{
    class AnimationToolkit final : public TEditorToolkit<EditorModel>
    {
    public:

        ~AnimationToolkit();

    private:

        virtual char const* GetName() const override final { return "Kruger Animation Toolkit"; }

        virtual void SetUserFlags( uint64 flags ) override;
        virtual uint64 GetUserFlags() const override;

        virtual void Initialize( UpdateContext const& context, SettingsRegistry const& settingsRegistry ) override;
        virtual void Shutdown( UpdateContext const& context ) override;

    private:

        DataBrowser*                        m_pDataBrowser = nullptr;
        TabWell*                            m_pTabWell = nullptr;
    };
}