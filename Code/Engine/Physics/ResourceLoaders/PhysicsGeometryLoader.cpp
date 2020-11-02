#include "PhysicsGeometryLoader.h"
#include "Engine/Physics/PhysX.h"
#include "Engine/Physics/PhysicsGeometry.h"
#include "System/Core/Serialization/BinaryArchive.h"

//-------------------------------------------------------------------------

using namespace physx;

//-------------------------------------------------------------------------
namespace KRG::Physics
{
    class PhysXSerializedInputData : public physx::PxInputStream
    {
    public:

        PhysXSerializedInputData( TVector<Byte> const& buffer ) : m_buffer( buffer ) {}

    private:

        virtual PxU32 read( void* dest, PxU32 count ) override final
        {
            KRG_ASSERT( dest != nullptr );
            memcpy( dest, &m_buffer[m_readByteIdx], count );
            m_readByteIdx += count;
            return count;
        }

    private:

        TVector<Byte> const&    m_buffer;
        size_t                  m_readByteIdx = 0;
    };

    //-------------------------------------------------------------------------

    PhysicsGeometryLoader::PhysicsGeometryLoader()
    {
        m_loadableTypes.push_back( PhysicsGeometry::GetStaticResourceTypeID() );
    }

    void PhysicsGeometryLoader::SetPhysics( PxPhysics* pPhysics )
    {
        KRG_ASSERT( pPhysics != nullptr && m_pPhysics == nullptr );
        m_pPhysics = pPhysics;
    }

    bool PhysicsGeometryLoader::LoadInternal( ResourceID const& resID, Resource::ResourceRecord* pResourceRecord, Serialization::BinaryMemoryArchive& archive ) const
    {
        KRG_ASSERT( archive.IsValid() );

        // Create mesh resource
        PhysicsGeometry* pPhysicsGeometry = KRG::New<PhysicsGeometry>();
        archive >> *pPhysicsGeometry;

        // Deserialize cooked mesh data
        if ( pPhysicsGeometry->m_hasTriangleMeshData )
        {
            TVector<Byte> cookedTriangleMeshData;
            archive >> cookedTriangleMeshData;

            PhysXSerializedInputData cooked( cookedTriangleMeshData );
            pPhysicsGeometry->m_pTriangleMesh = m_pPhysics->createTriangleMesh( cooked );
        }

        pResourceRecord->SetResourceData( pPhysicsGeometry );
        return true;
    }

    void PhysicsGeometryLoader::UnloadInternal( ResourceID const& resID, Resource::ResourceRecord* pResourceRecord ) const
    {
        PhysicsGeometry* pPhysicsGeometry = pResourceRecord->GetResourceData<PhysicsGeometry>();
        if ( pPhysicsGeometry != nullptr )
        {
            if ( pPhysicsGeometry->m_pTriangleMesh != nullptr )
            {
                pPhysicsGeometry->m_pTriangleMesh->release();
                pPhysicsGeometry->m_pTriangleMesh = nullptr;
            }
        }

        ResourceLoader::UnloadInternal( resID, pResourceRecord );
    }
}