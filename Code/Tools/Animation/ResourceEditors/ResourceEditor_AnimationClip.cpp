#include "ResourceEditor_AnimationClip.h"
#include "Tools/Animation/Events/AnimationEventEditor.h"
#include "Engine/Animation/AnimationPose.h"
#include "Engine/Animation/Components/AnimationPlayerComponent.h"
#include "Engine/Animation/Systems/AnimationSystem.h"
#include "Engine/Animation/Components/AnimatedMeshComponent.h"
#include "Engine/Core/Entity/EntityWorld.h"
#include "System/Imgui/Widgets/InterfaceHelpers.h"
#include "System/Core/Math/MathStringHelpers.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    KRG_RESOURCE_WORKSPACE_FACTORY( AnimationClipWorkspaceFactory, AnimationClip, AnimationClipResourceEditor );

    //-------------------------------------------------------------------------

    char const* const AnimationClipResourceEditor::s_timelineWindowName = "Timeline##AnimationClip";
    char const* const AnimationClipResourceEditor::s_detailsWindowName = "Details##AnimationClip";
    char const* const AnimationClipResourceEditor::s_trackDataWindowName = "Track Data##AnimationClip";

    //-------------------------------------------------------------------------

    AnimationClipResourceEditor::AnimationClipResourceEditor( EditorModel* pModel, ResourceID const& resourceID )
        : TResourceEditorWorkspace<AnimationClip>( pModel, resourceID )
        , m_propertyGrid( *pModel->GetTypeRegistry(), pModel->GetSourceDataDirectory() )
    {}

    AnimationClipResourceEditor::~AnimationClipResourceEditor()
    {
        if ( m_pEventEditor != nullptr )
        {
            KRG::Delete( m_pEventEditor );
        }
    }

    void AnimationClipResourceEditor::Activate( EntityWorld* pPreviewWorld )
    {
        KRG_ASSERT( m_pPreviewEntity == nullptr );

        // We dont own the entity as soon as we add it to the map
        auto pPersistentMap = pPreviewWorld->GetPersistentMap();

        m_pPreviewEntity = KRG::New<Entity>( StringID( "Preview" ) );
        pPersistentMap->AddEntity( m_pPreviewEntity );

        m_pPreviewEntity->CreateSystem<AnimationSystem>();

        m_pAnimationComponent = KRG::New<AnimationPlayerComponent>( StringID( "Animation Component" ) );
        m_pAnimationComponent->SetAnimation( m_pResource.GetResourceID() );
        m_pPreviewEntity->AddComponent( m_pAnimationComponent );
    }

    void AnimationClipResourceEditor::Deactivate( EntityWorld* pPreviewWorld )
    {
        KRG_ASSERT( m_pPreviewEntity != nullptr );

        auto pPersistentMap = pPreviewWorld->GetPersistentMap();
        pPersistentMap->DestroyEntity( m_pPreviewEntity->GetID() );
        m_pPreviewEntity = nullptr;
        m_pAnimationComponent = nullptr;
    }

    void AnimationClipResourceEditor::InitializeDockingLayout( ImGuiID dockspaceID ) const
    {
        ImGuiID topDockID = 0;
        ImGuiID bottomLeftDockID = 0;
        ImGuiID bottomDockID = ImGui::DockBuilderSplitNode( dockspaceID, ImGuiDir_Down, 0.5f, nullptr, &topDockID );
        ImGuiID bottomRightDockID = ImGui::DockBuilderSplitNode( bottomDockID, ImGuiDir_Right, 0.25f, nullptr, &bottomLeftDockID );

        // Dock viewport
        ImGuiDockNode* pTopNode = ImGui::DockBuilderGetNode( topDockID );
        pTopNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingSplitMe | ImGuiDockNodeFlags_NoDockingOverMe;
        ImGui::DockBuilderDockWindow( GetViewportWindowName(), topDockID );

        // Dock windows
        ImGui::DockBuilderDockWindow( s_timelineWindowName, bottomLeftDockID );
        ImGui::DockBuilderDockWindow( s_trackDataWindowName, bottomRightDockID );
        ImGui::DockBuilderDockWindow( s_detailsWindowName, bottomRightDockID );
    }

    void AnimationClipResourceEditor::UpdateAndDraw( UpdateContext const& context, Render::ViewportManager& viewportManager, ImGuiWindowClass* pWindowClass )
    {
        if ( IsLoaded() )
        {
            // Lazy init of the event editor
            if ( m_pEventEditor == nullptr )
            {
                m_pEventEditor = KRG::New<EventEditor>( *m_pModel->GetTypeRegistry(), m_pModel->GetSourceDataDirectory(), m_pResource.GetPtr() );
            }

            if ( m_pMeshComponent == nullptr )
            {
                m_pMeshComponent = KRG::New<AnimatedMeshComponent>( StringID( "Mesh Component" ) );
                m_pMeshComponent->SetSkeleton( m_pAnimationComponent->GetSkeleton()->GetResourceID() );
                m_pMeshComponent->SetMesh( "data://ue_mann_anim/run_fwd.smsh" );
                //m_pMeshComponent->SetMesh( "data://packs/br/characters/sk_chr_70sfemale_01.smsh" );
                m_pPreviewEntity->AddComponent( m_pMeshComponent );
            }

            // Update position
            //-------------------------------------------------------------------------

            if ( m_isRootMotionEnabled )
            {
                m_characterTransform = m_pResource->GetRootTransform( m_pAnimationComponent->GetAnimTime() );
            }
            else
            {
                m_characterTransform = Transform::Identity;
            }

            // Draw in viewport
            //-------------------------------------------------------------------------

            auto drawingCtx = context.GetDrawingContext();

            Pose const* pPose = m_pAnimationComponent->GetPose();
            if ( pPose != nullptr )
            {
                drawingCtx.Draw( *pPose, m_characterTransform );
            }

            m_pResource->DrawRootMotionPath( drawingCtx, Transform::Identity );
        }

        //-------------------------------------------------------------------------

        DrawTimelineWindow( context, viewportManager, pWindowClass );
        DrawTrackDataWindow( context, viewportManager, pWindowClass );
        DrawDetailsWindow( context, viewportManager, pWindowClass );
    }

    void AnimationClipResourceEditor::DrawViewportToolbar( UpdateContext const& context, Render::ViewportManager& viewportManager )
    {
        if ( !IsLoaded() )
        {
            return;
        }

        //-------------------------------------------------------------------------

        ImGui::AlignTextToFramePadding();
        ImGui::Text( "Frame: %06.2f / %d", m_pEventEditor->GetPlayheadPositionAsPercentage().ToFloat() * m_pResource->GetNumFrames(), m_pResource->GetNumFrames() );

        ImGuiX::VerticalSeparator();

        ImGui::Text( "Time: %05.2fs / %05.2fs", m_pEventEditor->GetPlayheadPositionAsPercentage().ToFloat() * m_pResource->GetDuration(), m_pResource->GetDuration().ToFloat() );

        ImGuiX::VerticalSeparator();

        ImGui::Text( "Avg Linear Velocity: %.2fm/s", m_pResource->GetAverageLinearVelocity() );

        ImGuiX::VerticalSeparator();

        ImGui::Text( "Avg Angular Velocity: %.2fm/s", m_pResource->GetAverageAngularVelocity().ToFloat() );

        ImGuiX::VerticalSeparator();

        ImGui::Text( "Distance Covered: %.2fm", m_pResource->GetTotalRootMotionDelta().GetTranslation().GetLength3() );

        ImGuiX::VerticalSeparator();

        ImGui::Checkbox( "Root Motion", &m_isRootMotionEnabled );
    }

    void AnimationClipResourceEditor::DrawTimelineWindow( UpdateContext const& context, Render::ViewportManager& viewportManager, ImGuiWindowClass* pWindowClass )
    {
        ImGui::SetNextWindowClass( pWindowClass );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );
        if ( ImGui::Begin( s_timelineWindowName ) )
        {
            if ( IsWaitingForResource() )
            {
                ImGui::Text( "Loading:" );
                ImGui::SameLine();
                ImGuiX::DrawSpinner( "Loading" );
            }
            else if ( HasLoadingFailed() )
            {
                ImGui::Text( "Loading Failed: %s", m_pResource.GetResourceID().c_str() );
            }
            else
            {
                // Track editor and property grid
                //-------------------------------------------------------------------------

                m_pEventEditor->Update( context, m_pAnimationComponent );

                auto const& selectedItems = m_pEventEditor->GetSelectedItems();
                if ( !selectedItems.empty() )
                {
                    auto pAnimEventItem = static_cast<EventItem*>( selectedItems.back() );
                    m_propertyGrid.SetTypeToEdit( pAnimEventItem->GetEvent() );
                }
                else // Clear property grid
                {
                    m_propertyGrid.SetTypeToEdit( nullptr );
                }
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void AnimationClipResourceEditor::DrawDetailsWindow( UpdateContext const& context, Render::ViewportManager& viewportManager, ImGuiWindowClass* pWindowClass )
    {
        ImGui::SetNextWindowClass( pWindowClass );
        if ( ImGui::Begin( s_detailsWindowName ) )
        {
            m_propertyGrid.DrawGrid();
        }
        ImGui::End();
    }

    void AnimationClipResourceEditor::DrawTrackDataWindow( UpdateContext const& context, Render::ViewportManager& viewportManager, ImGuiWindowClass* pWindowClass )
    {
        ImGui::SetNextWindowClass( pWindowClass );
        if ( ImGui::Begin( s_trackDataWindowName ) )
        {
            if ( IsLoaded() )
            {
                // There may be a frame delay between the UI and the entity system creating the pose
                Pose const* pPose = m_pAnimationComponent->GetPose();
                if ( pPose != nullptr )
                {
                    if ( ImGui::BeginTable( "TrackDataTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg ) )
                    {
                        ImGui::TableSetupColumn( "Bone", ImGuiTableColumnFlags_WidthStretch );
                        ImGui::TableSetupColumn( "Transform", ImGuiTableColumnFlags_WidthStretch );
                        ImGui::TableHeadersRow();

                        //-------------------------------------------------------------------------

                        Transform const rootTransform = m_isRootMotionEnabled ? m_pResource->GetRootTransform( m_pAnimationComponent->GetAnimTime() ) : Transform::Identity;

                        ImGui::TableNextColumn();
                        ImGui::Text( "0. Root" );

                        ImGui::TableNextColumn();
                        ImGui::Text( "Rot: %s", Math::ToString( rootTransform.GetRotation() ).c_str() );
                        ImGui::Text( "Tra: %s", Math::ToString( rootTransform.GetTranslation() ).c_str() );
                        ImGui::Text( "Scl: %s", Math::ToString( rootTransform.GetScale() ).c_str() );

                        //-------------------------------------------------------------------------

                        Skeleton const* pSkeleton = pPose->GetSkeleton();
                        int32 const numBones = pSkeleton->GetNumBones();

                        for ( auto i = 1; i < numBones; i++ )
                        {
                            Transform const& boneTransform = pPose->GetGlobalTransform( i );

                            ImGui::TableNextColumn();
                            ImGui::Text( "%d. %s", i, pSkeleton->GetBoneID( i ).c_str() );

                            ImGui::TableNextColumn();
                            ImGui::Text( "Rot: %s", Math::ToString( boneTransform.GetRotation() ).c_str() );
                            ImGui::Text( "Tra: %s", Math::ToString( boneTransform.GetTranslation() ).c_str() );
                            ImGui::Text( "Scl: %s", Math::ToString( boneTransform.GetScale() ).c_str() );
                        }

                        ImGui::EndTable();
                    }
                }
            }
            else
            {
                ImGui::Text( "Nothing to show!" );
            }
        }
        ImGui::End();
    }

    bool AnimationClipResourceEditor::IsDirty() const
    {
        return ( m_pEventEditor != nullptr ) ? m_pEventEditor->IsDirty() : false;
    }

    bool AnimationClipResourceEditor::OnSave()
    {
        if ( m_pEventEditor != nullptr )
        {
            return m_pEventEditor->RequestSave();
        }

        return false;
    }
}