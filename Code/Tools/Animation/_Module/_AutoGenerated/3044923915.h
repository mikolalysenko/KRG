#pragma once

//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

// HeaderID: 3044923915

#include "../API.h"
#include "System/TypeSystem/TypeRegistry.h"
#include "System/TypeSystem/ITypeHelper.h"
#include "System/Core/Serialization/Serialization.h"
#include "D:\Kruger\Code\Tools\Animation\Graph\AnimationGraphTools_Node.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Graph::ToolsNode
//-------------------------------------------------------------------------

namespace KRG
{
    template<class Archive>
    KRG_TOOLS_ANIMATION_API void serialize( Archive& archive, KRG::Animation::Graph::ToolsNode& type )
    {
        archive( cereal::base_class<KRG::GraphEditor::Flow::Node>( &type ), KRG_NVP( m_canvasPosition ), KRG_NVP( m_ID ) );
    }

    //-------------------------------------------------------------------------

    namespace TypeSystem
    {
        template<>
        void TypeInfo::RegisterProperties< TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::ToolsNode> >( IRegisteredType const* pDefaultTypeInstance )
        {
            PropertyInfo propertyInfo;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_canvasPosition" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::Float2" );
            propertyInfo.m_parentTypeID = 4247465487;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_ID" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::UUID" );
            propertyInfo.m_parentTypeID = 4247465487;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;
        }

        //-------------------------------------------------------------------------

        namespace TypeHelpers
        {
            template<>
            class KRG_TOOLS_ANIMATION_API TTypeHelper<KRG::Animation::Graph::ToolsNode> final : public ITypeHelper
            {
                static TTypeHelper<KRG::Animation::Graph::ToolsNode> StaticTypeHelper;

                static IRegisteredType const* s_pDefaultTypeInstancePtr;

            public:

                virtual IRegisteredType const* GetDefaultTypeInstancePtr() const override { return s_pDefaultTypeInstancePtr; }

                static void RegisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    TypeSystem::TypeInfo typeInfo;
                    typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Graph::ToolsNode" );
                    typeInfo.m_size = sizeof( KRG::Animation::Graph::ToolsNode );
                    typeInfo.m_alignment = alignof( KRG::Animation::Graph::ToolsNode );
                    typeInfo.m_pTypeHelper = &StaticTypeHelper; 
                    typeInfo.m_metadata.SetFlag( ETypeInfoMetaData::Abstract );

                    // Parent Types 
                    //-------------------------------------------------------------------------

                    TypeSystem::TypeInfo const* pParentType = nullptr;

                    pParentType = KRG::GraphEditor::Flow::Node::s_pTypeInfo;
                    KRG_ASSERT( pParentType != nullptr );
                    typeInfo.m_parentTypes.push_back( pParentType );

                    // Register properties and type
                    //-------------------------------------------------------------------------

                    typeInfo.RegisterProperties< KRG::TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::ToolsNode> >( s_pDefaultTypeInstancePtr );
                    KRG::Animation::Graph::ToolsNode::s_pTypeInfo = typeRegistry.RegisterType( typeInfo );
                }

                static void UnregisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    auto const ID = TypeSystem::TypeID( "KRG::Animation::Graph::ToolsNode" );
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
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );

                }

                virtual void UnloadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );

                }

                virtual LoadingStatus GetResourceLoadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );
                    LoadingStatus status = LoadingStatus::Loaded;

                    return status;
                }

                virtual LoadingStatus GetResourceUnloadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );
                    LoadingStatus status = LoadingStatus::Unloading;

                    return LoadingStatus::Unloaded;
                }

                virtual ResourceTypeID GetExpectedResourceTypeForProperty( IRegisteredType* pType, uint32 propertyID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );
                    // We should never get here since we are asking for a resource type of an invalid property
                    KRG_UNREACHABLE_CODE();
                    return ResourceTypeID();
                }

                virtual Byte* GetArrayElementDataPtr( IRegisteredType* pType, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pType );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return nullptr;
                }

                virtual size_t GetArraySize( IRegisteredType const* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual size_t GetArrayElementSize( uint32 arrayID ) const override final
                {
                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual void ClearArray( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void AddArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void RemoveArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual bool AreAllPropertyValuesEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance ) const override final
                {
                    auto pTypeHelper = KRG::Animation::Graph::ToolsNode::s_pTypeInfo->m_pTypeHelper;
                    auto pType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( pOtherTypeInstance );

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 2454640797 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 4230898639 ) )
                    {
                       return false;
                    }

                    return true;
                }

                virtual bool IsPropertyValueEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance, uint32 propertyID, int32 arrayIdx = InvalidIndex ) const override final
                {
                    auto pType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( pOtherTypeInstance );

                    if ( propertyID == 2454640797 )
                    {
                        return pType->m_canvasPosition == pOtherType->m_canvasPosition;
                    }

                    if ( propertyID == 4230898639 )
                    {
                        return pType->m_ID == pOtherType->m_ID;
                    }

                    return false;
                }

                virtual void ResetToDefault( IRegisteredType* pTypeInstance, uint32 propertyID ) override final
                {
                    auto pDefaultType = reinterpret_cast<KRG::Animation::Graph::ToolsNode const*>( GetDefaultTypeInstancePtr() );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::ToolsNode*>( pTypeInstance );

                    if ( propertyID == 2454640797 )
                    {
                        pActualType->m_canvasPosition = pDefaultType->m_canvasPosition;
                        return;
                    }

                    if ( propertyID == 4230898639 )
                    {
                        pActualType->m_ID = pDefaultType->m_ID;
                        return;
                    }

                }

            };
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Graph::DataSlotNode::OverrideValue
//-------------------------------------------------------------------------

