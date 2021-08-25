#include "AnimationGraphNode_Passthrough.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    void PassthroughNode::Settings::InstantiateNode( TVector<GraphNode*> const& nodePtrs, AnimationGraphDataSet const* pDataSet, InitOptions options ) const
    {
        KRG_ASSERT( options == GraphNode::Settings::InitOptions::OnlySetPointers );
        auto pNode = CreateNode<PassthroughNode>( nodePtrs, options );
        SetOptionalNodePtrFromIndex( nodePtrs, m_childNodeIdx, pNode->m_pChildNode );
    }

    //-------------------------------------------------------------------------

    SyncTrack const& PassthroughNode::GetSyncTrack() const
    {
        if ( IsValid() )
        {
            return m_pChildNode->GetSyncTrack();
        }
        else
        {
            return SyncTrack::s_defaultTrack;
        }
    }

    void PassthroughNode::InitializeInternal( GraphContext& context, SyncTrackTime const& initialTime )
    {
        KRG_ASSERT( context.IsValid() );
        PoseNode::InitializeInternal( context, initialTime );

        //-------------------------------------------------------------------------

        m_previousTime = m_currentTime = 0.0f;
        m_duration = 1.0f;

        //-------------------------------------------------------------------------

        if ( m_pChildNode != nullptr )
        {
            m_pChildNode->Initialize( context, initialTime );

            if ( m_pChildNode->IsValid() )
            {
                m_duration = m_pChildNode->GetDuration();
                m_previousTime = m_pChildNode->GetPreviousTime();
                m_currentTime = m_pChildNode->GetCurrentTime();
            }
        }
    }

    void PassthroughNode::ShutdownInternal( GraphContext& context )
    {
        if ( m_pChildNode != nullptr )
        {
            m_pChildNode->Shutdown( context );
        }
        PoseNode::ShutdownInternal( context );
    }

    PoseNodeResult PassthroughNode::Update( GraphContext& context )
    {
        KRG_ASSERT( context.IsValid() );
        MarkNodeActive( context );

        PoseNodeResult result;

        // Forward child node results
        if ( IsChildValid() )
        {
            result = m_pChildNode->Update( context );
            m_duration = m_pChildNode->GetDuration();
            m_previousTime = m_pChildNode->GetPreviousTime();
            m_currentTime = m_pChildNode->GetCurrentTime();
        }
        else
        {
            result.m_sampledEventRange = SampledEventRange( context.m_sampledEvents.GetNumEvents() );
        }

        return result;
    }

    PoseNodeResult PassthroughNode::Update( GraphContext& context, SyncTrackTimeRange const& updateRange )
    {
        KRG_ASSERT( context.IsValid() );
        MarkNodeActive( context );

        PoseNodeResult result;

        // Forward child node results
        if ( IsChildValid() )
        {
            result = m_pChildNode->Update( context, updateRange );
            m_duration = m_pChildNode->GetDuration();
            m_previousTime = m_pChildNode->GetPreviousTime();
            m_currentTime = m_pChildNode->GetCurrentTime();
        }
        else
        {
            result.m_sampledEventRange = SampledEventRange( context.m_sampledEvents.GetNumEvents() );
        }

        return result;
    }

    void PassthroughNode::DeactivateBranch( GraphContext& context )
    {
        if ( IsValid() )
        {
            PoseNode::DeactivateBranch( context );
            m_pChildNode->DeactivateBranch( context );
        }
    }
}