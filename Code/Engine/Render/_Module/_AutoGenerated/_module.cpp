//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Render\_Module\Module.h"
#include "System/Resource/ResourceSystem.h"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\1144792658.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\2388998025.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\2754915885.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\3288576307.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\339520260.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\717744412.cpp"
#include "E:\Git\KRG\Code\Engine\Render\_Module\_AutoGenerated\734570957.cpp"

//-------------------------------------------------------------------------

void KRG::Render::EngineModule::RegisterTypes( TypeSystem::TypeRegistry& typeRegistry )
{
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::MeshComponent>::RegisterType( typeRegistry );
    TypeSystem::EnumHelpers::EnumHelper_KRG_Render_Mobility::RegisterEnum( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::StaticMeshComponent>::RegisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::SkeletalMeshComponent>::RegisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::WorldRendererSystem>::RegisterType( typeRegistry );
}

void KRG::Render::EngineModule::UnregisterTypes( TypeSystem::TypeRegistry& typeRegistry )
{
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::WorldRendererSystem>::UnregisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::SkeletalMeshComponent>::UnregisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::StaticMeshComponent>::UnregisterType( typeRegistry );
    TypeSystem::EnumHelpers::EnumHelper_KRG_Render_Mobility::UnregisterEnum( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Render::MeshComponent>::UnregisterType( typeRegistry );
}

