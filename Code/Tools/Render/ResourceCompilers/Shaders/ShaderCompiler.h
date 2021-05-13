#ifdef _WIN32
#pragma once

#include "Tools/Resource/Compilers/ResourceCompiler.h"
#include "System/Render/RenderShader.h"

//-------------------------------------------------------------------------

namespace KRG
{
    namespace Render
    {
        enum class ShaderType : uint8
        {
            KRG_REGISTER_ENUM

            Vertex = 0,
            Geometry,
            Pixel,
            Hull,
            Compute,
        };

        struct ShaderResourceDescriptor : public Resource::ResourceDescriptor
        {
            KRG_REGISTER_TYPE( ShaderResourceDescriptor );

            EXPOSE ShaderType           m_shaderType = ShaderType::Vertex;
            EXPOSE DataPath             m_shaderDataPath;
        };

        //-------------------------------------------------------------------------

        class ShaderCompiler : public Resource::Compiler
        {
            static const int32 VERSION = 1;

        public:

            ShaderCompiler();
            virtual Resource::CompilationResult Compile( Resource::CompileContext const& ctx ) const override;
        };
    }
}

#endif