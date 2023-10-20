#pragma once
#include "MonsterState.h"

enum class eBoomShotState
{
	None,
	TakeOut,
	Shoot,
	PutBack,
};

class HeadHunterBoomShot : public MonsterState
{
public:
	HeadHunterBoomShot();
	virtual ~HeadHunterBoomShot();
	HeadHunterBoomShot(const HeadHunterBoomShot&) = delete;
	HeadHunterBoomShot& operator=(const HeadHunterBoomShot&) = delete;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Initialize() override;

	int mShootCount;
	eBoomShotState mBoomShotState;
};

