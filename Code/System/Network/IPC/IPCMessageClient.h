#pragma once

#include "System/Network/_Module/API.h"
#include "IPCMessage.h"
#include "System/Network/NetworkSystem.h"

//-------------------------------------------------------------------------

namespace KRG::Network::IPC
{
    class KRG_SYSTEM_NETWORK_API Client final : public ClientConnection
    {
    public:

        // Queues a message to be sent to the server. Note this is a destructive operation!! This call will move the data 
        void SendMessageToServer( Message&& message );

        // Iterates over all incoming messages and calls the processing function
        void ProcessIncomingMessages( TFunction<void( Message const& message )> messageProcessorFunction );

    private:

        virtual void ProcessMessage( void* pData, size_t size ) override;
        virtual void SendMessages( TFunction<void( void*, uint32 )> const& sendFunction ) override;

    protected:

        TVector<Message>                        m_incomingMessages;
        TVector<Message>                        m_outgoingMessages;
    };
}