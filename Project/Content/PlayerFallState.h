#pragma once
#include "PlayerState.h"
class PlayerFallState : public PlayerState
{
public:
	PlayerFallState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerFallState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;

};

