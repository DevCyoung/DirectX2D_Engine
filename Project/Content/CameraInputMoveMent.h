#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CameraInputMoveMent);

class CameraInputMoveMent : public ScriptComponent
{
public:
	CameraInputMoveMent();
	virtual ~CameraInputMoveMent();
	//CameraInputMoveMent(const CameraInputMoveMent&) = delete;
	CameraInputMoveMent& operator=(const CameraInputMoveMent&) = delete;

	CLONE(CameraInputMoveMent)
private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
