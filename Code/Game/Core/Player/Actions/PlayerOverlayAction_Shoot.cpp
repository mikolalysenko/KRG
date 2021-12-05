#include "PlayerOverlayAction_Shoot.h"
#include "System/Input/InputSystem.h"

//-------------------------------------------------------------------------

namespace KRG::Player
{
    bool ShootOverlayAction::TryStartInternal( ActionContext const& ctx )
    {
        if ( ctx.m_pInputSystem->GetControllerState()->GetRightTriggerValue() >= 0.2f )
        {
            return true;
        }

        return false;
    }

    Action::Status ShootOverlayAction::UpdateInternal( ActionContext const& ctx )
    {
        if ( ctx.m_pInputSystem->GetControllerState()->GetRightTriggerValue() < 0.2f )
        {
            return Status::Completed;
        }

        return Status::Running;
    }

    void ShootOverlayAction::StopInternal( ActionContext const& ctx, StopReason reason )
    {

    }
}