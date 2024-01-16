#include "pch.h"
#include "PlayerGlobalState.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerGlobalState::PlayerGlobalState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerGlobalState::~PlayerGlobalState()
{
}

void PlayerGlobalState::InputUpdate()
{
	Assert(false, ASSERT_MSG_INVALID);
}

void PlayerGlobalState::Update()
{
	Assert(false, ASSERT_MSG_INVALID);
}

void PlayerGlobalState::Enter()
{
	Assert(false, ASSERT_MSG_INVALID);
}

void PlayerGlobalState::Exit()
{
	Assert(false, ASSERT_MSG_INVALID);
}

void PlayerGlobalState::RunToIdle()
{
	mAnimator->Play(L"RunToIdle", false);
	mOwner->ChangeState(mOwner->mPlayerIdleState);
}

bool PlayerGlobalState::IsStop()
{
	if (mRigidbody->GetVelocity().x == 0.0f &&
		mRigidbody->GetVelocity().y == 0.0f &&
		mRigidbody->IsGround())
	{
		return true;
	}

	return false;
}

bool PlayerGlobalState::IsInputMoveKey()
{
	if (gInput->GetKey(eKeyCode::W) ||
		gInput->GetKey(eKeyCode::A) ||
		gInput->GetKey(eKeyCode::D) ||
		gInput->GetKey(eKeyCode::S) ||
		gInput->GetKey(eKeyCode::LBTN) ||
		gInput->GetKeyDown(eKeyCode::W) ||
		gInput->GetKeyDown(eKeyCode::A) ||
		gInput->GetKeyDown(eKeyCode::D) ||
		gInput->GetKeyDown(eKeyCode::S) ||
		gInput->GetKeyDown(eKeyCode::LBTN))
	{
		return true;
	}

	return false;
}


Vector2 PlayerGlobalState::GetInputDirectionX()
{
	Vector2 direction = Vector2::Zero;

	if (gInput->GetKey(eKeyCode::A) || gInput->GetKeyDown(eKeyCode::A))
	{
		direction.x -=  1.0f;
	}

	if (gInput->GetKey(eKeyCode::D) || gInput->GetKeyDown(eKeyCode::D))
	{
		direction.x +=  1.0f;
	}

	return direction;
}

bool PlayerGlobalState::IsRollInput()
{
	if (gInput->GetKeyDown(eKeyCode::A) || gInput->GetKeyDown(eKeyCode::D))
	{
		if (gInput->GetKey(eKeyCode::S))
		{
			return true;
		}
	}
	else if (gInput->GetKey(eKeyCode::A) || gInput->GetKey(eKeyCode::D))
	{
		if (gInput->GetKeyDown(eKeyCode::S))
		{
			return true;
		}
	}

	return false;
}

void PlayerGlobalState::InputFlip()
{
	Vector2 dir = GetInputDirectionX();

	if (dir.x < 0)
	{
		mTransform->SetRotation(0.f, 180.f, 0.f);
	}
	else if (dir.x > 0)
	{
		mTransform->SetRotation(0.f, 0.f, 0.f);
	}
}
