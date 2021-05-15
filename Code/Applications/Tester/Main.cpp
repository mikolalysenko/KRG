#include "System/TypeSystem/TypeRegistry.h"
#include "Applications/Shared/ApplicationGlobalState.h"
#include "_AutoGenerated/ToolsTypeRegistration.h"
#include "Engine/Physics/PhysicsLayers.h"
#include "System/Core/FileSystem/FileSystem.h"
#include "System/Core/Serialization/JsonArchive.h"
#include "Tools/Animation/Events/AnimationEventTrackInfo.h"
#include "Tools/Core/TypeSystem/Serialization/TypeSerialization.h"
#include "Engine/Animation/Events/AnimationEvent_Footstep.h"
#include "Game/Core/TestComponent.h"

//-------------------------------------------------------------------------

using namespace KRG;
using namespace KRG::Physics;

//-------------------------------------------------------------------------


int main( int argc, char *argv[] )
{
    {
        KRG::ApplicationGlobalState State;
        TypeSystem::TypeRegistry typeRegistry;
        AutoGenerated::Tools::RegisterTypes( typeRegistry );

        //-------------------------------------------------------------------------

        Animation::Tools::EventTrackInfo trackInfo;
        trackInfo.m_isSyncTrack = true;
        trackInfo.m_eventTypeID = Animation::Events::FootstepEvent::GetStaticTypeID();

        ExternalTestStruct testStruct;
        testStruct.m_uint16 = 17;
        testStruct.m_U64 = 17;
        testStruct.m_dynamicArray[0].m_dynamicArray.emplace_back( ExternalTestSubSubStruct() );
        testStruct.m_dynamicArray[0].m_dynamicArray.emplace_back( ExternalTestSubSubStruct() );

        TypeSystem::TypeDescriptor typeDesc;
        TypeSystem::Serialization::CreateTypeDescriptorFromNativeType( typeRegistry, &testStruct, typeDesc );

        ExternalTestStruct testStruct1;
        TypeSystem::TypeCreator::CreateTypeFromDescriptor( typeRegistry, typeDesc, &testStruct1 );

        //-------------------------------------------------------------------------

        AutoGenerated::Tools::UnregisterTypes( typeRegistry );
    }

    return 0;
}