#include "pch.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "Rect2DInterpolation.h"
#include "GameObjectBuilder.h"
#include <Engine/Physics2D.h>
#include <Engine/EngineMath.h>
#include <Engine/SceneManager.h>

PlayerFSM::PlayerFSM(GameObject* const owner)
	: mOwner(owner)
	, mRect2DInterpolation(nullptr)
	, mRigidbody2D(nullptr)
	, mAnimator2D(nullptr)
	, mVelocity(Vector3::Zero)
	, mPlayerIdleState(new PlayerIdleState(owner, this))
	, mPlayerRunState(new PlayerRunState(owner, this))
	, mPlayerAttackState(new PlayerAttackState(owner, this))
	, mPlayerRollState(new PlayerRollState(owner, this))
	, mPlayerCrouchState(new PlayerCrouchState(owner, this))
	, mPlayerJumpState(new PlayerJumpState(owner, this))
	, mPlayerFallState(new PlayerFallState(owner, this))
	, mPlayerDoorBreakFullState(new PlayerDoorBreakFullState(owner, this))
	, mPlayerDoorState(new PlayerDoorState(owner, this))
	, mPlayerFlipState(new PlayerFlipState(owner, this))
	, mPlayerWallSlideState(new PlayerWallSlideState(owner, this))
	, mPlayerGlobalState(new PlayerGlobalState(owner, this))
	, mPlayerRecoverState(new PlayerRecoverState(owner, this))
	, mPlayerHurtGroundState(new PlayerHurtGroundState(owner, this))
	, mPlayerHurtState(new PlayerHurtState(owner, this))
{
	mCurState = mPlayerIdleState;
}

PlayerFSM::~PlayerFSM()
{
	DELETE_POINTER_NOT_NULL(mPlayerIdleState);
	DELETE_POINTER_NOT_NULL(mPlayerRunState);
	DELETE_POINTER_NOT_NULL(mPlayerAttackState);
	DELETE_POINTER_NOT_NULL(mPlayerRollState);
	DELETE_POINTER_NOT_NULL(mPlayerCrouchState);
	DELETE_POINTER_NOT_NULL(mPlayerJumpState);
	DELETE_POINTER_NOT_NULL(mPlayerFallState);
	DELETE_POINTER_NOT_NULL(mPlayerDoorBreakFullState);
	DELETE_POINTER_NOT_NULL(mPlayerDoorState);
	DELETE_POINTER_NOT_NULL(mPlayerFlipState);
	DELETE_POINTER_NOT_NULL(mPlayerWallSlideState);
	DELETE_POINTER_NOT_NULL(mPlayerGlobalState);
	DELETE_POINTER_NOT_NULL(mPlayerRecoverState);
	DELETE_POINTER_NOT_NULL(mPlayerHurtGroundState);
	DELETE_POINTER_NOT_NULL(mPlayerHurtState);

}

//FIXME: 모든 state Initialize 추가해줘야함
void PlayerFSM::Initialize(PlayerState* const startState)
{
	mRect2DInterpolation = mOwner->GetComponent<Rect2DInterpolation>();
	mRigidbody2D = mOwner->GetComponent<Rigidbody2D>();
	mAnimator2D = mOwner->GetComponent<Animator2D>();

	mPlayerIdleState->Initialize();
	mPlayerRunState->Initialize();
	mPlayerAttackState->Initialize();
	mPlayerRollState->Initialize();
	mPlayerCrouchState->Initialize();
	mPlayerJumpState->Initialize();
	mPlayerFallState->Initialize();
	mPlayerDoorBreakFullState->Initialize();
	mPlayerDoorState->Initialize();
	mPlayerFlipState->Initialize();
	mPlayerWallSlideState->Initialize();
	mPlayerGlobalState->Initialize();
	mPlayerRecoverState->Initialize();
	mPlayerHurtGroundState->Initialize();
	mPlayerHurtState->Initialize();


	mCurState = startState;
	mCurState->Enter();
}

void PlayerFSM::GlobalUpdate()
{
	if (gInput->GetKeyDown(eKeyCode::RBTN))
	{
		/*if (mCurState == mPlayerHurtGroundState)
		{
			ChangeState(mPlayerRecoverState);
		}
		else
		{
			ChangeState(mPlayerHurtGroundState);
		}*/
		
	}
	else if (CanChagneToAttackState())
	{
		ChangeState(mPlayerAttackState);
	}
	else if (CanChagneToJumpState())
	{
		ChangeState(mPlayerJumpState);
	}
	else if (CanChagneToRunState())
	{
		mAnimator2D->Play(L"IdleToRun", false);
		ChangeState(mPlayerRunState);
	}
	else if (CanChagneToWallSlideState())
	{
		//nChagneToWallSlideState();
		ChangeState(mPlayerWallSlideState);
	}
	else if (CanChagneToFallState())
	{
		ChangeState(mPlayerFallState);
	}


}

void PlayerFSM::InputUpdate()
{
	//if (gInput->GetKeyDown(eKeyCode::RBTN))
	//{
	//	Camera* mainCamera = mOwner->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
	//	Vector3 mousePos = helper::WindowScreenMouseToWorld3D(mainCamera);
	//	Vector3 playerPos = mOwner->GetComponent<Transform>()->GetPosition();
	//	Vector3 dir = mousePos - mOwner->GetComponent<Transform>()->GetPosition();
	//	dir.z = 0.f;	
	//	dir.Normalize();

	//	GameObject* bullet = GameObjectBuilder::CreateBullet(dir, playerPos, eBulletType::PlayerBeer1);
	//	mOwner->GetGameSystem()->GetScene()->RegisterEventAddGameObject(bullet, eLayerType::Bullet);
	//}

	mCurState->InputUpdate();
}

