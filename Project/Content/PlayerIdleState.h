#pragma once
#include "PlayerState.h"
class PlayerFSM;

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerIdleState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