namespace KRG
{
    template<class Archive>
    KRG_TOOLS_ANIMATION_API void serialize( Archive& archive, KRG::Animation::Graph::DataSlotNode::OverrideValue& type )
    {
        archive( cereal::base_class<KRG::IRegisteredType>( &type ), KRG_NVP( m_variationID ), KRG_NVP( m_resourceID ) );
    }

    //-------------------------------------------------------------------------

    namespace TypeSystem
    {
        template<>
        void TypeInfo::RegisterProperties< TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::DataSlotNode::OverrideValue> >( IRegisteredType const* pDefaultTypeInstance )
        {
            KRG_ASSERT( pDefaultTypeInstance != nullptr );
            KRG::Animation::Graph::DataSlotNode::OverrideValue const* pActualDefaultTypeInstance = ( KRG::Animation::Graph::DataSlotNode::OverrideValue const* ) pDefaultTypeInstance;

            PropertyInfo propertyInfo;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_variationID" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::StringID" );
            propertyInfo.m_parentTypeID = 694334223;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = &pActualDefaultTypeInstance->m_variationID;
            propertyInfo.m_offset = offsetof( KRG::Animation::Graph::DataSlotNode::OverrideValue, m_variationID );
            propertyInfo.m_size = sizeof( KRG::StringID );
            propertyInfo.m_flags.Set( 0 );
            m_properties.emplace_back( propertyInfo );
            m_propertyMap.insert( TPair<StringID, int32>( propertyInfo.m_ID, int32( m_properties.size() ) - 1 ) );

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_resourceID" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::ResourceID" );
            propertyInfo.m_parentTypeID = 694334223;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = &pActualDefaultTypeInstance->m_resourceID;
            propertyInfo.m_offset = offsetof( KRG::Animation::Graph::DataSlotNode::OverrideValue, m_resourceID );
            propertyInfo.m_size = sizeof( KRG::ResourceID );
            propertyInfo.m_flags.Set( 0 );
            m_properties.emplace_back( propertyInfo );
            m_propertyMap.insert( TPair<StringID, int32>( propertyInfo.m_ID, int32( m_properties.size() ) - 1 ) );
        }

        //-------------------------------------------------------------------------

        namespace TypeHelpers
        {
            template<>
            class KRG_TOOLS_ANIMATION_API TTypeHelper<KRG::Animation::Graph::DataSlotNode::OverrideValue> final : public ITypeHelper
            {
                static TTypeHelper<KRG::Animation::Graph::DataSlotNode::OverrideValue> StaticTypeHelper;

                static IRegisteredType const* s_pDefaultTypeInstancePtr;

            public:

                virtual IRegisteredType const* GetDefaultTypeInstancePtr() const override { return s_pDefaultTypeInstancePtr; }

                static void RegisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    IRegisteredType*& pDefaultTypeInstance = const_cast<IRegisteredType*&>( s_pDefaultTypeInstancePtr );
                    pDefaultTypeInstance = (IRegisteredType*) KRG::Alloc( sizeof( KRG::Animation::Graph::DataSlotNode::OverrideValue ), alignof( KRG::Animation::Graph::DataSlotNode::OverrideValue ) );
                    new ( pDefaultTypeInstance ) KRG::Animation::Graph::DataSlotNode::OverrideValue;

                    TypeSystem::TypeInfo typeInfo;
                    typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Graph::DataSlotNode::OverrideValue" );
                    typeInfo.m_size = sizeof( KRG::Animation::Graph::DataSlotNode::OverrideValue );
                    typeInfo.m_alignment = alignof( KRG::Animation::Graph::DataSlotNode::OverrideValue );
                    typeInfo.m_pTypeHelper = &StaticTypeHelper; 

                    // Parent Types 
                    //-------------------------------------------------------------------------

                    TypeSystem::TypeInfo const* pParentType = nullptr;

                    pParentType = KRG::IRegisteredType::s_pTypeInfo;
                    KRG_ASSERT( pParentType != nullptr );
                    typeInfo.m_parentTypes.push_back( pParentType );

                    // Register properties and type
                    //-------------------------------------------------------------------------

                    typeInfo.RegisterProperties< KRG::TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::DataSlotNode::OverrideValue> >( s_pDefaultTypeInstancePtr );
                    KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo = typeRegistry.RegisterType( typeInfo );
                }

                static void UnregisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    auto const ID = TypeSystem::TypeID( "KRG::Animation::Graph::DataSlotNode::OverrideValue" );
                    typeRegistry.UnregisterType( ID );

                    IRegisteredType*& pDefaultTypeInstance = const_cast<IRegisteredType*&>( s_pDefaultTypeInstancePtr );
                    reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pDefaultTypeInstance )->~OverrideValue();
                    KRG::Free( pDefaultTypeInstance );
                }

                virtual IRegisteredType* CreateType() const override final
                {
                    return KRG::New<KRG::Animation::Graph::DataSlotNode::OverrideValue>();
                }

                virtual void CreateTypeInPlace( IRegisteredType* pAllocatedMemory ) const override final
                {
                    KRG_ASSERT( pAllocatedMemory != nullptr );
                    new( pAllocatedMemory ) KRG::Animation::Graph::DataSlotNode::OverrideValue();
                }

                virtual void LoadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );

                }

                virtual void UnloadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );

                }

                virtual LoadingStatus GetResourceLoadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );
                    LoadingStatus status = LoadingStatus::Loaded;

                    return status;
                }

                virtual LoadingStatus GetResourceUnloadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );
                    LoadingStatus status = LoadingStatus::Unloading;

                    return LoadingStatus::Unloaded;
                }

                virtual ResourceTypeID GetExpectedResourceTypeForProperty( IRegisteredType* pType, uint32 propertyID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );
                    // We should never get here since we are asking for a resource type of an invalid property
                    KRG_UNREACHABLE_CODE();
                    return ResourceTypeID();
                }

                virtual Byte* GetArrayElementDataPtr( IRegisteredType* pType, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pType );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return nullptr;
                }

                virtual size_t GetArraySize( IRegisteredType const* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual size_t GetArrayElementSize( uint32 arrayID ) const override final
                {
                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual void ClearArray( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void AddArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void RemoveArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pTypeInstance );

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual bool AreAllPropertyValuesEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance ) const override final
                {
                    auto pTypeHelper = KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper;
                    auto pType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( pOtherTypeInstance );

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 174645900 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 159853016 ) )
                    {
                       return false;
                    }

                    return true;
                }

                virtual bool IsPropertyValueEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance, uint32 propertyID, int32 arrayIdx = InvalidIndex ) const override final
                {
                    auto pType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( pOtherTypeInstance );

                    if ( propertyID == 174645900 )
                    {
                        return pType->m_variationID == pOtherType->m_variationID;
                    }

                    if ( propertyID == 159853016 )
                    {
                        return pType->m_resourceID == pOtherType->m_resourceID;
                    }

                    return false;
                }

                virtual void ResetToDefault( IRegisteredType* pTypeInstance, uint32 propertyID ) override final
                {
                    auto pDefaultType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue const*>( GetDefaultTypeInstancePtr() );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode::OverrideValue*>( pTypeInstance );

                    if ( propertyID == 174645900 )
                    {
                        pActualType->m_variationID = pDefaultType->m_variationID;
                        return;
                    }

                    if ( propertyID == 159853016 )
                    {
                        pActualType->m_resourceID = pDefaultType->m_resourceID;
                        return;
                    }

                }

            };
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Graph::DataSlotNode
//-------------------------------------------------------------------------

