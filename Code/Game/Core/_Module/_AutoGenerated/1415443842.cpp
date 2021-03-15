//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "D:\Kruger\Code\Game\Core\_Module\_AutoGenerated\1415443842.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::AnotherTestStruct
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::AnotherTestStruct::StaticTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            void const* TTypeHelper<KRG::AnotherTestStruct>::DefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::AnotherTestStruct> TTypeHelper<KRG::AnotherTestStruct>::StaticTypeHelper;
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::TestStruct
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::TestStruct::StaticTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            void const* TTypeHelper<KRG::TestStruct>::DefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::TestStruct> TTypeHelper<KRG::TestStruct>::StaticTypeHelper;
        }
    }
}

//-------------------------------------------------------------------------
// Enum Helper: KRG::SomeFlags
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_SomeFlags::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::SomeFlags" );
                typeInfo.m_size = sizeof( KRG::SomeFlags );
                typeInfo.m_alignment = alignof( KRG::SomeFlags );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::SomeFlags" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int32;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "c" ), 3 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "a" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "CoW" ), 5 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "B" ), 2 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "D" ), 4 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "A" ), 5 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_SomeFlags::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::SomeFlags" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::TestComponent::InternalStruct
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::TestComponent::InternalStruct::StaticTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            void const* TTypeHelper<KRG::TestComponent::InternalStruct>::DefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::TestComponent::InternalStruct> TTypeHelper<KRG::TestComponent::InternalStruct>::StaticTypeHelper;
        }
    }
}

//-------------------------------------------------------------------------
// Enum Helper: KRG::TestComponent::InternalEnum
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_TestComponent_InternalEnum::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::TestComponent::InternalEnum" );
                typeInfo.m_size = sizeof( KRG::TestComponent::InternalEnum );
                typeInfo.m_alignment = alignof( KRG::TestComponent::InternalEnum );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::TestComponent::InternalEnum" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Uint8;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Bar" ), 75 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "foo" ), 54 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_TestComponent_InternalEnum::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::TestComponent::InternalEnum" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// Enum Helper: KRG::TestComponent::Test::InternalEnum
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_TestComponent_Test_InternalEnum::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::TestComponent::Test::InternalEnum" );
                typeInfo.m_size = sizeof( KRG::TestComponent::Test::InternalEnum );
                typeInfo.m_alignment = alignof( KRG::TestComponent::Test::InternalEnum );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::TestComponent::Test::InternalEnum" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int16;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Bar" ), 0 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "foo" ), -1 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_TestComponent_Test_InternalEnum::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::TestComponent::Test::InternalEnum" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::TestComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::TestComponent::StaticTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            void const* TTypeHelper<KRG::TestComponent>::DefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::TestComponent> TTypeHelper<KRG::TestComponent>::StaticTypeHelper;
        }
    }

    TypeSystem::TypeInfo const* KRG::TestComponent::GetTypeInfo() const
    {
        return KRG::TestComponent::StaticTypeInfo;
    }

    void KRG::TestComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::TestComponent::StaticTypeInfo->m_pTypeHelper->LoadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Loading;
    }

    void KRG::TestComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        KRG::TestComponent::StaticTypeInfo->m_pTypeHelper->UnloadResources( context.m_pResourceSystem, requesterID, this );
        m_status = Status::Unloaded;
    }

    void KRG::TestComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            auto const resourceLoadingStatus = KRG::TestComponent::StaticTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( this );
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
