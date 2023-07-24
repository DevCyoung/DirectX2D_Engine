#pragma once
#include "PlayerState.h"
class PlayerDoorBreakFullState : public PlayerState
{
public:
	PlayerDoorBreakFullState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerDoorBreakFullState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

