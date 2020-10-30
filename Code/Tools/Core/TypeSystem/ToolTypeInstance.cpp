#include "ToolTypeInstance.h"
#include "System/TypeSystem/EnumInfo.h"
#include "System/TypeSystem/TypeValueConverter.h"
#include "System/TypeSystem/TypeRegistry.h"

//-------------------------------------------------------------------------

namespace KRG::TypeSystem
{
    namespace
    {
        static S64 GetEnumValue( EnumInfo const* pEnumInfo, void const* pPropertyValue )
        {
            KRG_ASSERT( pEnumInfo != nullptr && pPropertyValue != nullptr );

            S64 value = 0;

            switch ( pEnumInfo->m_underlyingType )
            {
                case CoreTypes::U8:
                {
                    value = ( S64 ) * reinterpret_cast<U8 const*>( pPropertyValue );
                }
                break;

                case CoreTypes::S8:
                {
                    value = ( S64 ) * reinterpret_cast<S8 const*>( pPropertyValue );
                }
                break;

                case CoreTypes::U16:
                {
                    value = ( S64 ) * reinterpret_cast<U16 const*>( pPropertyValue );
                }
                break;

                case CoreTypes::S16:
                {
                    value = ( S64 ) * reinterpret_cast<S16 const*>( pPropertyValue );
                }
                break;

                case CoreTypes::U32:
                {
                    value = ( S64 ) * reinterpret_cast<U32 const*>( pPropertyValue );
                }
                break;

                case CoreTypes::S32:
                {
                    value = ( S64 ) * reinterpret_cast<S32 const*>( pPropertyValue );
                }
                break;

                default:
                KRG_HALT();
                break;
            }

            return value;
        }

        static String GetEnumStringValue( EnumInfo const* pEnumInfo, void const* pPropertyValue )
        {
            S64 const defaultValue = GetEnumValue( pEnumInfo, pPropertyValue );
            return pEnumInfo->GetConstantLabel( defaultValue ).c_str();
        }
    }

    //-------------------------------------------------------------------------
    // PROPERTY INSTANCE
    //-------------------------------------------------------------------------

    ToolPropertyInstance::ToolPropertyInstance( TypeRegistry const& typeRegistry, PropertyInfo const& propertyInfo )
        : m_propertyInfo( propertyInfo )
        , m_pTypeRegistry( &typeRegistry )
    {
        KRG_ASSERT( propertyInfo.IsValid() );

        //-------------------------------------------------------------------------

        m_friendlyName = m_propertyInfo.m_ID.c_str();
        m_friendlyName = StringUtils::RemoveAllOccurrencesInPlace( StringUtils::RemoveAllOccurrencesInPlace( m_friendlyName, "m_p" ), "m_" );
        m_friendlyName[0] = (char) toupper( m_friendlyName[0] );

        //-------------------------------------------------------------------------

        if ( IsArray() )
        {
            m_value = m_defaultValue = String().sprintf( "%d", m_propertyInfo.m_arraySize );
            CreateDefaultArrayElements();
        }
        else
        {
            if ( IsCoreType() )
            {
                TypeValueConverter::ConvertValueToString( m_propertyInfo.m_typeID, m_propertyInfo.m_pDefaultValue, m_defaultValue );
                m_value = m_defaultValue;
            }
            else if ( IsEnum() )
            {
                auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( GetTypeID() );
                KRG_ASSERT( pEnumInfo != nullptr );
                m_value = m_defaultValue = GetEnumStringValue( pEnumInfo, m_propertyInfo.m_pDefaultValue );
            }
            else // Complex type
            {
                m_pTypeInfo = typeRegistry.GetTypeInfo( m_propertyInfo.m_typeID );
                KRG_ASSERT( m_pTypeInfo != nullptr );

                // Create property instances
                for ( auto const& childPropertyInfo : m_pTypeInfo->m_properties )
                {
                    m_childProperties.emplace_back( ToolPropertyInstance( typeRegistry, childPropertyInfo.second ) );
                }
            }
        }
    }

