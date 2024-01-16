#include "pch.h"
#include "PlayerController.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"
#include "GameManager.h"
#include "MonsterAttack.h"
#include "ResourceManager.h"
#include "FolowPlayer.h"
#include "DieController.h"
#include "BulletMovement.h"
#include "KatanaZeroSystem.h"
PlayerController::PlayerController()
	: ScriptComponent(eScriptComponentType::PlayerController)
	, mPlayerFSM(nullptr)
	, mSlash(nullptr)
	, mbControl(true)
	, mbinvincibility(false)
	, mbDead(false)
{
}

PlayerController::~PlayerController()
{
	SAFE_DELETE_POINTER(mPlayerFSM);
}

void PlayerController::ChangeHurtState()
{
	mPlayerFSM->ChangeState(mPlayerFSM->mPlayerHurtState);
}

void PlayerController::initialize()
{
	mPlayerFSM->Initialize(mPlayerFSM->mPlayerIdleState);



	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"IdleToRun");

		{
			std::function<void()> func = std::bind(&PlayerController::idleToRun, this);
			animation->SetLastFrameEndEvent(func);
		}
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"RunToIdle");


		{
			std::function<void()> func = std::bind(&PlayerController::runToIdleVeloZero, this);
			animation->SetFrameEndEvent(3, func);
		}

		{
			std::function<void()> func = std::bind(&PlayerController::runToIdle, this);
			animation->SetLastFrameEndEvent(func);
		}

	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Roll");

		std::function<void()> func = [this]() {
			this->GetOwner()->GetComponent<Animator2D>()->Play(L"Idle", true);
			this->mPlayerFSM->ChangeState(mPlayerFSM->mPlayerIdleState);
		};

		animation->SetLastFrameEndEvent(func);
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"PostCrouch");
		std::function<void()> func = [this]() {
			this->GetOwner()->GetComponent<Animator2D>()->Play(L"Idle", true);
			this->mPlayerFSM->ChangeState(mPlayerFSM->mPlayerIdleState);
		};

		animation->SetLastFrameEndEvent(func);
	}

	{
		std::function<void()> func = [this]() {

			//Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

			if (GetOwner()->GetComponent<Rect2DInterpolation>()->IsCollisionWallFloor() || GetOwner()->GetComponent<Rect2DInterpolation>()->IsCollisionWallSlop())
			{
				mPlayerFSM->mPlayerGlobalState->RunToIdle();
			}
			else
			{
				//animator->Play(L"Fall", true);
				mPlayerFSM->ChangeState(mPlayerFSM->mPlayerFallState);
			}


		};

		Animation2D* animation = animator->FindAnimationOrNull(L"Attack");

		animation->SetLastFrameEndEvent(func);
	}


	mSlash->GetComponent<Transform>()->SetPosition(100000.f, 100000.f, 100000.f);
	//GameManager::GetInstance()->GetRewindManager()->RegisterRewindObject(GetOwner());


	//Sound
	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Roll");

		std::function<void()> func = [this]() {
			gSoundManager->Play(eResAudioClip::playerRoll, 0.2f);

		};

		animation->SetFrameStartEvent(0, func);

	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Jump");

		std::function<void()> func = [this]() {
			gSoundManager->Play(eResAudioClip::playerJump, 0.4f);

			Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
			position.y += 15.f;
			gEffectManager->Shot(L"JumpCloud", position);

		};

		animation->SetFrameStartEvent(0, func);
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Flip");

		std::function<void()> func = [this]() {
			gSoundManager->Play(eResAudioClip::playerRoll, 0.4f);

		};

		animation->SetFrameStartEvent(0, func);
	}

	/*{
		Animation2D* animation = animator->FindAnimationOrNull(L"WallSlide");

		std::function<void()> func = [this]() {
			GameManager::GetInstance()->GetSoundManager()->Play(eResAudioClip::playerWallSlide, 0.4f);

		};

		animation->SetFrameStartEvent(0, func);
	}*/

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"IdleToRun");

		std::function<void()> func = [this]() {
			gSoundManager->Play(eResAudioClip::playerPreRun, 0.25f);

			Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();

			position.y -= 12.f;

			if (GetOwner()->GetComponent<Transform>()->GetFlipX())
			{
				position.x += 25.f;
				gEffectManager->Shot(L"StomperCloud", position, false);
			}
			else
			{
				position.x -= 25.f;
				gEffectManager->Shot(L"StomperCloud", position, true);
			}
		};

		animation->SetFrameStartEvent(2, func);
	}




	
	//GetOwner()->GetComponent<Afterimage>()
}

