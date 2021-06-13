#include "AnimationGraphTools_AnimationGraph.h"
#include "AnimationGraphTools_Compilation.h"
#include "Nodes/AnimationToolsNode_Results.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    ToolsAnimationGraph::~ToolsAnimationGraph()
    {
        ResetInternalState();
    }

    void ToolsAnimationGraph::ResetInternalState()
    {
        for ( auto pParameter : m_controlParameters )
        {
            KRG::Delete( pParameter );
        }
        m_controlParameters.clear();

        for ( auto pParameter : m_virtualParameters )
        {
            KRG::Delete( pParameter );
        }
        m_virtualParameters.clear();

        m_variations.Reset();

        KRG::Delete( m_pRootGraph );
    }

    void ToolsAnimationGraph::CreateNew()
    {
        ResetInternalState();

        // Create root blend tree
        m_pRootGraph = KRG::New<ToolsGraph>( GraphType::BlendTree );
        m_pRootGraph->CreateNode<ResultToolsNode>( NodeValueType::Pose );
    }

    bool ToolsAnimationGraph::Load( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonValue const& graphObjectValue )
    {
        KRG_ASSERT( graphObjectValue.IsObject() );

        ResetInternalState();

        // Root Graph
        //-------------------------------------------------------------------------

        auto rootGraphValueIter = graphObjectValue.FindMember( "RootGraph" );
        if ( rootGraphValueIter == graphObjectValue.MemberEnd() )
        {
            return false;
        }

        m_pRootGraph = SafeCast<ToolsGraph>( GraphEditor::BaseGraph::CreateGraphFromSerializedData( typeRegistry, rootGraphValueIter->value, nullptr ) );

        // Variations
        //-------------------------------------------------------------------------

        auto variationsValueIter = graphObjectValue.FindMember( "Variations" );
        if ( variationsValueIter == graphObjectValue.MemberEnd() || !variationsValueIter->value.IsArray() )
        {
            return false;
        }

        if ( !m_variations.Serialize( typeRegistry, variationsValueIter->value ) )
        {
            return false;
        }

        // Control Parameters
        //-------------------------------------------------------------------------

        auto controlParametersValueIter = graphObjectValue.FindMember( "ControlParameters" );
        if ( controlParametersValueIter == graphObjectValue.MemberEnd() )
        {
            return false;
        }

        for ( auto& nodeObjectValue : controlParametersValueIter->value.GetArray() )
        {
            auto pNewParameter = GraphEditor::BaseNode::CreateNodeFromSerializedData( typeRegistry, nodeObjectValue, nullptr );
            m_controlParameters.emplace_back( SafeCast<ControlParameterToolsNode>( pNewParameter ) );
        }

        // Fix reference node ptrs
        auto const controlParameterReferences = FindAllNodesOfType<ControlParameterReferenceToolsNode>();
        for ( auto const& pParameter : controlParameterReferences )
        {
            auto pFoundParameter = FindControlParameter( pParameter->GetReferencedParameterID() );
            if ( pFoundParameter != nullptr )
            {
                pParameter->m_pParameter = pFoundParameter;
            }
            else // Invalid graph data encountered
            {
                return false;
            }
        }

        // Virtual Parameters
        //-------------------------------------------------------------------------

        auto virtualParametersValueIter = graphObjectValue.FindMember( "VirtualParameters" );
        if( virtualParametersValueIter == graphObjectValue.MemberEnd() )
        {
            return false;
        }

        for ( auto& nodeObjectValue : virtualParametersValueIter->value.GetArray() )
        {
            auto pNewParameter = GraphEditor::BaseNode::CreateNodeFromSerializedData( typeRegistry, nodeObjectValue, nullptr );
            m_virtualParameters.emplace_back( SafeCast<VirtualParameterToolsNode>( pNewParameter ) );
        }

        // Fix reference node ptrs
        auto const virtualParameterReferences = FindAllNodesOfType<VirtualParameterReferenceToolsNode>();
        for ( auto const& pParameter : virtualParameterReferences )
        {
            auto pFoundParameter = FindVirtualParameter( pParameter->GetReferencedParameterID() );
            if ( pFoundParameter != nullptr )
            {
                pParameter->m_pParameter = pFoundParameter;
            }
            else // Invalid graph data encountered
            {
                return false;
            }
        }

        return true;
    }

    void ToolsAnimationGraph::Save( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonWriter& writer ) const
    {
        writer.StartObject();

        writer.Key( "RootGraph" );
        m_pRootGraph->Serialize( typeRegistry, writer );

        //-------------------------------------------------------------------------

        writer.Key( "Variations" );
        m_variations.Serialize( typeRegistry, writer );

        //-------------------------------------------------------------------------

        writer.Key( "ControlParameters" );
        writer.StartArray();

        for ( auto pNode : m_controlParameters )
        {
            pNode->Serialize( typeRegistry, writer );
        }

        writer.EndArray();

        //-------------------------------------------------------------------------

        writer.Key( "VirtualParameters" );
        writer.StartArray();

        for ( auto pNode : m_virtualParameters )
        {
            pNode->Serialize( typeRegistry, writer );
        }

        writer.EndArray();

        //-------------------------------------------------------------------------

        writer.EndObject();
    }

    //-------------------------------------------------------------------------

    void ToolsAnimationGraph::CreateControlParameter( NodeValueType type )
    {
        String parameterName = "Parameter";
        EnsureUniqueParameterName( parameterName );
        m_controlParameters.emplace_back( KRG::New<ControlParameterToolsNode>( parameterName, type ) );
    }

    void ToolsAnimationGraph::CreateVirtualParameter( NodeValueType type )
    {
        String parameterName = "Parameter";
        EnsureUniqueParameterName( parameterName );
        m_virtualParameters.emplace_back( KRG::New<VirtualParameterToolsNode>( parameterName, type ) );
    }

    void ToolsAnimationGraph::RenameControlParameter( UUID parameterID, String newName )
    {
        auto pParameter = FindControlParameter( parameterID );
        KRG_ASSERT( pParameter != nullptr );
        EnsureUniqueParameterName( newName );
        pParameter->m_name = newName;
    }

    void ToolsAnimationGraph::RenameVirtualParameter( UUID parameterID, String newName )
    {
        auto pParameter = FindVirtualParameter( parameterID );
        KRG_ASSERT( pParameter != nullptr );
        EnsureUniqueParameterName( newName );
        pParameter->m_name = newName;
    }

    void ToolsAnimationGraph::DestroyControlParameter( UUID parameterID )
    {
        // Find and remove all reference nodes
        auto const controlParameterReferences = FindAllNodesOfType<ControlParameterReferenceToolsNode>();

        for ( auto const& pFoundParameterNode : controlParameterReferences )
        {
            if ( pFoundParameterNode->GetReferencedParameterID() == parameterID )
            {
                pFoundParameterNode->Destroy();
            }
        }

        // Delete parameter
        for ( auto iter = m_controlParameters.begin(); iter != m_controlParameters.end(); ++iter )
        {
            if ( ( *iter )->m_ID == parameterID )
            {
                KRG::Delete( *iter );
                m_controlParameters.erase( iter );
                break;
            }
        }
    }

    void ToolsAnimationGraph::DestroyVirtualParameter( UUID parameterID )
    {
        KRG_ASSERT( FindVirtualParameter( parameterID ) != nullptr );

        // Find and remove all reference nodes
        auto const virtualParameterReferences = FindAllNodesOfType<VirtualParameterReferenceToolsNode>();

        for ( auto const& pFoundParameterNode : virtualParameterReferences )
        {
            if ( pFoundParameterNode->GetReferencedParameterID() == parameterID )
            {
                pFoundParameterNode->Destroy();
            }
        }

        // Delete parameter
        for ( auto iter = m_virtualParameters.begin(); iter != m_virtualParameters.end(); ++iter )
        {
            if ( (*iter)->m_ID == parameterID )
            {
                KRG::Delete( *iter );
                m_virtualParameters.erase( iter );
                break;
            }
        }
    }

    void ToolsAnimationGraph::EnsureUniqueParameterName( String& parameterName ) const
    {
        String tempString = parameterName;
        bool isNameUnique = false;
        int32 suffix = 0;

        while ( !isNameUnique )
        {
            isNameUnique = true;

            // Check control parameters
            for ( auto pParameter : m_controlParameters )
            {
                if ( pParameter->m_name == tempString )
                {
                    isNameUnique = false;
                    break;
                }
            }

            // Check virtual parameters
            if ( isNameUnique )
            {
                for ( auto pParameter : m_virtualParameters )
                {
                    if ( pParameter->m_name == tempString )
                    {
                        isNameUnique = false;
                        break;
                    }
                }
            }

            if ( !isNameUnique )
            {
                tempString.sprintf( "%s_%d", parameterName.c_str(), suffix );
                suffix++;
            }
        }

        //-------------------------------------------------------------------------

        parameterName = tempString;
    }

    ControlParameterToolsNode* ToolsAnimationGraph::FindControlParameter( UUID parameterID ) const
    {
        for ( auto pParameter : m_controlParameters )
        {
            if ( pParameter->m_ID == parameterID )
            {
                return pParameter;
            }
        }
        return nullptr;
    }

    VirtualParameterToolsNode* ToolsAnimationGraph::FindVirtualParameter( UUID parameterID ) const
    {
        for ( auto pParameter : m_virtualParameters )
        {
            if ( pParameter->m_ID == parameterID )
            {
                return pParameter;
            }
        }
        return nullptr;
    }

    bool ToolsAnimationGraph::Compile( ToolsGraphCompilationContext& context ) const
    {
        KRG_ASSERT( IsValid() );

        // Always compile control parameters first
        //-------------------------------------------------------------------------

        for ( auto pParameter : m_controlParameters )
        {
            if ( pParameter->Compile( context ) == InvalidIndex )
            {
                return false;
            }
        }

        context.m_numControlParameters = (uint32) m_controlParameters.size();

        // Then Virtual parameters
        //-------------------------------------------------------------------------

        for ( auto pParameter : m_virtualParameters )
        {
            if ( pParameter->Compile( context ) == InvalidIndex )
            {
                return false;
            }
        }

        // Finally compile the actual graph
        //-------------------------------------------------------------------------

        auto const resultNodes = m_pRootGraph->FindAllNodesOfType<ResultToolsNode>( false );
        KRG_ASSERT( resultNodes.size() == 1 );
        context.m_rootNodeIdx = resultNodes[0]->Compile( context );
        context.m_persistentNodeIndices.emplace_back( context.m_rootNodeIdx );

        return context.m_rootNodeIdx != InvalidIndex;
    }
}