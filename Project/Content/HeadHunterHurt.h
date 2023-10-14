#pragma once
#include "MonsterState.h"

enum class eHurtState
{
	None,
	Hirt,
	HurtFly,
	HurtGround,
	TelportShotReady,
};

class HeadHunterHurt : public MonsterState
{
public:
	HeadHunterHurt();
	virtual ~HeadHunterHurt();
	HeadHunterHurt(const HeadHunterHurt&) = delete;
	HeadHunterHurt& operator=(const HeadHunterHurt&) = delete;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	eHurtState mHurtState;
	float mHurtTime;
};

