#pragma once

#include "AnimationGraphNode_Transition.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    class StateMachineNode final : public PoseNode
    {
        using StateIndex = int16;

    public:

        struct TransitionSettings
        {
            KRG_SERIALIZE_MEMBERS( m_targetStateIdx, m_transitionNodeIdx, m_conditionNodeIdx );

            StateIndex                                              m_targetStateIdx = InvalidIndex;
            NodeIndex                                               m_transitionNodeIdx = InvalidIndex;
            NodeIndex                                               m_conditionNodeIdx = InvalidIndex;
        };

        struct StateSettings
        {
            KRG_SERIALIZE_MEMBERS( m_stateNodeIdx, m_entryConditionNodeIdx, m_transitionSettings );

            NodeIndex                                               m_stateNodeIdx = InvalidIndex;
            NodeIndex                                               m_entryConditionNodeIdx = InvalidIndex;
            TInlineVector<TransitionSettings,5>                     m_transitionSettings;
        };

        //-------------------------------------------------------------------------

        struct Settings : public PoseNode::Settings
        {
            KRG_REGISTER_TYPE( Settings );
            KRG_SERIALIZE_GRAPHNODESETTINGS( PoseNode::Settings, m_stateSettings, m_defaultStateIndex );

        public:

            virtual void InstantiateNode( TVector<GraphNode*> const& nodePtrs, AnimationGraphDataSet const* pDataSet, InitOptions options ) const override;

        public:

            TInlineVector<StateSettings, 5>                         m_stateSettings;
            StateIndex                                              m_defaultStateIndex = InvalidIndex;
        };

        //-------------------------------------------------------------------------

        struct Transition
        {
            TransitionNode*                                         m_pTransitionNode = nullptr;
            BoolValueNode*                                          m_pConditionNode = nullptr;
            StateIndex                                              m_targetStateIdx = InvalidIndex;
        };

        struct State
        {
            bool HasForceableTransitions() const;

            StateNode*                                              m_pStateNode = nullptr;
            BoolValueNode*                                          m_pEntryConditionNode = nullptr;
            TInlineVector<Transition, 5>                            m_transitions;
        };

    private:

        virtual SyncTrack const& GetSyncTrack() const override;
        virtual bool IsValid() const override;

        virtual void InitializeInternal( GraphContext& context, SyncTrackTime const& initialTime ) override;
        virtual void ShutdownInternal( GraphContext& context ) override;

        virtual PoseNodeResult Update( GraphContext& context ) override;
        virtual PoseNodeResult Update( GraphContext& context, SyncTrackTimeRange const& updateRange ) override;
        virtual void DeactivateBranch( GraphContext& context ) override;

        StateIndex SelectDefaultState( GraphContext& context ) const;

        void InitializeTransitionConditions( GraphContext& context );
        void ShutdownTransitionConditions( GraphContext& context );

        void EvaluateTransitions( GraphContext& context, PoseNodeResult& NodeResult );
        void UpdateTransitionStack( GraphContext& context );

    private:

        TInlineVector<State, 10>                                m_states;
        TransitionNode*                                         m_pActiveTransition;
        StateIndex                                              m_activeStateIndex;
    };
}