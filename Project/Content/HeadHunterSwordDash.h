#pragma once
#include "MonsterState.h"

enum class eSwordDashState
{
	None,
	PreDash,
	Dash,
	DashEndGround,
};

class HeadHunterSwordDash : public MonsterState
{
public:
	HeadHunterSwordDash();
	virtual ~HeadHunterSwordDash();
	HeadHunterSwordDash(const HeadHunterSwordDash&) = delete;
	HeadHunterSwordDash& operator=(const HeadHunterSwordDash&) = delete;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Initialize() override;

	eSwordDashState mSwordDashState;
	float mDashTime;
	bool mbLeft;
};

