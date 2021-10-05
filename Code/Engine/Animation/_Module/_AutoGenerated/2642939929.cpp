//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "d:\Kruger\Code\Engine\Animation\_Module\_AutoGenerated\2642939929.h"

//-------------------------------------------------------------------------
// TypeHelper: KRG::Animation::AnimationComponent
//-------------------------------------------------------------------------

namespace KRG
{
    TypeSystem::TypeInfo const* KRG::Animation::AnimationComponent::s_pTypeInfo = nullptr;
    namespace TypeSystem
    {
        namespace TypeHelpers
        {
            IRegisteredType const* TTypeHelper<KRG::Animation::AnimationComponent>::s_pDefaultTypeInstancePtr = nullptr;

            TTypeHelper<KRG::Animation::AnimationComponent> TTypeHelper<KRG::Animation::AnimationComponent>::StaticTypeHelper;
        }
    }

    void KRG::Animation::AnimationComponent::Load( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        m_status = Status::Loaded;
    }

    void KRG::Animation::AnimationComponent::Unload( EntityModel::LoadingContext const& context, UUID requesterID )
    {
        m_status = Status::Unloaded;
    }

    void KRG::Animation::AnimationComponent::UpdateLoading()
    {
        if( m_status == Status::Loading )
        {
            m_status = EntityComponent::Status::Loaded;
        }
    }
}
