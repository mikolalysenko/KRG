#pragma once

#include "Tools/Core/Editors/ResourceEditorWorkspace.h"
#include "System/DevTools/ImguiX.h"
#include "Engine/Animation/AnimationSkeleton.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    class SkeletonResourceEditor : public TResourceEditorWorkspace<Skeleton>
    {
        static char const* const s_infoWindowName;
        static char const* const s_skeletonTreeWindowName;

        struct BoneInfo
        {
            inline void DestroyChildren()
            {
                for ( auto& pChild : m_children )
                {
                    pChild->DestroyChildren();
                    KRG::Delete( pChild );
                }

                m_children.clear();
            }

        public:

            int32                           m_boneIdx;
            TInlineVector<BoneInfo*, 5>     m_children;
            bool                            m_isExpanded = true;
        };

    public:

        using TResourceEditorWorkspace::TResourceEditorWorkspace;
        virtual ~SkeletonResourceEditor();

        virtual char const* GetWorkspaceName() const override { return "Skeleton"; }
        virtual void Activate( EntityWorld* pPreviewWorld ) override;
        virtual void Deactivate( EntityWorld* pPreviewWorld ) override;

        virtual void InitializeDockingLayout( ImGuiID dockspaceID ) const override;
        virtual void Draw( UpdateContext const& context, Render::ViewportManager& viewportManager, ImGuiWindowClass* pWindowClass ) override;

    private:

        void CreateSkeletonTree();
        void DestroySkeletonTree();
        ImRect RenderSkeletonTree( BoneInfo* pBone );

    private:

        BoneInfo*   m_pSkeletonTreeRoot = nullptr;
        StringID    m_selectedBoneID;
    };
}