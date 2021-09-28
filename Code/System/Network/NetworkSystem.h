#pragma once
#include "_Module\API.h"
#include "System\Core\Types\Containers.h"
#include "System\Core\Types\Function.h"
#include "System\Core\Types\String.h"

//-------------------------------------------------------------------------

namespace KRG::Network
{
    class NetworkSystem;

    //-------------------------------------------------------------------------

    class KRG_SYSTEM_NETWORK_API ServerConnection
    {
        friend NetworkSystem;
        friend struct NetworkCallbackHandler;

    public:

        using ClientConnectionHandle = uint32;

    public:

        virtual ~ServerConnection();

        inline bool IsRunning() const { return m_socketHandle != 0 && m_pollingGroupHandle != 0; }

        inline uint32 GetSocketHandle() const { return m_socketHandle; }

        inline TVector<uint32> const& GetConnectedClientIDs() const { return m_connectedClients; }

        virtual void ProcessMessage( uint32 connectionID, void* pData, size_t size ) = 0;

        virtual void SendMessages( TFunction<void( ClientConnectionHandle, void*, uint32 )> const& sendFunction ) = 0;

    protected:

        uint32                                          m_socketHandle = 0;
        uint32                                          m_pollingGroupHandle = 0;
        TVector<ClientConnectionHandle>                 m_connectedClients;
    };

    //-------------------------------------------------------------------------

    class KRG_SYSTEM_NETWORK_API ClientConnection
    {
        friend NetworkSystem;
        friend struct NetworkCallbackHandler;

    public:

        enum class Status
        {
            Disconnected,
            Connecting,
            Connected,
            Reconnecting,
            ConnectionFailed
        };

    public:

        virtual ~ClientConnection();

        inline bool IsConnected() const { return m_status == Status::Connected; }
        inline bool IsConnecting() const { return m_status == Status::Connecting || m_status == Status::Reconnecting; };
        inline bool HasConnectionFailed() const { return m_status == Status::ConnectionFailed; }
        inline bool IsDisconnected() const { return m_status == Status::Disconnected; }

        inline uint32 const& GetClientConnectionID() const { return m_connectionHandle; }
        inline InlineString<25> const& GetAddress() const { return m_address; }

        virtual void ProcessMessage( void* pData, size_t size ) = 0;

        virtual void SendMessages( TFunction<void( void*, uint32 )> const& sendFunction ) = 0;

    private:

        void Update();
        bool TryStartConnection();
        void CloseConnection();

    private:

        InlineString<25>                                m_address;
        uint32                                          m_connectionHandle = 0;
        uint32                                          m_reconnectionAttemptsRemaining = 5;
        Status                                          m_status = Status::Disconnected;
    };

    //-------------------------------------------------------------------------

    class KRG_SYSTEM_NETWORK_API NetworkSystem final
    {
        friend struct NetworkCallbackHandler;

    public:

        static bool Initialize();
        static void Shutdown();
        static void Update();

        // Start a server connection on the specified port
        static bool StartServerConnection( ServerConnection* pServerConnection, uint16 portNumber );
        static void StopServerConnection( ServerConnection* pServerConnection );

        // Start a client connection to a specified address. Address format: "XXX.XXX.XXX.XXX:Port"
        static bool StartClientConnection( ClientConnection* pClientConnection, char const* pAddress );
        static void StopClientConnection( ClientConnection* pClientConnection );

    private:

        NetworkSystem() = delete;
    };
}