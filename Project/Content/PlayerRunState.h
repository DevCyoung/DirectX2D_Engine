#pragma once
#include "PlayerState.h"

class PlayerRunState : public PlayerState
{
public:
	PlayerRunState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerRunState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