    ToolPropertyInstance::ToolPropertyInstance( TypeRegistry const& typeRegistry, PropertyInfo const& propertyInfo, String const& stringValue )
        : ToolPropertyInstance( typeRegistry, propertyInfo )
    {
        KRG_ASSERT( ( IsCoreType() || IsEnum() ) && !stringValue.empty() );
        m_value = stringValue;
        m_defaultValue = stringValue;
    }

    ToolPropertyInstance::ToolPropertyInstance( TypeRegistry const& typeRegistry, TypeInfo const* pTypeInfo )
        : m_pTypeRegistry( &typeRegistry )
    {
        KRG_ASSERT( pTypeInfo != nullptr );
        m_pTypeInfo = pTypeInfo;

        // Create property instances
        for ( auto const& childPropertyInfo : m_pTypeInfo->m_properties )
        {
            m_childProperties.emplace_back( ToolPropertyInstance( typeRegistry, childPropertyInfo.second ) );
        }
    }

    //-------------------------------------------------------------------------

    ResourceTypeID ToolPropertyInstance::GetResourceTypeIDForResourceProperty() const
    {
        KRG_ASSERT( IsResourcePtr() || m_propertyInfo.m_typeID == CoreTypes::ResourceID );

        ResourceTypeID resourceTypeID;
        if ( m_propertyInfo.m_typeID == CoreTypes::TResourcePtr )
        {
            resourceTypeID = m_pTypeRegistry->GetResourceTypeIDForType( m_propertyInfo.m_templateArgumentTypeID );
        }

        return resourceTypeID;
    }

    //-------------------------------------------------------------------------

