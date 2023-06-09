#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(BulletMovement);

class BulletMovement : public ScriptComponent
{
public:
	BulletMovement();
	virtual ~BulletMovement();
	BulletMovement(const BulletMovement&) = delete;
	BulletMovement& operator=(const BulletMovement&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

private:
	float mDelay;
};
