#pragma once

//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

// HeaderID: 2754915885

#include "../API.h"
#include "System/TypeSystem/TypeRegistry.h"
#include "System/TypeSystem/ITypeHelper.h"
#include "System/Core/Serialization/Serialization.h"
#include "E:\Git\KRG\Code\Engine\Render\Components\MeshComponent.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Render::MeshComponent
//-------------------------------------------------------------------------

namespace KRG
{
    template<class Archive>
    KRG_ENGINE_RENDER_API void serialize( Archive& archive, KRG::Render::MeshComponent& type )
    {
        archive( cereal::base_class<KRG::SpatialEntityComponent>( &type ), KRG_NVP( m_transform ), KRG_NVP( m_materialOverrides ) );
    }

    //-------------------------------------------------------------------------

    namespace TypeSystem
    {
        template<>
        void TypeInfo::RegisterProperties< TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::MeshComponent> >( IRegisteredType const* pDefaultTypeInstance )
        {
            PropertyInfo propertyInfo;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_transform" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::Transform" );
            propertyInfo.m_parentTypeID = 4234960285;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_materialOverrides" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::TResourcePtr" );
            propertyInfo.m_parentTypeID = 4234960285;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "KRG::Render::Material" );
            propertyInfo.m_pDefaultValue = nullptr;
        }

        //-------------------------------------------------------------------------

        namespace TypeHelpers
        {
            template<>
            class KRG_ENGINE_RENDER_API TTypeHelper<KRG::Render::MeshComponent> final : public ITypeHelper
            {
                static TTypeHelper<KRG::Render::MeshComponent> StaticTypeHelper;

                static IRegisteredType const* s_pDefaultTypeInstancePtr;

            public:

                virtual IRegisteredType const* GetDefaultTypeInstancePtr() const override { return s_pDefaultTypeInstancePtr; }

                static void RegisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    TypeSystem::TypeInfo typeInfo;
                    typeInfo.m_ID = TypeSystem::TypeID( "KRG::Render::MeshComponent" );
                    typeInfo.m_size = sizeof( KRG::Render::MeshComponent );
                    typeInfo.m_alignment = alignof( KRG::Render::MeshComponent );
                    typeInfo.m_pTypeHelper = &StaticTypeHelper; 
                    typeInfo.m_metadata.SetFlag( ETypeInfoMetaData::Abstract );

                    // Parent Types 
                    //-------------------------------------------------------------------------

                    TypeSystem::TypeInfo const* pParentType = nullptr;

                    pParentType = KRG::SpatialEntityComponent::s_pTypeInfo;
                    KRG_ASSERT( pParentType != nullptr );
                    typeInfo.m_parentTypes.push_back( pParentType );

                    // Register properties and type
                    //-------------------------------------------------------------------------

                    typeInfo.RegisterProperties< KRG::TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::MeshComponent> >( s_pDefaultTypeInstancePtr );
                    KRG::Render::MeshComponent::s_pTypeInfo = typeRegistry.RegisterType( typeInfo );
                }

                static void UnregisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    auto const ID = TypeSystem::TypeID( "KRG::Render::MeshComponent" );
                    typeRegistry.UnregisterType( ID );

                }

                virtual IRegisteredType* CreateType() const override final
                {
                    KRG_HALT(); // Error! Trying to instantiate an abstract type!
                    return nullptr;
                }

                virtual void CreateTypeInPlace( IRegisteredType* pAllocatedMemory ) const override final
                {
                    KRG_HALT(); // Error! Trying to instantiate an abstract type!
                }

                virtual void LoadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );

                    for ( auto& resourcePtr : pActualType->m_materialOverrides )
                    {
                        if ( resourcePtr.IsValid() )
                        {
                            pResourceSystem->LoadResource( resourcePtr, requesterID );
                        }
                    }

                }

                virtual void UnloadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );

                    for ( auto& resourcePtr : pActualType->m_materialOverrides )
                    {
                        if ( resourcePtr.IsValid() )
                        {
                            pResourceSystem->UnloadResource( resourcePtr, requesterID );
                        }
                    }

                }

                virtual LoadingStatus GetResourceLoadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );
                    LoadingStatus status = LoadingStatus::Loaded;

                    for ( auto const& resourcePtr : pActualType->m_materialOverrides )
                    {
                        if ( !resourcePtr.IsValid() || resourcePtr.HasLoadingFailed() )
                        {
                            status = LoadingStatus::Failed;
                        }
                        else if ( !resourcePtr.IsLoaded() )
                        {
                            return LoadingStatus::Loading;
                        }
                    }

                    return status;
                }

                virtual LoadingStatus GetResourceUnloadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );
                    LoadingStatus status = LoadingStatus::Unloading;

                    for ( auto const& resourcePtr : pActualType->m_materialOverrides )
                    {
                        KRG_ASSERT( !resourcePtr.IsLoading() );
                        if ( !resourcePtr.IsUnloaded() )
                        {
                            return LoadingStatus::Unloading;
                        }
                    }

                    return LoadingStatus::Unloaded;
                }

                virtual ResourceTypeID GetExpectedResourceTypeForProperty( IRegisteredType* pType, uint32 propertyID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );
                    if ( propertyID == 2164280863 )
                    {
                        return KRG::Render::Material::GetStaticResourceTypeID();
                    }

                    // We should never get here since we are asking for a resource type of an invalid property
                    KRG_UNREACHABLE_CODE();
                    return ResourceTypeID();
                }

                virtual Byte* GetArrayElementDataPtr( IRegisteredType* pType, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pType );

                    if ( arrayID == 2164280863 )
                    {
                        if ( ( arrayIdx + 1 ) >= pActualType->m_materialOverrides.size() )
                        {
                            pActualType->m_materialOverrides.resize( arrayIdx + 1 );
                        }

                        return (Byte*) &pActualType->m_materialOverrides[arrayIdx];
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return nullptr;
                }

                virtual size_t GetArraySize( IRegisteredType const* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent const*>( pTypeInstance );

                    if ( arrayID == 2164280863 )
                    {
                        return pActualType->m_materialOverrides.size();
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual size_t GetArrayElementSize( uint32 arrayID ) const override final
                {
                    if ( arrayID == 2164280863 )
                    {
                        return sizeof( KRG::TResourcePtr<KRG::Render::Material> );
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual void ClearArray( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pTypeInstance );

                    if ( arrayID == 2164280863 )
                    {
                        pActualType->m_materialOverrides.clear();
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void AddArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pTypeInstance );

                    if ( arrayID == 2164280863 )
                    {
                        pActualType->m_materialOverrides.emplace_back();
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void RemoveArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pTypeInstance );

                    if ( arrayID == 2164280863 )
                    {
                        pActualType->m_materialOverrides.erase( pActualType->m_materialOverrides.begin() + arrayIdx );
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual bool AreAllPropertyValuesEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance ) const override final
                {
                    auto pTypeHelper = KRG::Render::MeshComponent::s_pTypeInfo->m_pTypeHelper;
                    auto pType = reinterpret_cast<KRG::Render::MeshComponent const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Render::MeshComponent const*>( pOtherTypeInstance );

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 2436416701 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 2164280863 ) )
                    {
                       return false;
                    }

                    return true;
                }

                virtual bool IsPropertyValueEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance, uint32 propertyID, int32 arrayIdx = InvalidIndex ) const override final
                {
                    auto pType = reinterpret_cast<KRG::Render::MeshComponent const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Render::MeshComponent const*>( pOtherTypeInstance );

                    if ( propertyID == 2436416701 )
                    {
                        return pType->m_transform == pOtherType->m_transform;
                    }

                    if ( propertyID == 2164280863 )
                    {
                        // Compare array elements
                        if ( arrayIdx != InvalidIndex )
                        {
                            if ( arrayIdx >= pOtherType->m_materialOverrides.size() )
                            {
                                return false;
                            }

                            return pType->m_materialOverrides[arrayIdx] == pOtherType->m_materialOverrides[arrayIdx];
                        }
                        else // Compare entire array contents
                        {
                            if ( pType->m_materialOverrides.size() != pOtherType->m_materialOverrides.size() )
                            {
                                return false;
                            }

                            for ( size_t i = 0; i < pType->m_materialOverrides.size(); i++ )
                            {
                                if( pType->m_materialOverrides[i] != pOtherType->m_materialOverrides[i] )
                                {
                                    return false;
                                }
                            }

                            return true;
                        }
                    }

                    return false;
                }

                virtual void ResetToDefault( IRegisteredType* pTypeInstance, uint32 propertyID ) override final
                {
                    auto pDefaultType = reinterpret_cast<KRG::Render::MeshComponent const*>( GetDefaultTypeInstancePtr() );
                    auto pActualType = reinterpret_cast<KRG::Render::MeshComponent*>( pTypeInstance );

                    if ( propertyID == 2436416701 )
                    {
                        pActualType->m_transform = pDefaultType->m_transform;
                        return;
                    }

                    if ( propertyID == 2164280863 )
                    {
                        pActualType->m_materialOverrides = pDefaultType->m_materialOverrides;
                        return;
                    }

                }

            };
        }
    }
}