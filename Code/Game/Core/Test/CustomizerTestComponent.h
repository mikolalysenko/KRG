#pragma once

#include "../_Module/API.h"
#include "System/TypeSystem/TypeRegistrationMacros.h"
#include "System/Entity/EntityComponent.h"
#include "System/Core/Types/Color.h"
#include "System/Core/Math/Transform.h"
#include "System/Resource/ResourcePtr.h"

//-------------------------------------------------------------------------

namespace KRG
{
    class KRG_GAME_CORE_API CustomizerTestComponent : public EntityComponent
    {
        KRG_REGISTER_ENTITY_COMPONENT;

        friend class CustomizerTestSystem;

    public:

        CustomizerTestComponent() = default;

    protected:

        EXPOSE TVector<ResourceID>  m_meshIDs;
        EXPOSE TVector<ResourceID>  m_armorMeshIDs;
        EXPOSE TVector<ResourceID>  m_hairMeshIDs;
        EXPOSE TVector<ResourceID>  m_materialIDs;
        EXPOSE TVector<ResourceID>  m_animationIDs;
        EXPOSE ResourceID           m_skeletonID;
    };
}