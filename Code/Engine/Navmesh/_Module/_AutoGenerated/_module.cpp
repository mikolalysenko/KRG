//-------------------------------------------------------------------------
// This is an auto-generated file - DO NOT edit
//-------------------------------------------------------------------------

#include "E:\Git\KRG\Code\Engine\Navmesh\_Module\Module.h"
#include "System/Resource/ResourceSystem.h"
#include "E:\Git\KRG\Code\Engine\Navmesh\_Module\_AutoGenerated\1360916276.cpp"
#include "E:\Git\KRG\Code\Engine\Navmesh\_Module\_AutoGenerated\2533922123.cpp"
#include "E:\Git\KRG\Code\Engine\Navmesh\_Module\_AutoGenerated\352136731.cpp"
#include "E:\Git\KRG\Code\Engine\Navmesh\_Module\_AutoGenerated\899016312.cpp"

//-------------------------------------------------------------------------

void KRG::Navmesh::EngineModule::RegisterTypes( TypeSystem::TypeRegistry& typeRegistry )
{
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshComponent>::RegisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshDebugView>::RegisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshWorldSystem>::RegisterType( typeRegistry );
}

void KRG::Navmesh::EngineModule::UnregisterTypes( TypeSystem::TypeRegistry& typeRegistry )
{
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshWorldSystem>::UnregisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshDebugView>::UnregisterType( typeRegistry );
    TypeSystem::TypeHelpers::TTypeHelper<KRG::Navmesh::NavmeshComponent>::UnregisterType( typeRegistry );
}

