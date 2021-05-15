#pragma once

#include "API.h"
#include "Tools/Physics/ResourceCompilers/PhysicsMeshCompiler.h"
#include "Tools/Physics/ResourceCompilers/PhysicsMaterialDatabaseCompiler.h"
#include "Tools/Resource/Compilers/ResourceCompilerRegistry.h"

//-------------------------------------------------------------------------

namespace KRG::Physics
{
    class KRG_TOOLS_PHYSICS_API ToolsModule
    {
        KRG_REGISTER_MODULE;

    public:

        void RegisterCompilers( Resource::CompilerRegistry& compilerRegistry )
        {
            compilerRegistry.RegisterCompiler( &m_meshCompiler );
            compilerRegistry.RegisterCompiler( &m_databaseCompiler );
        }

        void UnregisterCompilers( Resource::CompilerRegistry& compilerRegistry )
        {
            compilerRegistry.UnregisterCompiler( &m_meshCompiler );
            compilerRegistry.UnregisterCompiler( &m_databaseCompiler );
        }

    private:

        PhysicsMeshCompiler                 m_meshCompiler;
        PhysicsMaterialDatabaseCompiler     m_databaseCompiler;
    };
}