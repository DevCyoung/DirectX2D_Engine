#pragma once
#include "MonsterState.h"
class HeadHunterIdle : public MonsterState
{
public:
	HeadHunterIdle();
	virtual ~HeadHunterIdle();
	HeadHunterIdle(const HeadHunterIdle&) = delete;
	HeadHunterIdle& operator=(const HeadHunterIdle&) = delete;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	// MonsterState��(��) ���� ��ӵ�
	virtual void Initialize() override;

	int prevRand;
};

