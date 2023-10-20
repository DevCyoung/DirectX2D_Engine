#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "BasicMonsterAI.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ShieldCop);

class ShieldCop : public BasicMonsterAI
{
public:
	ShieldCop();
	virtual ~ShieldCop();
	ShieldCop(const ShieldCop&) = delete;
	ShieldCop& operator=(const ShieldCop&) = delete;

	virtual void aim() override;

	// BasicMonsterAI��(��) ���� ��ӵ�
	virtual void CreateAnimation(Scene* scene) override;
	virtual void CreateGun(Scene* scene) override;
};
