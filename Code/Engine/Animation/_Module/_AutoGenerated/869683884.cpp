//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "d:\Kruger\Code\Engine\Animation\_Module\_AutoGenerated\869683884.h"

//-------------------------------------------------------------------------
// Enum Helper: KRG::Animation::Graph::IDComparisonNode::Comparison
//-------------------------------------------------------------------------

namespace KRG
{
    namespace TypeSystem
    {
        namespace EnumHelpers
        {
            void EnumHelper_KRG_Animation_Graph_IDComparisonNode_Comparison::RegisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                TypeSystem::TypeInfo typeInfo;
                typeInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Graph::IDComparisonNode::Comparison" );
                typeInfo.m_size = sizeof( KRG::Animation::Graph::IDComparisonNode::Comparison );
                typeInfo.m_alignment = alignof( KRG::Animation::Graph::IDComparisonNode::Comparison );
                typeRegistry.RegisterType( typeInfo );

                TypeSystem::EnumInfo enumInfo;
                enumInfo.m_ID = TypeSystem::TypeID( "KRG::Animation::Graph::IDComparisonNode::Comparison" );
                enumInfo.m_underlyingType = TypeSystem::CoreTypes::Uint8;
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "DoesntMatch" ), 1 ) );
                enumInfo.m_constants.insert( TPair<StringID, int64>( StringID( "Matches" ), 0 ) );

                typeRegistry.RegisterEnum( enumInfo );
            }

            void EnumHelper_KRG_Animation_Graph_IDComparisonNode_Comparison::UnregisterEnum( TypeSystem::TypeRegistry& typeRegistry )
            {
                auto const ID = TypeSystem::TypeID( "KRG::Animation::Graph::IDComparisonNode::Comparison" );
                typeRegistry.UnregisterType( ID );
                typeRegistry.UnregisterEnum( ID );
            }
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Graph::IDComparisonNode::Settings
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Animation::Graph::IDComparisonNode::Settings::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Animation::Graph::IDComparisonNode::Settings>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Animation::Graph::IDComparisonNode::Settings> TTypeHelper<KRG::Animation::Graph::IDComparisonNode::Settings>::StaticTypeHelper;
        }
    }
}

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::Graph::IDToFloatNode::Settings
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Animation::Graph::IDToFloatNode::Settings::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Animation::Graph::IDToFloatNode::Settings>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Animation::Graph::IDToFloatNode::Settings> TTypeHelper<KRG::Animation::Graph::IDToFloatNode::Settings>::StaticTypeHelper;
        }
    }
}
