//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "d:\Kruger\Code\Engine\Animation\_Module\_AutoGenerated\2466578237.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::Animation::Event::EventType
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_Animation_Event_EventType::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Event::EventType" );
                typeInfo.m_size = sizeof( KRG::Animation::Event::EventType );
                typeInfo.m_alignment = alignof( KRG::Animation::Event::EventType );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Event::EventType" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Int32;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Both" ), 2 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Immediate" ), 0 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Duration" ), 1 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_Animation_Event_EventType::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::Animation::Event::EventType" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Event
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Animation::Event::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Animation::Event>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Animation::Event> TTypeHelper<KRG::Animation::Event>::StaticTypeHelper;
        }
    }
}
