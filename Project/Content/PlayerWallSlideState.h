#pragma once
#include "PlayerState.h"
class PlayerWallSlideState : public PlayerState
{
public:
	PlayerWallSlideState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerWallSlideState();

	// PlayerState��(��) ���� ��ӵ�
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;

	virtual void Initialize() override;


private:
	float gravityScale;

	float oriGravityScale;
	float oriGravityLimit;

};