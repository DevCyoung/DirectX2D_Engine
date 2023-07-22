#pragma once
#include "PlayerState.h"

class PlayerRollState : public PlayerState
{
public:
	PlayerRollState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerRollState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

