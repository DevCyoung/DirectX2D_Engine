#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(AxeMovement);

enum class eAxeMovementState
{
	None,
	Idle,
	Throw,
	Return,
	Rotation,
};

class AxeMovement : public ScriptComponent
{
public:
	AxeMovement();
	virtual ~AxeMovement();
	AxeMovement(const AxeMovement&) = delete;
	AxeMovement& operator=(const AxeMovement&) = delete;

	void SetStoop(bool bStoop) { mbStoop = bStoop; }
	bool IsStoop() const { return mbStoop; }

	void SetState(eAxeMovementState state) { mState = state; }	

	void SetKissyfaace(GameObject* const kissyface) { Assert(kissyface, ASSERT_MSG_NULL); mKissyface = kissyface; }
	void SetRotationDistance(float rotationDistance) { mRotationDistance = rotationDistance; }


private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;


	virtual void onCollisionEnter(Collider2D* other) override;


	bool mbStoop;
	int mRotationCount;
	eAxeMovementState mState;
	GameObject* mKissyface;
	float mRotationDistance;
};
