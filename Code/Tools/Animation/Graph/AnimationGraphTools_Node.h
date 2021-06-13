#pragma once
#include "AnimationGraphTools_Common.h"
#include "AnimationGraphTools_Variations.h"
#include "Tools/Core/GraphEditor/FlowGraph.h"
#include "Engine/Animation/Graph/AnimationGraphCommon.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    class ToolsGraphCompilationContext;

    //-------------------------------------------------------------------------

    class ToolsNode : public GraphEditor::Flow::Node
    {
        KRG_REGISTER_TYPE( ToolsNode );

    public:

        // Get the type of node this is, this is either the output type for the nodes with output or the first input for nodes with no outputs
        KRG_FORCE_INLINE NodeValueType GetValueType() const
        {
            if ( GetNumOutputPins() == 0 )
            {
                KRG_ASSERT( GetNumInputPins() > 0 );
                return NodeValueType( GetInputPin( 0 )->m_type );
            }
            else
            {
                return NodeValueType( GetOutputPin( 0 )->m_type );
            }
        }

        virtual ImColor GetColor() const final { return GetColorForValueType( GetValueType() ); }

        virtual ImColor GetPinColor( GraphEditor::Flow::Pin const& pin ) const final { return GetColorForValueType( (NodeValueType) pin.m_type ); }

        // Get the types of graphs that this node is allowed to be placed in
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const = 0;

        // Is this node a persistent node i.e. is it always initialized 
        virtual bool IsPersistentNode() const { return false; }

        // Compile this node into its runtime representation. Returns the node index of the compiled node.
        virtual NodeIndex Compile( ToolsGraphCompilationContext& context ) const { return InvalidIndex; }

        // Returns the string path from the root graph
        String GetPathFromRoot() const;

    protected:

        KRG_FORCE_INLINE void CreateInputPin( char const* pPinName, NodeValueType pinType ) { GraphEditor::Flow::Node::CreateInputPin( pPinName, (uint32) pinType ); }
        KRG_FORCE_INLINE void CreateOutputPin( char const* pPinName, NodeValueType pinType, bool allowMultipleOutputConnections = false ) { GraphEditor::Flow::Node::CreateOutputPin( pPinName, (uint32) pinType, allowMultipleOutputConnections ); }
    };

    //-------------------------------------------------------------------------

    class DataSlotNode : public ToolsNode
    {
        KRG_REGISTER_TYPE( DataSlotNode );

    public:

        struct OverrideValue : public IRegisteredType
        {
            KRG_REGISTER_TYPE( OverrideValue );

            REGISTER StringID               m_variationID;
            REGISTER ResourceID             m_resourceID;
        };

    public:

        bool AreSlotValuesValid() const;
        virtual ResourceTypeID GetSlotResourceType() const { return ResourceTypeID::Unknown; }

        // This will return the final resolved resource value for this slot
        ResourceID GetValue( VariationHierarchy const& variationHierarchy, StringID variationID ) const;

        // Variation override management
        //-------------------------------------------------------------------------

        bool HasOverrideForVariation( StringID variationID ) const { return GetOverrideValueForVariation( variationID ) != nullptr; }
        ResourceID* GetOverrideValueForVariation( StringID variationID );
        ResourceID const* GetOverrideValueForVariation( StringID variationID ) const { return const_cast<DataSlotNode*>( this )->GetOverrideValueForVariation( variationID ); }

        void CreateOverride( StringID variationID );
        void RenameOverride( StringID oldVariationID, StringID newVariationID );
        void RemoveOverride( StringID variationID );
        void SetOverrideValueForVariation( StringID variationID, ResourceID const& resourceID );

    protected:

        REGISTER ResourceID                 m_defaultResourceID;
        REGISTER TVector<OverrideValue>     m_overrides;
    };
}