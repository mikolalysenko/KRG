//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\3288576307.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::Render::Mobility
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_Render_Mobility::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::Render::Mobility" );
                typeInfo.m_size = sizeof( KRG::Render::Mobility );
                typeInfo.m_alignment = alignof( KRG::Render::Mobility );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::Render::Mobility" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int32;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Dynamic" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Static" ), 0 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_Render_Mobility::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::Render::Mobility" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Render::StaticMeshComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Render::StaticMeshComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Render::StaticMeshComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Render::StaticMeshComponent> TTypeHelper<KRG::Render::StaticMeshComponent>::StaticTypeHelper;
        }
    }

    void KRG::Render::StaticMeshComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Render::StaticMeshComponent::s_pTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::Render::StaticMeshComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::Render::StaticMeshComponent::s_pTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::Render::StaticMeshComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::Render::StaticMeshComponent::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
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
