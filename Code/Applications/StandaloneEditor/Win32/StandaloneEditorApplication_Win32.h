#pragma once

#include "Engine.h"
#include "Win32/Application_Win32.h"

#include "_AutoGenerated/ToolsTypeRegistration.h"
#include "Tools/Core/Editors/StandaloneEditor.h"

//-------------------------------------------------------------------------

namespace KRG
{
    class StandaloneEditorEngine final : public Engine
    {
        friend class StandaloneEditorApplication;

    public:

        using Engine::Engine;

        virtual ~StandaloneEditorEngine();

        virtual void RegisterTypes() override
        {
            AutoGenerated::Tools::RegisterTypes( *m_pTypeRegistry );
        }

        virtual void UnregisterTypes() override
        {
            AutoGenerated::Tools::UnregisterTypes( *m_pTypeRegistry );
        }

        #if KRG_DEVELOPMENT_TOOLS
        virtual void CreateDevelopmentToolset() override { KRG_ASSERT( m_pActiveEditor != nullptr ); m_pDevelopmentToolset = m_pActiveEditor; }
        #endif

        // User flags
        inline void SetUserFlags( uint64 flags ) { m_pActiveEditor->SetUserFlags( flags ); }
        inline uint64 GetUserFlags() const { return m_pActiveEditor->GetUserFlags(); }

    private:

        StandaloneEditor*                         m_pActiveEditor = nullptr;
    };

    //-------------------------------------------------------------------------

    class StandaloneEditorApplication final : public Win32Application
    {

    public:

        StandaloneEditorApplication( HINSTANCE hInstance );

    private:

        virtual bool ReadSettings( int32 argc, char** argv ) override;
        virtual bool Initialize();
        virtual bool Shutdown();

        virtual LRESULT WndProcess( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

        virtual bool ApplicationLoop() override;

    private:

        StandaloneEditorEngine          m_editorEngine;
    };
}