void PlayerFSM::Update()
{
	mCurState->Update();

	//return
	if (mOwner->GetComponent<PlayerController>()->IsControl() == false)
	{
		return;
	}

	{
		Transform* const transform = mOwner->GetComponent<Transform>();
		//RenderTargetRenderer* const renderer = mOwner->GetGameSystem()->GetRenderTargetRenderer();
		//DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer2D();

		Vector3 pos = transform->GetPosition();
		Matrix mat = transform->GetComponent<RectCollider2D>()->GetColliderWorldMatrix();

		Vector3 lp = Vector3(-0.5f, -0.5f, 0.f);
		lp = XMVector3TransformCoord(lp, mat);

		pos = lp;

		pos.y += 10.f;

		//

		RayCast2DHitInfo info = {};

		//Physics2D* const physics2D = mOwner->GetGameSystem()->GetPhysics2D();
		Vector2 lp2 = Vector2(pos.x, pos.y);
		Vector2 direction = Vector2::Down;

		//bool rs = physics2D->RayCastHit2D(lp2, Vector2::Down, 100.f, eLayerType::Slope, &info);
		//
		//if (rs)
		//{
		//	debugRenderer->DrawLine2D2(pos, Vector2::Down, 100.f, 0.f, Vector4(1.f, 0.f, 0.f, 1.f));
		//}
		//else
		//{
		//	debugRenderer->DrawLine2D2(pos, Vector2::Down, 100.f, 0.f, Vector4(1.f, 1.f, 1.f, 1.f));
		//}


		Rigidbody2D* const rigidbody2D = mOwner->GetComponent<Rigidbody2D>();
		const Vector2 dir = mPlayerGlobalState->GetInputDirectionX();
		Vector2 right = Vector2::Right;




		if (mCurState != mPlayerRollState)
		{
			//LeftWall, RightWall 구분해야함
			if (mRect2DInterpolation->IsCollisionWallSlop() &&
				mRect2DInterpolation->IsCollisionWallFloor() == false)
			{
				right = Vector2(cos(Deg2Rad(45)), 0.f);


				if (rigidbody2D->GetVelocity().x > 0.f)
				{
					right.y = -sin(Deg2Rad(45));
				}

			}

			float speed = 400.f;

			if (abs(rigidbody2D->GetVelocity().x) < right.x * speed)
			{
				rigidbody2D->AddForce(right * dir.x * 4000.f);
			}
			else if (gInput->GetKeyDown(eKeyCode::A) || gInput->GetKeyDown(eKeyCode::D))
			{
				Vector2 newVelocity = right * dir.x * speed;
				if (mRect2DInterpolation->IsCollisionWallLeft() || mRect2DInterpolation->IsCollisionWallRight())
				{
					newVelocity.y = -600.f;
				}
				rigidbody2D->SetVelocity(newVelocity);
			}

		}

		

	}



	if (gInput->GetKey(eKeyCode::S) || mCurState == mPlayerAttackState)
	{
		if (mCurState != mPlayerRollState)
		{
			mRect2DInterpolation->TurnOffPlatform();
		}

	}
	else
	{
		mRect2DInterpolation->TurnOnPlatform();
	}


}

bool PlayerFSM::CanChagneToAttackState() const
{
	return gInput->GetKeyDown(eKeyCode::LBTN) && mCurState != mPlayerAttackState;
}

bool PlayerFSM::CanChagneToFallState() const
{
	if (mCurState == mPlayerFallState ||
		mCurState == mPlayerWallSlideState ||
		mCurState == mPlayerAttackState ||
		mCurState == mPlayerFlipState || 
		mCurState == mPlayerRollState)
	{
		return false;
	}

	if (mRigidbody2D->GetVelocity().y >= 0.f || mRigidbody2D->IsGround())
	{
		return false;
	}

	return true;
}

bool PlayerFSM::CanChagneToJumpState() const
{
	if (gInput->GetKeyDown(eKeyCode::W))
	{
		if (mRect2DInterpolation->IsCollisionWallFloor() ||
			mRect2DInterpolation->IsCollisionWallSlop())
		{
			return true;
		}
	}

	return false;
}

bool PlayerFSM::CanChagneToRunState() const
{
	if (mPlayerRunState == mCurState)
	{
		return false;
	}

	if (mPlayerIdleState != mCurState)
	{
		return false;
	}

	if (gInput->GetKey(eKeyCode::A) == false && gInput->GetKey(eKeyCode::D) == false)
	{
		return false;
	}

	if (gInput->GetKey(eKeyCode::A) && gInput->GetKey(eKeyCode::D))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallRight() && gInput->GetKey(eKeyCode::D))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallLeft() && gInput->GetKey(eKeyCode::A))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallFloor() == false &&
		mRect2DInterpolation->IsCollisionWallSlop()  == false)
	{
		return false;
	}

	return true;
}

bool PlayerFSM::CanChagneToWallSlideState() const
{
	if (mCurState == mPlayerWallSlideState)
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallFloor() || mRect2DInterpolation->IsCollisionWallSlop())
	{
		return false;
	}	

	Vector2 velocity = mRigidbody2D->GetVelocity();

	if (0.f < velocity.x || gInput->GetKey(eKeyCode::D))
	{
		if (mRect2DInterpolation->IsCollisionWallRight())
		{
			return true;
		}
	}

	if (0.f > velocity.x || gInput->GetKey(eKeyCode::A))
	{
		if (mRect2DInterpolation->IsCollisionWallLeft())
		{
			return true;
		}
	}

	if (mCurState == mPlayerFlipState)
	{
		if (mRect2DInterpolation->IsCollisionWallRight())
		{
			return true;
		}
		if (mRect2DInterpolation->IsCollisionWallLeft())
		{
			return true;
		}
	}

	return false;
}
