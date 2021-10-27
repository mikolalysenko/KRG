//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Physics\_Module\_AutoGenerated\2223379098.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Physics::PhysicsCapsuleComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Physics::PhysicsCapsuleComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Physics::PhysicsCapsuleComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Physics::PhysicsCapsuleComponent> TTypeHelper<KRG::Physics::PhysicsCapsuleComponent>::StaticTypeHelper;
        }
    }

    void KRG::Physics::PhysicsCapsuleComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Physics::PhysicsCapsuleComponent::s_pTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::Physics::PhysicsCapsuleComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Physics::PhysicsCapsuleComponent::s_pTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::Physics::PhysicsCapsuleComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::Physics::PhysicsCapsuleComponent::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
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
