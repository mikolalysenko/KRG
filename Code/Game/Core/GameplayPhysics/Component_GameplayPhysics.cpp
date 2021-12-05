#include "Component_GameplayPhysics.h"
#include "GameplayPhysicsState.h"

//-------------------------------------------------------------------------

namespace KRG::GameplayPhysics
{
    void GameplayPhysicsComponent::CreatePhysicsStates()
    {
        KRG_ASSERT( m_registeredStates.empty() );
        CreatePhysicsStatesInternal();
        KRG_ASSERT( !m_registeredStates.empty() );
    }

    void GameplayPhysicsComponent::DestroyPhysicsStates()
    {
        KRG_ASSERT( !m_registeredStates.empty() );
        m_pActiveState->Deactivate();

        for ( auto pRegisteredState : m_registeredStates )
        {
            KRG::Delete( pRegisteredState );
        }
        m_registeredStates.clear();
        m_pActiveState = nullptr;
    }
}