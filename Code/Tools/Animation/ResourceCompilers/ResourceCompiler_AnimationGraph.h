#pragma once

#include "Tools/Animation/_Module/API.h"
#include "Tools/Core/Resource/Compilers/ResourceCompiler.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    namespace Graph
    {
        class AnimationToolsGraph; 
        class ToolsGraphCompilationContext;
    }

    //-------------------------------------------------------------------------

    struct KRG_TOOLS_ANIMATION_API AnimationGraphVariationResourceDescriptor final : public Resource::ResourceDescriptor
    {
        KRG_REGISTER_TYPE( AnimationGraphVariationResourceDescriptor );

        KRG_EXPOSE DataPath                     m_graphDataPath;
        KRG_EXPOSE StringID                     m_variationID; // Optional: if not set, will use the default variation
    };

    //-------------------------------------------------------------------------

    class AnimationGraphCompiler final : public Resource::Compiler
    {
        static const int32 s_version = 0;

    public:

        AnimationGraphCompiler();
        virtual Resource::CompilationResult Compile( Resource::CompileContext const& ctx ) const final;

    private:

        Resource::CompilationResult CompileDefinition( Resource::CompileContext const& ctx ) const;
        Resource::CompilationResult CompileVariation( Resource::CompileContext const& ctx ) const;
        bool GenerateVirtualDataSetResource( Resource::CompileContext const& ctx, Graph::AnimationToolsGraph const& toolsGraph, Graph::ToolsGraphCompilationContext const& compilationContext, StringID const& variationID, DataPath const& dataSetPath ) const;
    };
}