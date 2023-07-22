#pragma once
#include "PlayerState.h"
class PlayerAttackState : public PlayerState
{
public:
	PlayerAttackState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerAttackState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