    ToolPropertyInstance* ToolPropertyInstance::GetProperty( PropertyPath const& path, bool allowDynamicArrayElementCreation )
    {
        KRG_ASSERT( IsValid() );
        KRG_ASSERT( !m_propertyInfo.IsArrayProperty() ); // Array properties do not have children with IDs

        ToolPropertyInstance* pFoundPropertyInstance = nullptr;

        //-------------------------------------------------------------------------

        auto const& pathElement = path.FirstElement();
        for ( auto& childProperty : m_childProperties )
        {
            if ( childProperty.GetID() == pathElement.m_propertyID )
            {
                pFoundPropertyInstance = &childProperty;
                break;
            }
        }

        if ( pFoundPropertyInstance == nullptr )
        {
            return nullptr;
        }

        //-------------------------------------------------------------------------

        if ( pathElement.IsArrayElement() && !pFoundPropertyInstance->IsArray() )
        {
            return nullptr;
        }

        //-------------------------------------------------------------------------

        if ( pathElement.IsArrayElement() )
        {
            // Handle the static array case
            if ( pFoundPropertyInstance->IsStaticArray() )
            {
                if ( pFoundPropertyInstance->IsValidArrayElementIndex( pathElement.m_arrayElementIdx ) )
                {
                    pFoundPropertyInstance = &pFoundPropertyInstance->GetArrayElement( pathElement.m_arrayElementIdx );
                }
                else
                {
                    return nullptr;
                }
            }
            else // Dynamic arrays
            {
                if ( pFoundPropertyInstance->IsValidArrayElementIndex( pathElement.m_arrayElementIdx ) )
                {
                    pFoundPropertyInstance = &pFoundPropertyInstance->GetArrayElement( pathElement.m_arrayElementIdx );
                }
                else
                {
                    if ( allowDynamicArrayElementCreation )
                    {
                        S32 const numElementsToAdd = pathElement.m_arrayElementIdx - pFoundPropertyInstance->GetNumArrayElements() + 1;
                        for ( auto i = 0; i < numElementsToAdd; i++ )
                        {
                            pFoundPropertyInstance->AddArrayElement();
                        }

                        pFoundPropertyInstance = &pFoundPropertyInstance->GetArrayElement( pathElement.m_arrayElementIdx );
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }

        //-------------------------------------------------------------------------

        if ( path.GetNumElements() > 1 )
        {
            PropertyPath const subPath = path.GetPathWithoutFirstElement();
            return pFoundPropertyInstance->GetProperty( subPath );
        }

        return pFoundPropertyInstance;
    }

    ToolPropertyInstance* ToolPropertyInstance::GetProperty( StringID propertyID )
    {
        KRG_ASSERT( !m_propertyInfo.IsArrayProperty() );

        for ( auto& childProperty : m_childProperties )
        {
            if ( childProperty.GetID() == propertyID )
            {
                return &childProperty;
            }
        }

        return nullptr;
    }

    //-------------------------------------------------------------------------

    TVector<char const*> ToolPropertyInstance::GetEnumValues() const
    {
        KRG_ASSERT( IsEnum() );

        auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( GetTypeID() );
        KRG_ASSERT( pEnumInfo != nullptr );

        TVector<char const*> outValues;
        for ( auto const& constant : pEnumInfo->m_constants )
        {
            outValues.emplace_back( constant.first.ToString() );
        }

        return outValues;
    }

    S64 ToolPropertyInstance::GetIntForEnumStringValue( char const* pString )
    {
        KRG_ASSERT( IsEnum() );

        auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( GetTypeID() );
        KRG_ASSERT( pEnumInfo != nullptr );
        return pEnumInfo->GetConstantValue( StringID( pString ) );
    }

    char const* ToolPropertyInstance::GetStringValueForEnumValue( S64 value )
    {
        KRG_ASSERT( IsEnum() );

        auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( GetTypeID() );
        KRG_ASSERT( pEnumInfo != nullptr );

        for ( auto const& constant : pEnumInfo->m_constants )
        {
            if ( constant.second == value )
            {
                return constant.first.c_str();
            }
        }

        KRG_UNREACHABLE_CODE();
        return nullptr;
    }

    bool ToolPropertyInstance::IsValidEnumStringValue( char const* pString )
    {
        KRG_ASSERT( IsEnum() );

        auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( GetTypeID() );
        KRG_ASSERT( pEnumInfo != nullptr );

        return pEnumInfo->IsValidValue( StringID( pString ) );
    }

    //-------------------------------------------------------------------------

    void ToolPropertyInstance::CreateDefaultArrayElements()
    {
        KRG_ASSERT( m_pTypeRegistry != nullptr );
        KRG_ASSERT( m_propertyInfo.IsValid() && m_propertyInfo.IsArrayProperty() );

        //-------------------------------------------------------------------------

        if ( m_propertyInfo.IsStaticArrayProperty() )
        {
            KRG_ASSERT( m_propertyInfo.m_arraySize > 0 );
        }

        //-------------------------------------------------------------------------

        for ( auto i = 0; i < m_propertyInfo.m_arraySize; i++ )
        {
            AddArrayElementInternal();
        }
    }

    void ToolPropertyInstance::AddArrayElementInternal()
    {
        KRG_ASSERT( IsValid() );
        KRG_ASSERT( IsArray() );

        ToolPropertyInstance* pAddedArrayElement = nullptr;
        S32 const newArrayElementIdx = (S32) m_childProperties.size();

        PropertyInfo arrayElementInfo = m_propertyInfo;
        arrayElementInfo.m_flags.ClearFlag( PropertyInfo::Flags::IsArray );
        arrayElementInfo.m_flags.ClearFlag( PropertyInfo::Flags::IsDynamicArray );
        arrayElementInfo.m_ID = StringID( String().sprintf( "m_%d", newArrayElementIdx ) );

        //-------------------------------------------------------------------------

        // If this is one of the defaults elements, set the correct default values
        if ( newArrayElementIdx < m_propertyInfo.m_arraySize )
        {
            if ( TypeSystem::IsCoreType( arrayElementInfo.m_typeID ) )
            {
                String arrayElementDefaultStringValue;
                TypeValueConverter::ConvertValueToString( m_propertyInfo.m_typeID, m_propertyInfo.GetArrayDefaultElementPtr( newArrayElementIdx ), arrayElementDefaultStringValue );
                pAddedArrayElement = &m_childProperties.emplace_back( ToolPropertyInstance( *m_pTypeRegistry, arrayElementInfo, arrayElementDefaultStringValue ) );
            }
            else if ( m_propertyInfo.IsEnumProperty() )
            {
                auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( arrayElementInfo.m_typeID );
                KRG_ASSERT( pEnumInfo != nullptr );

                String arrayElementDefaultStringValue = GetEnumStringValue( pEnumInfo, m_propertyInfo.GetArrayDefaultElementPtr( newArrayElementIdx ) );
                pAddedArrayElement = &m_childProperties.emplace_back( ToolPropertyInstance( *m_pTypeRegistry, arrayElementInfo, arrayElementDefaultStringValue ) );
            }
            else
            {
                pAddedArrayElement = &m_childProperties.emplace_back( ToolPropertyInstance( *m_pTypeRegistry, arrayElementInfo ) );
            }
        }
        else
        {
            pAddedArrayElement = &m_childProperties.emplace_back( ToolPropertyInstance( *m_pTypeRegistry, arrayElementInfo ) );
        }

        //-------------------------------------------------------------------------

        KRG_ASSERT( pAddedArrayElement != nullptr );
        pAddedArrayElement->m_arrayElementIdx = newArrayElementIdx;
    }

    void ToolPropertyInstance::SetNumArrayElements( S32 numElements )
    {
        KRG_ASSERT( IsValid() );
        KRG_ASSERT( IsDynamicArray() );
        KRG_ASSERT( numElements >= 0 );

        if ( numElements == 0 )
        {
            m_childProperties.clear();
        }

        else
        {
            S32 const currentNumElements = GetNumArrayElements();
            if ( numElements == currentNumElements )
            {
                return;
            }
            else if ( numElements > currentNumElements )
            {
                S32 const numElementsToAdd = numElements - currentNumElements;
                for ( auto i = 0; i < numElementsToAdd; i++ )
                {
                    AddArrayElement();
                }
            }
            else
            {
                S32 const numElementsToRemove = currentNumElements - numElements;
                for ( auto i = 0; i < numElementsToRemove; i++ )
                {
                    m_childProperties.pop_back();
                }
            }
        }
    }

    void ToolPropertyInstance::RemoveArrayElement( S32 elementIdx )
    {
        KRG_ASSERT( IsValid() );
        KRG_ASSERT( IsDynamicArray() );
        KRG_ASSERT( elementIdx >= 0 && elementIdx < m_childProperties.size() );
        m_childProperties.erase( m_childProperties.begin() + elementIdx );

        // Fix up array element IDs and indices
        for ( S32 i = elementIdx; i < (S32) m_childProperties.size(); i++ )
        {
            m_childProperties[i].m_propertyInfo.m_ID = StringID( String().sprintf( "m_%d", i ) );
            m_childProperties[i].m_arrayElementIdx = i;
        }
    }

    //-------------------------------------------------------------------------

    void ToolPropertyInstance::SetStringValue( String const& stringValue )
    {
        KRG_ASSERT( !IsStaticArray() && !IsStructure() );

        if ( IsDynamicArray() )
        {
            m_value = stringValue;
            S32 const numElements = StringUtils::StrToS32( stringValue );
            SetNumArrayElements( numElements );
        }
        else if ( IsEnum() )
        {
            IsValidEnumStringValue( stringValue.c_str() );
        }
        else
        {
            KRG_ASSERT( TypeValueConverter::IsValidStringValueForType( GetTypeID(), stringValue ) );
        }

        m_value = stringValue;
    }

    bool ToolPropertyInstance::IsDefaultValue() const
    {
        if ( m_value != m_defaultValue )
        {
            return false;
        }

        //-------------------------------------------------------------------------

        if ( IsDynamicArray() )
        {
            if ( GetNumArrayElements() != m_propertyInfo.m_arraySize )
            {
                return false;
            }

            // Manually check element vs defaults, since you could have removed and created a new entry which will have a different default that the one specified in c++
            for ( auto i = 0; i < m_propertyInfo.m_arraySize; i++ )
            {
                if ( TypeSystem::IsCoreType( m_propertyInfo.m_typeID ) )
                {
                    String defaultElementValue;
                    TypeValueConverter::ConvertValueToString( m_propertyInfo.m_typeID, m_propertyInfo.GetArrayDefaultElementPtr( i ), defaultElementValue );
                    if ( m_childProperties[i].GetStringValue() != defaultElementValue )
                    {
                        return false;
                    }
                }
                else if ( m_propertyInfo.IsEnumProperty() )
                {
                    auto const pEnumInfo = m_pTypeRegistry->GetEnumInfo( m_propertyInfo.m_typeID );
                    KRG_ASSERT( pEnumInfo != nullptr );

                    String defaultElementValue = GetEnumStringValue( pEnumInfo, m_propertyInfo.GetArrayDefaultElementPtr( i ) );
                    if ( m_childProperties[i].GetStringValue() != defaultElementValue )
                    {
                        return false;
                    }
                }
            }
        }

        //-------------------------------------------------------------------------

        for ( auto const& childProperty : m_childProperties )
        {
            if ( !childProperty.IsDefaultValue() )
            {
                return false;
            }
        }

        //-------------------------------------------------------------------------

        return true;
    }

    void ToolPropertyInstance::ResetToDefaultValue()
    {
        m_value = m_defaultValue;

        //-------------------------------------------------------------------------

        // If we are resetting a dynamic array property, destroy all child properties and recreate them from the defaults
        if ( IsDynamicArray() )
        {
            m_childProperties.clear();
            CreateDefaultArrayElements();
        }

        //-------------------------------------------------------------------------

        for ( auto& childProperty : m_childProperties )
        {
            childProperty.ResetToDefaultValue();
        }
    }

    //-------------------------------------------------------------------------
    // TYPE INSTANCE
    //-------------------------------------------------------------------------

    namespace
    {
        static void FlattenProperties( ToolPropertyInstance const& propertyInstance, PropertyPath const& currentPath, TVector<ToolPropertyInstanceDescriptor>& outProperties )
        {
            if ( propertyInstance.IsDefaultValue() )
            {
                return;
            }

            //-------------------------------------------------------------------------

            PropertyPath propertyPath = currentPath;
            if ( propertyInstance.IsArrayElement() )
            {
                propertyPath.ReplaceLastElement( propertyPath.GetLastElement().m_propertyID, propertyInstance.GetArrayElementIndex() );
            }
            else
            {
                propertyPath += propertyInstance.GetID();
            }

            //-------------------------------------------------------------------------

            if ( propertyInstance.IsArray() )
            {
                // Flatten array elements
                for ( auto const& childProperty : propertyInstance.GetProperties() )
                {
                    FlattenProperties( childProperty, propertyPath, outProperties );
                }
            }
            else if ( propertyInstance.IsStructure() )
            {
                for ( auto const& childProperty : propertyInstance.GetProperties() )
                {
                    FlattenProperties( childProperty, propertyPath, outProperties );
                }
            }
            else // Core Types/Enums
            {
                outProperties.push_back( ToolPropertyInstanceDescriptor( propertyPath, propertyInstance.GetStringValue(), propertyInstance.GetTypeID() ) );
            }
        }
    }

    //-------------------------------------------------------------------------

    ToolTypeInstance::ToolTypeInstance( TypeRegistry const& typeRegistry, TypeInfo const* pTypeInfo )
        : ToolPropertyInstance( typeRegistry, pTypeInfo )
    {}

    ToolTypeInstance::ToolTypeInstance( TypeRegistry const& typeRegistry, ToolTypeInstanceDescriptor const& typeDescriptor )
        : ToolTypeInstance( typeRegistry, typeRegistry.GetTypeInfo( typeDescriptor.m_typeID ) )
    {
        // Set property values
        for ( auto const& serializedProperty : typeDescriptor.m_properties )
        {
            auto pProperty = GetProperty( serializedProperty.m_path, true );
            if ( pProperty )
            {
                pProperty->SetStringValue( serializedProperty.m_value );
            }
        }
    }

    //-------------------------------------------------------------------------

    ToolTypeInstanceDescriptor ToolTypeInstance::GetDescriptor() const
    {
        ToolTypeInstanceDescriptor descriptor;
        descriptor.m_typeID = m_pTypeInfo->m_ID;

        // Get all properties that have a non-default value set
        PropertyPath path;
        for ( auto const& propertyInstance : m_childProperties )
        {
            FlattenProperties( propertyInstance, path, descriptor.m_properties );
        }

        return descriptor;
    }
}