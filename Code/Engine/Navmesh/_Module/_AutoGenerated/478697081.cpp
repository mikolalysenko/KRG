//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "D:\Kruger\Code\Engine\Navmesh\_Module\_AutoGenerated\478697081.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Navmesh::NavmeshComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Navmesh::NavmeshComponent::StaticTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            void const* TTypeHelper<KRG::Navmesh::NavmeshComponent>::DefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Navmesh::NavmeshComponent> TTypeHelper<KRG::Navmesh::NavmeshComponent>::StaticTypeHelper;
        }
    }

    TypeSystem::TypeInfo const* KRG::Navmesh::NavmeshComponent::GetTypeInfo() const
    {
        return KRG::Navmesh::NavmeshComponent::StaticTypeInfo;
    }

    void KRG::Navmesh::NavmeshComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Navmesh::NavmeshComponent::StaticTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::Navmesh::NavmeshComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Navmesh::NavmeshComponent::StaticTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::Navmesh::NavmeshComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::Navmesh::NavmeshComponent::StaticTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
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