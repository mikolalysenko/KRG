#pragma once
#include "../AnimationGraphTools_Node.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    class SelectorConditionNode final : public ToolsNode
    {
        KRG_REGISTER_TYPE( SelectorConditionNode );

        friend class SelectorToolsNode;

    public:

        SelectorConditionNode();

        virtual char const* GetTypeName() const override { return "Conditions"; }
        virtual char const* GetCategory() const override { return "Conditions"; }
        virtual bool IsUserCreatable() const override { return false; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::ValueTree ); }
    };

    //-------------------------------------------------------------------------

    class SelectorToolsNode final : public ToolsNode
    {
        KRG_REGISTER_TYPE( SelectorToolsNode );

    public:

        SelectorToolsNode();

    private:

        virtual char const* GetTypeName() const override { return "Selector"; }
        virtual char const* GetCategory() const override { return "Flow"; }
        virtual TBitFlags<GraphType> GetAllowedParentGraphTypes() const override { return TBitFlags<GraphType>( GraphType::BlendTree ); }
        virtual NodeIndex Compile( ToolsGraphCompilationContext& context ) const override;

        virtual bool SupportsDynamicInputPins() const override { return true; }
        virtual InlineString<100> GetNewDynamicInputPinName() const override;
        virtual uint32 GetDynamicInputPinValueType() const override { return (uint32) NodeValueType::Pose; }
        virtual void OnDynamicPinCreation( UUID pinID ) override;
        virtual void OnDynamicPinDestruction( UUID pinID ) override;
    };
}