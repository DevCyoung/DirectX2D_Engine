#pragma once
#include "MonsterState.h"

enum class eTeleportState
{
	None,
	In,
	Out,	
};

class HeadHunterTeleport : public MonsterState
{

public:
	HeadHunterTeleport();
	virtual ~HeadHunterTeleport();
	HeadHunterTeleport(const HeadHunterTeleport&) = delete;
	HeadHunterTeleport& operator=(const HeadHunterTeleport&) = delete;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	void Shot();

private:
	eTeleportState  mTeleportState;
	int             mAttackCount;
};

