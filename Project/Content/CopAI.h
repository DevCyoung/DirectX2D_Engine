#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "BasicMonsterAI.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CopAI);

class CopAI : public BasicMonsterAI
{
public:
	CopAI();
	virtual ~CopAI();
	CopAI(const CopAI&) = delete;
	CopAI& operator=(const CopAI&) = delete;	

	// BasicMonsterAI��(��) ���� ��ӵ�
	virtual void CreateAnimation(Scene* scene) override;
	virtual void CreateGun(Scene* scene) override;
};
