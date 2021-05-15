#include "MaterialCompiler.h"
#include "Engine/Render/Material/RenderMaterial.h"
#include "System/Core/Serialization/BinaryArchive.h"
#include "System/Core/FileSystem/FileSystem.h"

//-------------------------------------------------------------------------

namespace KRG::Render
{
    bool MaterialResourceDescriptor::IsValid()
    {
        return m_diffuseTexture.GetResourceID().IsValid();
    }

    //-------------------------------------------------------------------------

    MaterialCompiler::MaterialCompiler()
        : Resource::Compiler( "MaterialCompiler", VERSION )
    {
        m_outputTypes.push_back( Material::GetStaticResourceTypeID() );
    }

    Resource::CompilationResult MaterialCompiler::Compile( Resource::CompileContext const& ctx ) const
    {
        MaterialResourceDescriptor resourceDescriptor;
        if ( !ctx.TryReadResourceDescriptor( resourceDescriptor ) )
        {
            return Error( "Failed to read resource descriptor from input file: %s", ctx.m_inputFilePath.c_str() );
        }

        if ( !resourceDescriptor.IsValid() )
        {
            return Error( "Incomplete or invalid material descriptor" );
        }

        Resource::ResourceHeader hdr( VERSION, Material::GetStaticResourceTypeID() );
        Material material;
        material.m_pDiffuseTexture = resourceDescriptor.m_diffuseTexture;
        hdr.m_installDependencies.push_back( material.m_pDiffuseTexture.GetResourceID() );

        // Serialize
        //-------------------------------------------------------------------------

        FileSystem::EnsurePathExists( ctx.m_outputFilePath );
        Serialization::BinaryFileArchive archive( Serialization::Mode::Write, ctx.m_outputFilePath );
        if ( archive.IsValid() )
        {
            archive << hdr << material;
            return CompilationSucceeded( ctx );
        }
        else
        {
            return CompilationFailed( ctx );
        }
    }
}