//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Core\_Module\_AutoGenerated\3059223877.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::CameraComponent::ProjectionType
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_CameraComponent_ProjectionType::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::CameraComponent::ProjectionType" );
                typeInfo.m_size = sizeof( KRG::CameraComponent::ProjectionType );
                typeInfo.m_alignment = alignof( KRG::CameraComponent::ProjectionType );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::CameraComponent::ProjectionType" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int32;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Orthographic" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Perspective" ), 0 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_CameraComponent_ProjectionType::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::CameraComponent::ProjectionType" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::CameraComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::CameraComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::CameraComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::CameraComponent> TTypeHelper<KRG::CameraComponent>::StaticTypeHelper;
        }
    }

    void KRG::CameraComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::CameraComponent::s_pTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::CameraComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::CameraComponent::s_pTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::CameraComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::CameraComponent::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
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
