#ifdef _WIN32
#include "Platform_Win32.h"
#include "System/Core/Memory/Memory.h"

#include <windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

//-------------------------------------------------------------------------

namespace KRG::Platform::Win32
{
    U32 GetProcessID( char const* processName )
    {
        U32 processID = 0;
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof( PROCESSENTRY32 );

        HANDLE snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

        if ( Process32First( snapshot, &entry ) )
        {
            while ( Process32Next( snapshot, &entry ) )
            {
                if ( strcmp( entry.szExeFile, processName ) == 0 )
                {
                    processID = entry.th32ProcessID;
                }
            }
        }

        CloseHandle( snapshot );
        return processID;
    }

    U32 StartProcess( char const* exePath, char const* cmdLine )
    {
        PROCESS_INFORMATION processInfo;
        memset( &processInfo, 0, sizeof( processInfo ) );

        STARTUPINFO startupInfo;
        memset( &startupInfo, 0, sizeof( startupInfo ) );
        startupInfo.hStdInput = GetStdHandle( STD_INPUT_HANDLE );
        startupInfo.hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
        startupInfo.hStdError = GetStdHandle( STD_ERROR_HANDLE );
        startupInfo.dwFlags = STARTF_USESTDHANDLES;
        startupInfo.cb = sizeof( startupInfo );

        char fullCmdLine[MAX_PATH];
        if ( cmdLine != nullptr )
        {
            Printf( fullCmdLine, MAX_PATH, "%s %s", exePath, cmdLine );
        }
        else
        {
            Printf( fullCmdLine, MAX_PATH, "%s", exePath );
        }

        if ( CreateProcess( nullptr, fullCmdLine, nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo, &processInfo ) )
        {
            return processInfo.dwProcessId;
        }

        return 0;
    }

    bool KillProcess( U32 processID )
    {
        KRG_ASSERT( processID != 0 );
        HANDLE pProcess = OpenProcess( PROCESS_TERMINATE, false, processID );
        if ( pProcess != nullptr )
        {
            return TerminateProcess( pProcess, 0 ) > 0;
        }

        return false;
    }

    String GetProcessPath( U32 processID )
    {
        KRG_ASSERT( processID != 0 );

        String returnPath;
        HANDLE pProcess = OpenProcess( PROCESS_QUERY_INFORMATION, false, processID );
        if ( pProcess != nullptr )
        {
            TCHAR currentProcessPath[MAX_PATH + 1];
            if ( GetModuleFileNameEx( pProcess, 0, currentProcessPath, MAX_PATH + 1 ) )
            {
                returnPath = currentProcessPath;
            }
            CloseHandle( pProcess );
        }

        return returnPath;
    }

    String GetCurrentModulePath()
    {
        String path;
        TCHAR exepath[MAX_PATH + 1];
        if ( GetModuleFileName( 0, exepath, MAX_PATH + 1 ) )
        {
            path = exepath;
        }

        return path;
    }

    String GetLastErrorMessage()
    {
        auto const errorID = GetLastError();

        LPSTR pMessageBuffer = nullptr;
        auto size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorID, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPSTR) &pMessageBuffer, 0, NULL );
        String message( pMessageBuffer, size );
        LocalFree( pMessageBuffer );
        return message;
    }

    String GetShortPath( String const& origPath )
    {
        TCHAR shortPath[MAX_PATH + 1];
        if ( GetShortPathName( origPath.c_str(), shortPath, MAX_PATH + 1 ) )
        {
            return String( shortPath );
        }

        return String();
    }
}
#endif