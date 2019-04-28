#pragma once

#include <Urho3D/Engine/Application.h>

namespace Urho3D
{
class Node;
class Scene;
class AView;
}

using namespace Urho3D;

//
// for eye candy-ization only 
//
#include <Urho3D/Scene/LogicComponent.h>

/// Custom logic component for rotating a scene node. From Urho3D samples
class Rotator : public LogicComponent
{
    URHO3D_OBJECT(Rotator, LogicComponent);

public:
    Rotator(Context* context); /// Construct.
    void SetRotationSpeed(const Vector3& speedxyz); /// Set rotation speed about the Euler axes. Will be scaled with scene update time step.
    virtual void Update(float timeStep) override;  /// Handle scene update. Called by LogicComponent base class.
    const Vector3& GetRotationSpeed() const
    {
        return rotationSpeed_;    /// Return rotation speed.
    }
private:
    Vector3 rotationSpeed_;  /// Rotation speed.
};

