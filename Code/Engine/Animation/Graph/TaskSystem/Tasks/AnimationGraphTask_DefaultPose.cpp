#include "AnimationGraphTask_DefaultPose.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph::Tasks
{
    DefaultPoseTask::DefaultPoseTask( NodeIndex sourceNodeIdx, Pose::InitialState type )
        : Task( sourceNodeIdx )
        , m_type( type )
    {}

    void DefaultPoseTask::Execute( TaskContext const& context )
    {
        auto pResultBuffer = GetNewPoseBuffer( context );
        pResultBuffer->m_pose.Reset( m_type );
        MarkTaskComplete( context );
    }
}