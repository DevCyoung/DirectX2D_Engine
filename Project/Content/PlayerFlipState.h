#pragma once
#include "PlayerState.h"
class PlayerFlipState : public PlayerState
{
public:
	PlayerFlipState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerFlipState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

