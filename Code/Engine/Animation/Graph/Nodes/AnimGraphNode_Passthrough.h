#pragma once
#include "Engine/Animation/Graph/AnimGraphNode.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    class FPassthroughNode : public AnimationNode
    {
    public:

        struct Settings : public AnimationNode::Settings
        {
            NodeIndex       m_childNodeIdx = InvalidIndex;
        };

    public:

        virtual bool IsValid() const override { return AnimationNode::IsValid() && IsChildValid(); }
        virtual SyncTrack const& GetSyncTrack() const override;

    protected:

        virtual void OnConstruct( GraphNode::Settings const* pSettings, TVector<GraphNode*> const& nodePtrs, GraphDataSet const& dataSet ) override;
        virtual void InitializeInternal( GraphContext& context, SyncTrackTime const& initialTime ) override;
        virtual void ShutdownInternal( GraphContext& context ) override;

        // Syntactic sugar for readability in derived classes
        inline bool IsChildValid() const { return m_pChildNode->IsValid(); }

        virtual AnimationNode::UpdateResult Update( GraphContext& context ) override;
        virtual AnimationNode::UpdateResult Update( GraphContext& context, SyncTrackTimeRange const& updateRange ) override;
        virtual void DeactivateBranch( GraphContext& context );

    protected:

        AnimationNode*      m_pChildNode = nullptr;
    };
}