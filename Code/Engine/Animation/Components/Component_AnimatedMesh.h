#pragma once

#include "Engine/Animation/_Module/API.h"
#include "Engine/Animation/AnimationSkeleton.h"
#include "Engine/Render/Components/Component_SkeletalMesh.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    class Pose;

    //-------------------------------------------------------------------------

    class KRG_ENGINE_ANIMATION_API AnimatedMeshComponent : public Render::SkeletalMeshComponent
    {
        KRG_REGISTER_ENTITY_COMPONENT( AnimatedMeshComponent );

    public:

        using Render::SkeletalMeshComponent::SkeletalMeshComponent;

        inline Skeleton const* GetSkeleton() const { return m_pSkeleton.GetPtr(); }
        void SetSkeleton( ResourceID skeletonResourceID );

        void SetPose( Pose const* pPose );

    private:

        virtual void Initialize() override final;
        virtual void Shutdown() override final;

        void GenerateBoneMap();

    private:

        KRG_EXPOSE TResourcePtr<Skeleton>               m_pSkeleton = nullptr;
        TVector<int32>                                  m_animToMeshBoneMap;
    };
}