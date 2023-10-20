#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "BasicMonsterAI.h"

REGISTER_SCRIPTCOMPONENT_TYPE(GangsterAI);

class GangsterAI : public BasicMonsterAI
{
public:
	GangsterAI();
	virtual ~GangsterAI();
	GangsterAI(const GangsterAI&) = delete;
	GangsterAI& operator=(const GangsterAI&) = delete;

	// BasicMonsterAI��(��) ���� ��ӵ�
	virtual void CreateAnimation(Scene* scene) override;
	virtual void CreateGun(Scene* scene) override;
};
