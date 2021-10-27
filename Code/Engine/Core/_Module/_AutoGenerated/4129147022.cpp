//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Core\_Module\_AutoGenerated\4129147022.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::EntityComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::EntityComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::EntityComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::EntityComponent> TTypeHelper<KRG::EntityComponent>::StaticTypeHelper;
        }
    }

    void KRG::EntityComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        m_status = Status::Loaded;
    }

    void KRG::EntityComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        m_status = Status::Unloaded;
    }

    void KRG::EntityComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            m_status = EntityComponent::Status::Loaded;
        }
    }
}
