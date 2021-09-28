#pragma once

#include "Tools/Render/_Module/API.h"
#include "ResourceCompiler_RenderMesh.h"

//-------------------------------------------------------------------------

namespace KRG::Render
{
    class SkeletalMesh;

    //-------------------------------------------------------------------------

    struct KRG_TOOLS_RENDER_API SkeletalMeshResourceDescriptor : public MeshResourceDescriptor
    {
        KRG_REGISTER_TYPE( SkeletalMeshResourceDescriptor );
    };

    //-------------------------------------------------------------------------

    class SkeletalMeshCompiler : public MeshCompiler
    {
        static const int32 s_version = 3;

    public:

        SkeletalMeshCompiler();
        virtual Resource::CompilationResult Compile( Resource::CompileContext const& ctx ) const override;

    private:

        void TransferSkeletalMeshData( RawAssets::RawMesh const& rawMesh, SkeletalMesh& mesh ) const;
    };
}