void PlayerController::update()
{
	Assert(mPlayerFSM, ASSERT_MSG_NULL);

	if (gInput->GetKeyDown(eKeyCode::K))
	{
		bool bDamaged = KatanaZeroSystem::GetInstance()->IsPlayerDamaged();
		KatanaZeroSystem::GetInstance()->SetPlayerDamaged(!bDamaged);
	}

	if (GameManager::GetInstance()->GetRewindManager()->GetRewindState() != eRewindState::Record)
	{
		return;
	}

	if (mbControl)
	{
		mPlayerFSM->GlobalUpdate();

		mPlayerFSM->InputUpdate();
	}

	mPlayerFSM->Update();

	if (mPlayerFSM->GetCurState() == mPlayerFSM->mPlayerRollState ||
		mPlayerFSM->GetCurState() == mPlayerFSM->mPlayerFlipState)
	{
		mbinvincibility = true;
	}
	else
	{
		mbinvincibility = false;
	}
}

void PlayerController::lateUpdate()
{

}

void PlayerController::onCollisionEnter(Collider2D* other)
{
	if (other->GetOwner()->GetLayer() == eLayerType::Bullet && false == mbDead &&
		mPlayerFSM->mPlayerRollState != mPlayerFSM->GetCurState() &&
		mPlayerFSM->mPlayerFlipState != mPlayerFSM->GetCurState() &&
		false == other->GetOwner()->GetComponent<BulletMovement>()->IsPlayerBullet())
	{
		if (mbControl)
		{
			mbControl = false;
			Vector3 dir = other->GetOwner()->GetComponent<BulletMovement>()->mDir;
			mPlayerFSM->mPlayerHurtState->mDirection = Vector2(dir.x, dir.y);
			mPlayerFSM->ChangeState(mPlayerFSM->mPlayerHurtState);

			gSoundManager->PlayInForce(eResAudioClip::PlayerDie, 1.f);

			Camera* const mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
			mainCamera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();

			GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f, eTimeEffectType::Damaged);

			//DieEnter
			dieEnter();
		}
	}
}

void PlayerController::onCollisionStay(Collider2D* other)
{

	if (other->GetOwner()->GetLayer() == eLayerType::MonsterAttack && false == mbinvincibility)
	{
		if (mbControl)
		{
			if (other->GetOwner()->GetComponent<MonsterAttack>()->GetAttackAble())
			{
				mbControl = false;
				//mPlayerFSM->mPlayerHurtState->mDirection = other->GetOwner()->GetComponent<MonsterAttack>()->GetAttackDirection();
				Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
				Vector2 direction = rigidbody->GetDirection();
				direction.x *= -1.f;
				mPlayerFSM->mPlayerHurtState->mDirection = direction;
				mPlayerFSM->ChangeState(mPlayerFSM->mPlayerHurtState);


				gSoundManager->PlayInForce(eResAudioClip::PlayerDie, 1.f);

				Camera* const mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);

				mainCamera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();
				GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f, eTimeEffectType::Damaged);


				dieEnter();
			}
		}
	}	
}

void PlayerController::dieEnter()
{
	if (KatanaZeroSystem::GetInstance()->IsPlayerDamaged())
	{
		GameObject* dieControler = GetOwner()->GetGameSystem()->FindGameObject(L"DieController");

		dieControler->GetComponent<DieController>()->TurnOnDieText();
	}
	
}

void PlayerController::idleToRun()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	animator->Play(L"Run", true);
}

void PlayerController::runToIdle()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();
	//Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	animator->Play(L"Idle", true);
	//rigidbody->SetVelocity(Vector2(0.f, 0.f));
}

void PlayerController::runToIdleVeloZero()
{
	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
	rigidbody->SetVelocity(Vector2::Zero);
}

void PlayerController::toFall()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	animator->Play(L"Fall", true);
}
