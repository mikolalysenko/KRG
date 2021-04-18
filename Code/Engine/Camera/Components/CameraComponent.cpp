#include "CameraComponent.h"

//-------------------------------------------------------------------------

namespace KRG::Camera
{
    void CameraComponent::Initialize()
    {
        SpatialEntityComponent::Initialize();
        m_viewVolume = Math::ViewVolume( Float2( 1.0f ), TRange<float>( 0.1f, m_depth ), Radians( m_FOV ), GetWorldTransform().ToMatrix() );

        // Decompose current view into heading and pitch
        //-------------------------------------------------------------------------

        auto currentRotation = GetLocalTransform().ToEulerAngles();
        m_heading = currentRotation.m_z;
        m_pitch = currentRotation.m_x;
    }

    //-------------------------------------------------------------------------

    void CameraComponent::AdjustHeadingAndPitch( Radians headingDelta, Radians pitchDelta )
    {
        // Adjust heading and pitch based on input
        m_heading += headingDelta;
        m_heading.ClampToPositive();

        m_pitch += pitchDelta;
        m_pitch.ClampToPositive();

        auto const rotZ = Quaternion( Float3::UnitZ, m_heading );
        auto const rotX = Quaternion( Float3::UnitX, m_pitch );
        auto const rotTotal = rotX * rotZ;

        Transform localTransform = GetLocalTransform();
        localTransform.SetRotation( rotTotal );
        SetLocalTransform( localTransform );
    }

    void CameraComponent::OnWorldTransformUpdated()
    {
        m_viewVolume.SetWorldMatrix( GetWorldTransform().ToMatrix() );
    }

    Math::ViewVolume const& CameraComponent::CalculateViewVolume( Float2 const& viewDimensions )
    {
        m_viewVolume.SetViewDimensions( viewDimensions );
        return m_viewVolume;
    }
}