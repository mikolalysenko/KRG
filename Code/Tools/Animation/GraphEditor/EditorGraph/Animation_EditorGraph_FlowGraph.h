#pragma once
#include "Animation_EditorGraph_Common.h"
#include "Tools/Core/VisualGraph/VisualGraph_FlowGraph.h"
#include "Engine/Animation/Graph/Animation_RuntimeGraph_Common.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    class EditorGraphCompilationContext;
    class VariationHierarchy;

    //-------------------------------------------------------------------------
    // CORE EDITOR NODES
    //-------------------------------------------------------------------------

    class EditorGraphNode : public VisualGraph::Flow::Node
    {
        KRG_REGISTER_TYPE( EditorGraphNode );

    public:

        using VisualGraph::Flow::Node::Node;

        // Get the type of node this is, this is either the output type for the nodes with output or the first input for nodes with no outputs
        KRG_FORCE_INLINE ValueType GetValueType() const
        {
            if ( GetNumOutputPins() > 0 )
            {
                return ValueType( GetOutputPin( 0 )->m_type );
            }
            else if ( GetNumInputPins() > 0 )
            {
                return ValueType( GetInputPin( 0 )->m_type );
            }
            else
            {
                return ValueType::Unknown;
            }
        }

        virtual ImColor GetNodeColor() const override { return ImGuiX::ConvertColor( GetColorForValueType( GetValueType() ) ); }

        virtual ImColor GetPinColor( VisualGraph::Flow::Pin const& pin ) const override { return ImGuiX::ConvertColor( GetColorForValueType( (ValueType) pin.m_type ) ); }

        // Get the types of graphs that this node is allowed to be placed in
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const = 0;

        // Is this node a persistent node i.e. is it always initialized 
        virtual bool IsPersistentNode() const { return false; }

        // Compile this node into its runtime representation. Returns the node index of the compiled node.
        virtual NodeIndex Compile( EditorGraphCompilationContext& context ) const { return InvalidIndex; }

    protected:

        KRG_FORCE_INLINE void CreateInputPin( char const* pPinName, ValueType pinType ) { VisualGraph::Flow::Node::CreateInputPin( pPinName, (uint32) pinType ); }
        KRG_FORCE_INLINE void CreateOutputPin( char const* pPinName, ValueType pinType, bool allowMultipleOutputConnections = false ) { VisualGraph::Flow::Node::CreateOutputPin( pPinName, (uint32) pinType, allowMultipleOutputConnections ); }

        virtual void DrawExtraControls( VisualGraph::DrawContext const& ctx ) override;

        // Draw any extra information about the node
        virtual void DrawInfoText( VisualGraph::DrawContext const& ctx ) {}
    };

    class DataSlotEditorNode : public EditorGraphNode
    {
        KRG_REGISTER_TYPE( DataSlotEditorNode );

    public:

        struct OverrideValue : public IRegisteredType
        {
            KRG_REGISTER_TYPE( OverrideValue );

            KRG_REGISTER StringID               m_variationID;
            KRG_REGISTER ResourceID             m_resourceID;
        };

    public:

        bool AreSlotValuesValid() const;
        virtual ResourceTypeID GetSlotResourceType() const { return ResourceTypeID(); }

        // This will return the final resolved resource value for this slot
        ResourceID GetValue( VariationHierarchy const& variationHierarchy, StringID variationID ) const;

        // Variation override management
        //-------------------------------------------------------------------------

        bool HasOverrideForVariation( StringID variationID ) const { return GetOverrideValueForVariation( variationID ) != nullptr; }
        ResourceID* GetOverrideValueForVariation( StringID variationID );
        ResourceID const* GetOverrideValueForVariation( StringID variationID ) const { return const_cast<DataSlotEditorNode*>( this )->GetOverrideValueForVariation( variationID ); }

        void CreateOverride( StringID variationID );
        void RenameOverride( StringID oldVariationID, StringID newVariationID );
        void RemoveOverride( StringID variationID );
        void SetOverrideValueForVariation( StringID variationID, ResourceID const& resourceID );

    protected:

        KRG_REGISTER ResourceID                 m_defaultResourceID;
        KRG_REGISTER TVector<OverrideValue>     m_overrides;
    };

    class ResultEditorNode final : public EditorGraphNode
    {
        KRG_REGISTER_TYPE( ResultEditorNode );

    public:

        ResultEditorNode() = default;
        ResultEditorNode( ValueType valueType );

        virtual void Initialize( VisualGraph::BaseGraph* pParent ) override;

        virtual char const* GetTypeName() const override { return "Result"; }
        virtual char const* GetCategory() const override { return "Results"; }
        virtual bool IsUserCreatable() const override { return false; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::BlendTree, GraphType::ValueTree ); }
        virtual NodeIndex Compile( EditorGraphCompilationContext& context ) const override;

    private:

        KRG_REGISTER ValueType m_valueType = ValueType::Pose;
    };

    //-------------------------------------------------------------------------
    // PARAMETERS
    //-------------------------------------------------------------------------

    class ControlParameterEditorNode final : public EditorGraphNode
    {
        KRG_REGISTER_TYPE( ControlParameterEditorNode );
        friend class AnimationGraphEditorDefinition;

    public:

        ControlParameterEditorNode() = default;
        ControlParameterEditorNode( String const& name, ValueType type );

        virtual void Initialize( VisualGraph::BaseGraph* pParentGraph ) override;
        virtual bool IsVisibleNode() const override { return false; }
        virtual char const* GetDisplayName() const override { return m_name.c_str(); }
        virtual char const* GetTypeName() const override { return "Parameter"; }
        virtual char const* GetCategory() const override { return "Control Parameters"; }
        virtual bool IsUserCreatable() const override { return false; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::BlendTree, GraphType::ValueTree, GraphType::TransitionTree ); }
        virtual NodeIndex Compile( EditorGraphCompilationContext& context ) const override;
        virtual bool IsPersistentNode() const override { return true; }

    private:

        KRG_REGISTER String                     m_name;
        KRG_REGISTER ValueType                  m_type = ValueType::Float;
    };

    class VirtualParameterEditorNode final : public EditorGraphNode
    {
        KRG_REGISTER_TYPE( VirtualParameterEditorNode );
        friend class AnimationGraphEditorDefinition;

    public:

        VirtualParameterEditorNode() = default;
        VirtualParameterEditorNode( String const& name, ValueType type );

        virtual void Initialize( VisualGraph::BaseGraph* pParentGraph ) override;
        virtual bool IsVisibleNode() const override { return false; }
        virtual char const* GetDisplayName() const override { return m_name.c_str(); }
        virtual char const* GetTypeName() const override { return "Parameter"; }
        virtual char const* GetCategory() const override { return "Virtual Parameters"; }
        virtual bool IsUserCreatable() const override { return false; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::BlendTree, GraphType::ValueTree, GraphType::TransitionTree ); }
        virtual NodeIndex Compile( EditorGraphCompilationContext& context ) const override;

    private:

        KRG_REGISTER String                     m_name;
        KRG_REGISTER ValueType                  m_type = ValueType::Float;
    };

    class ParameterReferenceEditorNode final : public EditorGraphNode
    {
        KRG_REGISTER_TYPE( ParameterReferenceEditorNode );
        friend class AnimationGraphEditorDefinition;

    public:

        static void RefreshParameterReferences( VisualGraph::BaseGraph* pRootGraph );

    public:

        ParameterReferenceEditorNode() = default;
        ParameterReferenceEditorNode( ControlParameterEditorNode const* pParameter );
        ParameterReferenceEditorNode( VirtualParameterEditorNode const* pParameter );

        virtual void Initialize( VisualGraph::BaseGraph* pParentGraph ) override;

        inline EditorGraphNode const* GetReferencedParameter() const { return m_pParameter; }
        inline UUID const& GetReferencedParameterID() const { return m_parameterUUID; }
        inline ValueType GetParameterValueType() const { return m_parameterValueType; }

        virtual char const* GetDisplayName() const override { return m_pParameter->GetDisplayName(); }
        virtual char const* GetTypeName() const override { return "Parameter"; }
        virtual char const* GetCategory() const override { return "Parameter"; }
        virtual bool IsUserCreatable() const override { return true; }
        virtual bool IsDestroyable() const override { return true; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::BlendTree, GraphType::ValueTree, GraphType::TransitionTree ); }
        virtual NodeIndex Compile( EditorGraphCompilationContext& context ) const override;

    private:

        EditorGraphNode const*                  m_pParameter = nullptr;
        KRG_REGISTER UUID                       m_parameterUUID;
        KRG_REGISTER ValueType                  m_parameterValueType;
    };

    //-------------------------------------------------------------------------
    // BASE ANIMATION FLOW GRAPH
    //-------------------------------------------------------------------------

    class FlowGraph : public VisualGraph::FlowGraph
    {
        friend class AnimationGraphEditorDefinition;
        KRG_REGISTER_TYPE( FlowGraph );

    public:

        FlowGraph( GraphType type = GraphType::BlendTree );

        inline GraphType GetType() const { return m_type; }

        // Node factory methods
        //-------------------------------------------------------------------------

        template<typename T, typename ... ConstructorParams>
        T* CreateNode( ConstructorParams&&... params )
        {
            VisualGraph::ScopedGraphModification sgm( this );

            static_assert( std::is_base_of<EditorGraphNode, T>::value );
            auto pNode = KRG::New<T>( std::forward<ConstructorParams>( params )... );
            KRG_ASSERT( pNode->GetAllowedParentGraphTypes().IsFlagSet( m_type ) );
            pNode->Initialize( this );
            AddNode( pNode );
            return pNode;
        }

        EditorGraphNode* CreateNode( TypeSystem::TypeInfo const* pTypeInfo )
        {
            VisualGraph::ScopedGraphModification sgm( this );

            KRG_ASSERT( pTypeInfo->IsDerivedFrom( EditorGraphNode::GetStaticTypeID() ) );
            auto pNode = Cast<EditorGraphNode>( pTypeInfo->m_pTypeHelper->CreateType() );
            KRG_ASSERT( pNode->GetAllowedParentGraphTypes().IsFlagSet( m_type ) );
            pNode->Initialize( this );
            AddNode( pNode );
            return pNode;
        }

    private:

        virtual void PostPasteNodes( TInlineVector<VisualGraph::BaseNode*, 20> const& pastedNodes ) override;
        virtual void SerializeCustom( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonValue const& graphObjectValue ) override;
        virtual void SerializeCustom( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonWriter& writer ) const override;

    private:

        KRG_REGISTER GraphType       m_type;
    };
}