//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Physics\_Module\_AutoGenerated\2728660727.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Physics::PhysicsMeshComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Physics::PhysicsMeshComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Physics::PhysicsMeshComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Physics::PhysicsMeshComponent> TTypeHelper<KRG::Physics::PhysicsMeshComponent>::StaticTypeHelper;
        }
    }

    void KRG::Physics::PhysicsMeshComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Physics::PhysicsMeshComponent::s_pTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::Physics::PhysicsMeshComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Physics::PhysicsMeshComponent::s_pTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::Physics::PhysicsMeshComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::Physics::PhysicsMeshComponent::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
            if ( resourceLoadingStatus == LoadingStatus::Loading )
            {
                return; // Something is still loading so early-out
            }

            if ( resourceLoadingStatus == LoadingStatus::Failed )
            {
                m_status = EntityComponent::Status::LoadingFailed;
            }
            else
            {
                m_status = EntityComponent::Status::Loaded;
            }
        }
    }
}