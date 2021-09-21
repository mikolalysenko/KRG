#include "AnimationEventData.h"
#include "Tools/Core/TypeSystem/Serialization/TypeSerialization.h"
#include "System/DevTools/ImguiX.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    struct EventManipulator
    {
        static void SetEventTime( Event* pEvent, Seconds startTime, Seconds duration )
        {
            KRG_ASSERT( pEvent != nullptr && duration >= 0 );
            pEvent->m_startTime = startTime;
            pEvent->m_duration = duration;
        }
    };
}

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    EventItem::EventItem( Event* pEvent, float frameRate )
        : m_pEvent( pEvent )
        , m_animFrameRate( frameRate )
    {
        KRG_ASSERT( m_pEvent != nullptr && m_animFrameRate > 0 );
    }

    EventItem::~EventItem()
    {
        KRG::Delete( m_pEvent );
    }

    InlineString<100> EventItem::GetLabel() const
    {
        return m_pEvent->GetDisplayText();
    }

    FloatRange EventItem::GetTimeRange() const
    {
        KRG_ASSERT( m_animFrameRate != 0 && m_pEvent != nullptr );

        // Convert to frame-time
        float const startTime = m_pEvent->GetStartTime().ToFloat() * m_animFrameRate;
        float const duration = m_pEvent->GetDuration().ToFloat() * m_animFrameRate;
        float const endTime = startTime + duration;

        return FloatRange( startTime, endTime );
    }

    void EventItem::SetTimeRange( FloatRange const& inRange )
    {
        KRG_ASSERT( m_animFrameRate != 0 && m_pEvent != nullptr );

        // Convert to seconds
        float const startTime = inRange.m_start / m_animFrameRate;
        float const duration = inRange.GetLength() / m_animFrameRate;
        EventManipulator::SetEventTime( m_pEvent, startTime, duration );
    }

    void EventItem::SerializeCustom( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonValue const& typeObjectValue )
    {
        m_pEvent = TypeSystem::Serialization::CreateAndReadNativeType<Event>( typeRegistry, typeObjectValue["EventData"] );
    }

    void EventItem::SerializeCustom( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonWriter& writer ) const
    {
        writer.Key( "EventData" );
        TypeSystem::Serialization::WriteNativeType( typeRegistry, writer, m_pEvent );
    }

    //-------------------------------------------------------------------------

    const char* EventTrack::GetLabel() const
    {
        return reinterpret_cast<Event const*>( m_pEventTypeInfo->m_pTypeHelper->GetDefaultTypeInstancePtr() )->GetEventName();
    }

    void EventTrack::CreateItem( float itemStartTime )
    {
        KRG_ASSERT( m_animFrameRate > 0 );

        Seconds const startTime = itemStartTime / m_animFrameRate;

        //-------------------------------------------------------------------------

        auto pNewEvent = (Event*) m_pEventTypeInfo->m_pTypeHelper->CreateType();

        if ( m_eventType == Event::EventType::Immediate )
        {
            EventManipulator::SetEventTime( pNewEvent, startTime, 0.0f );
        }
        else
        {
            EventManipulator::SetEventTime( pNewEvent, startTime, 1.0f / m_animFrameRate );
        }

        m_items.emplace_back( KRG::New<EventItem>( pNewEvent, m_animFrameRate ) );
    };

    void EventTrack::DrawHeader( ImRect const& headerRect )
    {
        ImGui::SameLine( 10 );
        ImGui::AlignTextToFramePadding();
        if ( m_isSyncTrack )
        {
            ImGui::Text( KRG_ICON_HANDSHAKE_O " %s", GetLabel() );
        }
        else
        {
            ImGui::Text( GetLabel() );
        }
    }

    void EventTrack::DrawContextMenu( TVector<TimelineTrack*>& tracks, float playheadPosition )
    {
        if ( m_isSyncTrack )
        {
            if ( ImGui::MenuItem( "Clear Sync Track" ) )
            {
                m_isSyncTrack = false;
            }
        }
        else // Allow setting of sync track
        {
            if ( ImGui::MenuItem( "Set As Sync Track" ) )
            {
                // Clear sync track from any other track
                for ( auto pTrack : tracks )
                {
                    static_cast<EventTrack*>( pTrack )->m_isSyncTrack = false;
                }

                m_isSyncTrack = true;
            }
        }
    }

    void EventTrack::SerializeCustom( TypeSystem::TypeRegistry const& typeRegistry, RapidJsonValue const& typeObjectValue )
    {
        m_pEventTypeInfo = typeRegistry.GetTypeInfo( m_eventTypeID );
        KRG_ASSERT( m_pEventTypeInfo != nullptr );
    }
}