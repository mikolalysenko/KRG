#include "AnimationGraphTask.h"

//-------------------------------------------------------------------------

namespace KRG::Animation::Graph
{
    Task::Task( NodeIndex sourceNodeIdx, UpdateStage updateRequirements, TaskDependencies const& dependencies )
        : m_sourceNodeIdx( sourceNodeIdx )
        , m_updateStage( updateRequirements )
        , m_dependencies( dependencies )
    {
        KRG_ASSERT( sourceNodeIdx != InvalidIndex );
    }
}