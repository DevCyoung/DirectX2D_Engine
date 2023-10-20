#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "BasicMonsterAI.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ShotGunAI);

class ShotGunAI : public BasicMonsterAI
{
public:
	ShotGunAI();
	virtual ~ShotGunAI();
	ShotGunAI(const ShotGunAI&) = delete;
	ShotGunAI& operator=(const ShotGunAI&) = delete;

	// BasicMonsterAI��(��) ���� ��ӵ�
	virtual void CreateAnimation(Scene* scene) override;
	virtual void CreateGun(Scene* scene) override;
};
