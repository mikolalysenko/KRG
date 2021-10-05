//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "d:\Kruger\Code\Engine\Core\_Module\_AutoGenerated\2571240691.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::Math::Easing::Type
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_Math_Easing_Type::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::Math::Easing::Type" );
                typeInfo.m_size = sizeof( KRG::Math::Easing::Type );
                typeInfo.m_alignment = alignof( KRG::Math::Easing::Type );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::Math::Easing::Type" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Uint8;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInQuart" ), 12 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInCirc" ), 28 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutCubic" ), 6 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutCubic" ), 7 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutSine" ), 19 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInSine" ), 20 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutCirc" ), 26 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutQuart" ), 11 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutQuint" ), 14 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InSine" ), 17 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InCubic" ), 5 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InQuart" ), 9 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutQuint" ), 15 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInQuad" ), 4 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Linear" ), 0 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInQuint" ), 16 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InCirc" ), 25 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutQuart" ), 10 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutQuad" ), 2 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InQuint" ), 13 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InExpo" ), 21 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInCubic" ), 8 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutCirc" ), 27 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InQuad" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutExpo" ), 23 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutSine" ), 18 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutInExpo" ), 24 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "OutExpo" ), 22 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "InOutQuad" ), 3 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_Math_Easing_Type::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::Math::Easing::Type" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}
