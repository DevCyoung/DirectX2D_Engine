#pragma once
#include "PlayerState.h"

class PlayerHurtState : public PlayerState
{
public:
	PlayerHurtState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerHurtState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;

public:
	Vector2 mDirection;
	float mEffectTime;
};

