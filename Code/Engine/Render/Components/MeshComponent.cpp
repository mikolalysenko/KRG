#include "MeshComponent.h"

//-------------------------------------------------------------------------

namespace KRG::Render
{
    void MeshComponent::Initialize()
    {
        SpatialEntityComponent::Initialize();
        UpdateMaterialCache();
    }

    void MeshComponent::Shutdown()
    {
        m_materials.clear();
        SpatialEntityComponent::Shutdown();
    }

    void MeshComponent::SetMaterialOverride( int32 materialIdx, ResourceID materialResourceID )
    {
        KRG_ASSERT( IsUnloaded() );
        KRG_ASSERT( materialResourceID.IsValid() );

        if ( materialIdx >= m_materialOverrides.size() )
        {
            m_materialOverrides.resize( materialIdx + 1 );
            m_materialOverrides[materialIdx] = materialResourceID;
        }
    }

    void MeshComponent::UpdateMaterialCache()
    {
        auto const& defaultMaterials = GetDefaultMaterials();
        size_t const numMaterials = defaultMaterials.size();
        size_t const numMaterialOverrides = m_materialOverrides.size();

        m_materials.resize( numMaterials );

        for ( size_t i = 0; i < numMaterials; i++ )
        {
            if ( i < numMaterialOverrides )
            {
                if ( m_materialOverrides[i].IsValid() )
                {
                    KRG_ASSERT( m_materialOverrides[i].IsLoaded() );
                    m_materials[i] = m_materialOverrides[i].GetPtr();
                }
                else
                {
                    m_materials[i] = nullptr;
                }
            }
            else // Use default material
            {
                if ( defaultMaterials[i].IsValid() )
                {
                    KRG_ASSERT( defaultMaterials[i].IsLoaded() );
                    m_materials[i] = defaultMaterials[i].GetPtr();
                }
                else
                {
                    m_materials[i] = nullptr;
                }
            }
        }
    }
}