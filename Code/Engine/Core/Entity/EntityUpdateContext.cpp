#include "EntityUpdateContext.h"
#include "EntityWorld.h"

//-------------------------------------------------------------------------

namespace KRG
{
    EntityUpdateContext::EntityUpdateContext( UpdateContext const& context, EntityWorld* pWorld )
        : UpdateContext( context )
        , m_pWorld( pWorld )
    {
        KRG_ASSERT( m_pWorld != nullptr );
    }

    IWorldEntitySystem* EntityUpdateContext::GetWorldSystem( uint32 worldSystemID ) const
    {
        return m_pWorld->GetWorldSystem( worldSystemID );
    }

    Render::Viewport const* EntityUpdateContext::GetViewport() const
    {
        return m_pWorld->GetViewport();
    }

    Debug::DrawingContext EntityUpdateContext::GetDrawingContext() const
    {
        return m_pWorld->m_debugDrawingSystem.GetDrawingContext();
    }

    UUID const& EntityUpdateContext::GetWorldID() const
    {
        return m_pWorld->GetID();
    }
}