namespace KRG
{
    template<class Archive>
    KRG_TOOLS_ANIMATION_API void serialize( Archive& archive, KRG::Animation::Graph::DataSlotNode& type )
    {
        archive( cereal::base_class<KRG::Animation::Graph::ToolsNode>( &type ), KRG_NVP( m_canvasPosition ), KRG_NVP( m_ID ), KRG_NVP( m_defaultResourceID ), KRG_NVP( m_overrides ) );
    }

    //-------------------------------------------------------------------------

    namespace TypeSystem
    {
        template<>
        void TypeInfo::RegisterProperties< TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::DataSlotNode> >( IRegisteredType const* pDefaultTypeInstance )
        {
            PropertyInfo propertyInfo;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_canvasPosition" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::Float2" );
            propertyInfo.m_parentTypeID = 2600609933;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_ID" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::UUID" );
            propertyInfo.m_parentTypeID = 2600609933;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_defaultResourceID" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::ResourceID" );
            propertyInfo.m_parentTypeID = 2600609933;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;

            //-------------------------------------------------------------------------

            propertyInfo.m_ID = StringID( "m_overrides" );
            propertyInfo.m_typeID = TypeSystem::TypeID( "KRG::Animation::Graph::DataSlotNode::OverrideValue" );
            propertyInfo.m_parentTypeID = 2600609933;
            propertyInfo.m_templateArgumentTypeID = TypeSystem::TypeID( "" );
            propertyInfo.m_pDefaultValue = nullptr;
        }

        //-------------------------------------------------------------------------

        namespace TypeHelpers
        {
            template<>
            class KRG_TOOLS_ANIMATION_API TTypeHelper<KRG::Animation::Graph::DataSlotNode> final : public ITypeHelper
            {
                static TTypeHelper<KRG::Animation::Graph::DataSlotNode> StaticTypeHelper;

                static IRegisteredType const* s_pDefaultTypeInstancePtr;

            public:

                virtual IRegisteredType const* GetDefaultTypeInstancePtr() const override { return s_pDefaultTypeInstancePtr; }

                static void RegisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    TypeSystem::TypeInfo typeInfo;
                    typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Graph::DataSlotNode" );
                    typeInfo.m_size = sizeof( KRG::Animation::Graph::DataSlotNode );
                    typeInfo.m_alignment = alignof( KRG::Animation::Graph::DataSlotNode );
                    typeInfo.m_pTypeHelper = &StaticTypeHelper; 
                    typeInfo.m_metadata.SetFlag( ETypeInfoMetaData::Abstract );

                    // Parent Types 
                    //-------------------------------------------------------------------------

                    TypeSystem::TypeInfo const* pParentType = nullptr;

                    pParentType = KRG::Animation::Graph::ToolsNode::s_pTypeInfo;
                    KRG_ASSERT( pParentType != nullptr );
                    typeInfo.m_parentTypes.push_back( pParentType );

                    // Register properties and type
                    //-------------------------------------------------------------------------

                    typeInfo.RegisterProperties< KRG::TypeSystem::TypeHelpers::TTypeHelper<KRG::Animation::Graph::DataSlotNode> >( s_pDefaultTypeInstancePtr );
                    KRG::Animation::Graph::DataSlotNode::s_pTypeInfo = typeRegistry.RegisterType( typeInfo );
                }

                static void UnregisterType( TypeSystem::TypeRegistry& typeRegistry )
                {
                    auto const ID = TypeSystem::TypeID( "KRG::Animation::Graph::DataSlotNode" );
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
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );

                    for ( auto& propertyValue : pActualType->m_overrides )
                    {
                        KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->LoadResources( pResourceSystem, requesterID, &propertyValue );
                    }

                }

                virtual void UnloadResources( Resource::ResourceSystem* pResourceSystem, UUID const& requesterID, IRegisteredType* pType ) const override final
                {
                    KRG_ASSERT( pResourceSystem != nullptr );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );

                    for ( auto& propertyValue : pActualType->m_overrides )
                    {
                        KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->UnloadResources( pResourceSystem, requesterID, &propertyValue );
                    }

                }

                virtual LoadingStatus GetResourceLoadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );
                    LoadingStatus status = LoadingStatus::Loaded;

                    for ( auto& propertyValue : pActualType->m_overrides )
                    {
                        status = KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->GetResourceLoadingStatus( &propertyValue );
                        if ( status == LoadingStatus::Loading )
                        {
                            return LoadingStatus::Loading;
                        }
                    }

                    return status;
                }

                virtual LoadingStatus GetResourceUnloadingStatus( IRegisteredType* pType ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );
                    LoadingStatus status = LoadingStatus::Unloading;

                    for ( auto& propertyValue : pActualType->m_overrides )
                    {
                        status = KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->GetResourceUnloadingStatus( &propertyValue );
                        if ( status != LoadingStatus::Unloaded )
                        {
                            return LoadingStatus::Unloading;
                        }
                    }

                    return LoadingStatus::Unloaded;
                }

                virtual ResourceTypeID GetExpectedResourceTypeForProperty( IRegisteredType* pType, uint32 propertyID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );
                    // We should never get here since we are asking for a resource type of an invalid property
                    KRG_UNREACHABLE_CODE();
                    return ResourceTypeID();
                }

                virtual Byte* GetArrayElementDataPtr( IRegisteredType* pType, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pType );

                    if ( arrayID == 2183863778 )
                    {
                        if ( ( arrayIdx + 1 ) >= pActualType->m_overrides.size() )
                        {
                            pActualType->m_overrides.resize( arrayIdx + 1 );
                        }

                        return (Byte*) &pActualType->m_overrides[arrayIdx];
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return nullptr;
                }

                virtual size_t GetArraySize( IRegisteredType const* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( pTypeInstance );

                    if ( arrayID == 2183863778 )
                    {
                        return pActualType->m_overrides.size();
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual size_t GetArrayElementSize( uint32 arrayID ) const override final
                {
                    if ( arrayID == 2183863778 )
                    {
                        return sizeof( KRG::Animation::Graph::DataSlotNode::OverrideValue );
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                    return 0;
                }

                virtual void ClearArray( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pTypeInstance );

                    if ( arrayID == 2183863778 )
                    {
                        pActualType->m_overrides.clear();
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void AddArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pTypeInstance );

                    if ( arrayID == 2183863778 )
                    {
                        pActualType->m_overrides.emplace_back();
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual void RemoveArrayElement( IRegisteredType* pTypeInstance, uint32 arrayID, size_t arrayIdx ) const override final
                {
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pTypeInstance );

                    if ( arrayID == 2183863778 )
                    {
                        pActualType->m_overrides.erase( pActualType->m_overrides.begin() + arrayIdx );
                        return;
                    }

                    // We should never get here since we are asking for a ptr to an invalid property
                    KRG_UNREACHABLE_CODE();
                }

                virtual bool AreAllPropertyValuesEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance ) const override final
                {
                    auto pTypeHelper = KRG::Animation::Graph::DataSlotNode::s_pTypeInfo->m_pTypeHelper;
                    auto pType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( pOtherTypeInstance );

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 2454640797 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 4230898639 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 1592680383 ) )
                    {
                       return false;
                    }

                    if( !pTypeHelper->IsPropertyValueEqual( pType, pOtherType, 2183863778 ) )
                    {
                       return false;
                    }

                    return true;
                }

                virtual bool IsPropertyValueEqual( IRegisteredType const* pTypeInstance, IRegisteredType const* pOtherTypeInstance, uint32 propertyID, int32 arrayIdx = InvalidIndex ) const override final
                {
                    auto pType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( pTypeInstance );
                    auto pOtherType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( pOtherTypeInstance );

                    if ( propertyID == 2454640797 )
                    {
                        return pType->m_canvasPosition == pOtherType->m_canvasPosition;
                    }

                    if ( propertyID == 4230898639 )
                    {
                        return pType->m_ID == pOtherType->m_ID;
                    }

                    if ( propertyID == 1592680383 )
                    {
                        return pType->m_defaultResourceID == pOtherType->m_defaultResourceID;
                    }

                    if ( propertyID == 2183863778 )
                    {
                        // Compare array elements
                        if ( arrayIdx != InvalidIndex )
                        {
                            if ( arrayIdx >= pOtherType->m_overrides.size() )
                            {
                                return false;
                            }

                            return KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->AreAllPropertyValuesEqual( &pType->m_overrides[arrayIdx], &pOtherType->m_overrides[arrayIdx] );
                        }
                        else // Compare entire array contents
                        {
                            if ( pType->m_overrides.size() != pOtherType->m_overrides.size() )
                            {
                                return false;
                            }

                            for ( size_t i = 0; i < pType->m_overrides.size(); i++ )
                            {
                                if( !KRG::Animation::Graph::DataSlotNode::OverrideValue::s_pTypeInfo->m_pTypeHelper->AreAllPropertyValuesEqual( &pType->m_overrides[i], &pOtherType->m_overrides[i] ) )
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
                    auto pDefaultType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode const*>( GetDefaultTypeInstancePtr() );
                    auto pActualType = reinterpret_cast<KRG::Animation::Graph::DataSlotNode*>( pTypeInstance );

                    if ( propertyID == 2454640797 )
                    {
                        pActualType->m_canvasPosition = pDefaultType->m_canvasPosition;
                        return;
                    }

                    if ( propertyID == 4230898639 )
                    {
                        pActualType->m_ID = pDefaultType->m_ID;
                        return;
                    }

                    if ( propertyID == 1592680383 )
                    {
                        pActualType->m_defaultResourceID = pDefaultType->m_defaultResourceID;
                        return;
                    }

                    if ( propertyID == 2183863778 )
                    {
                        pActualType->m_overrides = pDefaultType->m_overrides;
                        return;
                    }

                }

            };
        }
    }
}
