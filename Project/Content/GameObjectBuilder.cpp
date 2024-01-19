#include "pch.h"
#include "GameObjectBuilder.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/Engine.h>
#include "PlayerController.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "ShiftController.h"
#include "UIEffect.h"
#include <Engine/Scene.h>
#include <Engine/EngineMath.h>
#include "FolowPlayer.h"
#include <Engine/AfterImage.h>
#include "SimpleDrawPoint.h"
#include "GangsterAI.h"
#include "PlayerPath.h"
#include "RewindComponent.h"

#include "KissyfaceAI.h"
#include "AxeMovement.h"
#include "MonsterAttack.h"
#include "HeadMovement.h"

#include "CopAI.h"
#include "ShieldCop.h"
#include "ShotGunAI.h"

//#include "Slash.h"
#include "SlashComponent.h"

#include "DoorController.h"

#include "BulletMovement.h"

#include "HeadHunterAI.h"

GameObject* GameObjectBuilder::Default2D(const std::wstring& materialName)
{
	GameObject* const obj = new GameObject();
	obj->AddComponent<SpriteRenderer>();

	SpriteRenderer* const spriteRenderer = obj->GetComponent<SpriteRenderer>();
	spriteRenderer->SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
	spriteRenderer->SetMaterial(gResourceManager->FindOrNull<Material>(materialName));
	return obj;
}

GameObject* GameObjectBuilder::Player()
{
	GameObject* const player = new GameObject();
	player->SetName(L"Player");


	player->AddComponent<Rigidbody2D>();
	player->AddComponent<AfterImage>();
	player->AddComponent<Rect2DInterpolation>();
	player->AddComponent<RectCollider2D>();
	player->AddComponent<PlayerPath>();
	player->AddComponent<RewindComponent>();


	player->GetComponent<AfterImage>()->SetCreateDeltaTime(0.02f);
	player->GetComponent<AfterImage>()->SetAlphaTime(1.2f);
	player->GetComponent<AfterImage>()->SetAlphaMaxTime(2.0f);

	player->GetComponent<AfterImage>()->SetColorR(0.2f);
	player->GetComponent<AfterImage>()->SetColorG(0.8f);
	player->GetComponent<AfterImage>()->SetColorB(0.8f);


	//Animation
	{
		player->GetComponent<Transform>()->SetPosition(0.f, 160.f, -2.f);

		player->AddComponent<Animator2D>();
		player->AddComponent<PlayerController>();

		player->GetComponent<PlayerController>()->SetFSM(new PlayerFSM(player));



		Animator2D* const anim = player->GetComponent<Animator2D>();
		anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"PlayerAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_zero);

		anim->CreateAnimation(L"Attack", atlas, 7,
			XMUINT2(5, 34), XMUINT2(62, 42), XMUINT2(10, 10), XMINT2(0, 3), 0.0325f);

		anim->CreateAnimation(L"Roll", atlas, 7,
			XMUINT2(5, 1718), XMUINT2(48, 33), XMUINT2(10, 10), XMINT2(0, -1), 0.06f);

		anim->CreateAnimation(L"DoorBreakFull", atlas, 10,
			XMUINT2(5, 198), XMUINT2(50, 44), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);

		anim->CreateAnimation(L"Fall", atlas, 4,
			XMUINT2(5, 281), XMUINT2(42, 48), XMUINT2(10, 10), XMINT2(-3, 6), 0.06f);

		anim->CreateAnimation(L"Jump", atlas, 4,
			XMUINT2(5, 826), XMUINT2(32, 42), XMUINT2(10, 10), XMINT2(-3, 3), 0.08f);

		anim->CreateAnimation(L"Idle", atlas, 11,
			XMUINT2(5, 681), XMUINT2(36, 35), XMUINT2(10, 10), XMINT2(0, 0), 0.1f);

		anim->CreateAnimation(L"IdleToRun", atlas, 4,
			XMUINT2(5, 755), XMUINT2(44, 32), XMUINT2(10, 10), XMINT2(0, -2), 0.08f);

		anim->CreateAnimation(L"Run", atlas, 10,
			XMUINT2(5, 1790), XMUINT2(44, 32), XMUINT2(10, 10), XMINT2(0, -2), 0.07f);

		anim->CreateAnimation(L"RunToIdle", atlas, 5,
			XMUINT2(5, 1861), XMUINT2(52, 36), XMUINT2(10, 10), XMINT2(0, 0), 0.085f);

		anim->CreateAnimation(L"Flip", atlas, 11,
			XMUINT2(5, 1137), XMUINT2(50, 45), XMUINT2(10, 10), XMINT2(0, 0), 0.065f);

		anim->CreateAnimation(L"PlaySong", atlas, 31,
			XMUINT2(5, 1221), XMUINT2(36, 39), XMUINT2(10, 10), XMINT2(0, 0), 0.09f);

		anim->CreateAnimation(L"PostCrouch", atlas, 2,
			XMUINT2(5, 1560), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.09f);

		anim->CreateAnimation(L"PreCrouch", atlas, 2,
			XMUINT2(5, 1639), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.09f);

		/*anim->CreateAnimation(L"Crouch", atlas, 1,
			XMUINT2(5, 2005), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 5800), 0.09f);*/

		anim->CreateAnimation(L"WallSlide", atlas, 1,
			XMUINT2(5, 2250), XMUINT2(46, 42), XMUINT2(10, 10), XMINT2(3, 0), 0.09f);

		anim->CreateAnimation(L"HurtGround", atlas, 6,
			XMUINT2(5, 532), XMUINT2(57, 25), XMUINT2(10, 10), XMINT2(0, -5), 0.09f);

		anim->CreateAnimation(L"HurtRecover", atlas, 9,
			XMUINT2(5, 596), XMUINT2(56, 46), XMUINT2(10, 10), XMINT2(1, 5), 0.09f);

		anim->CreateAnimation(L"HurtFlyLoop", atlas, 4,
			XMUINT2(5, 450), XMUINT2(50, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);


		player->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
	}

	//Collider
	{
		player->GetComponent<RectCollider2D>()->SetSize(22.f, 38.f);
		player->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 1.f));
	}

	player->GetComponent<Animator2D>()->Play(L"Idle", true);

	//Rigidbody
	player->GetComponent<Rigidbody2D>()->TurnOnGravity();
	player->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);
	player->GetComponent<Rigidbody2D>()->SetGravityVelocityLimit(1300.f);

	//Collider
	//player->GetComponent<RectCollider2D>()->SetSize(22.f, 44.f);
	//player->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));


	return player;
}

GameObject* GameObjectBuilder::InstantiateMonster(const eMonsterType type, Scene* const scene)
{
	(void)type;
	GameObject* const monster = new GameObject();
	monster->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);

	monster->SetName(L"Monster");
	monster->AddComponent<Rigidbody2D>();
	monster->AddComponent<Rect2DInterpolation>();
	monster->AddComponent<RectCollider2D>();
	monster->AddComponent<Animator2D>();
	switch (type)
	{
	case eMonsterType::Ganster:
		monster->AddComponent<GangsterAI>();
		break;
	case eMonsterType::Shield:
		monster->AddComponent<ShieldCop>();
		break;
	case eMonsterType::Cop:
		monster->AddComponent<CopAI>();
		break;
	case eMonsterType::Shotgun:
		monster->AddComponent<ShotGunAI>();
		break;
	default:
		assert(false);
		break;
	}
	monster->AddComponent<PlayerPath>();
	monster->AddComponent<RewindComponent>();

	monster->GetComponent<RectCollider2D>()->SetSize(22.f, 44.f);
	monster->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));

	monster->GetComponent<Rigidbody2D>()->TurnOnGravity();
	monster->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);	

	scene->AddGameObject(monster, eLayerType::Monster);

	monster->GetComponentOrNull<BasicMonsterAI>()->CreateAnimation(scene);
	monster->GetComponentOrNull<BasicMonsterAI>()->CreateGun(scene);

	monster->GetComponentOrNull<BasicMonsterAI>()->SetMonsterType(type);	

	{
		GameObject* emotion = new GameObject();
		emotion->SetName(L"Emotion");

		emotion->AddComponent<Animator2D>();

		//emotion->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		emotion->GetComponent<Transform>()->SetPosition(10.f, 30.f, 0.f);

		{
			Animator2D * anim = emotion->GetComponent<Animator2D>();

			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Emotion_emotion);
			anim->CreateAnimation(L"Follow", atlas, 3, XMUINT2(5, 703), 
				XMUINT2(17, 20), XMUINT2(10, 10), XMINT2(0, 0), 0.625f);

			anim->CreateAnimation(L"QuestionFollow", atlas, 3, XMUINT2(5, 703),
				XMUINT2(17, 20), XMUINT2(10, 10), XMINT2(0, 0), 0.625f);

			anim->CreateAnimation(L"Exclaim", atlas, 3, XMUINT2(5, 703),
				XMUINT2(17, 20), XMUINT2(10, 10), XMINT2(0, 0), 0.625f);

		}		
		emotion->SetParent(monster);
		monster->GetComponentOrNull<BasicMonsterAI>()->SetEmotion(emotion);
		scene->AddGameObject(emotion, eLayerType::Default);
	}

	return monster;
}

GameObject* GameObjectBuilder::InstantiateKissyface(Scene* const scene)
{
	GameObject* const kissyface = new GameObject();

	kissyface->GetComponent<Transform>()->SetPosition(-200.f, 0.f, 0.f);
	kissyface->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);

	kissyface->SetName(L"Monster");
	kissyface->AddComponent<Rigidbody2D>();
	kissyface->AddComponent<Rect2DInterpolation>();
	kissyface->AddComponent<RectCollider2D>();
	kissyface->AddComponent<Animator2D>();
	kissyface->AddComponent<KissyfaceAI>();

	//Collider
	{
		kissyface->GetComponent<RectCollider2D>()->SetSize(28.f, 58.f);
		kissyface->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));
	}

	//Rigidbody
	{
		kissyface->GetComponent<Rigidbody2D>()->TurnOnGravity();
		kissyface->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);
	}

	//Animation
	{
		Animator2D* const anim = kissyface->GetComponent<Animator2D>();
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

		anim->CreateAnimation(L"Block", atlas, 5, XMUINT2(5, 34), XMUINT2(53, 48), XMUINT2(10, 10), XMINT2(7, 0), 0.09f);

		anim->CreateAnimation(L"Dead", atlas, 12, XMUINT2(5, 121), XMUINT2(49, 26), XMUINT2(10, 10), XMINT2(-6, -12), 0.095f);

		anim->CreateAnimation(L"Slice", atlas, 14, XMUINT2(5, 222), XMUINT2(106, 56), XMUINT2(10, 10), XMINT2(-3, 3), 0.125f);



		anim->CreateAnimation(L"spr_kissyface_hit_grenade", atlas, 6, XMUINT2(5, 607), XMUINT2(72, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"Hurt", atlas, 6, XMUINT2(5, 696), XMUINT2(71, 58), XMUINT2(10, 10), XMINT2(-14, 4), 0.125f);

		anim->CreateAnimation(L"Recover", atlas, 7, XMUINT2(5, 1587), XMUINT2(69, 45), XMUINT2(10, 10), XMINT2(-13, -2), 0.08f);

		anim->CreateAnimation(L"PreJump", atlas, 4, XMUINT2(5, 1410), XMUINT2(44, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"Jump", atlas, 2, XMUINT2(5, 793), XMUINT2(38, 73), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"JumpSwing", atlas, 3, XMUINT2(5, 905), XMUINT2(31, 54), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"LandAttack", atlas, 6, XMUINT2(5, 998), XMUINT2(44, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_lunge", atlas, 5, XMUINT2(5, 1087), XMUINT2(83, 68), XMUINT2(10, 10), XMINT2(20, 9), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_lungeattack", atlas, 8, XMUINT2(5, 1194), XMUINT2(104, 54), XMUINT2(10, 10), XMINT2(35, 2), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_prelunge", atlas, 4, XMUINT2(5, 1498), XMUINT2(41, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);

		anim->CreateAnimation(L"NoHead", atlas, 7, XMUINT2(5, 1351), XMUINT2(53, 20), XMUINT2(10, 10), XMINT2(0, -15), 0.125f);






		anim->CreateAnimation(L"spr_kissyface_sharpenaxe", atlas, 16, XMUINT2(5, 1752), XMUINT2(31, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"Slash", atlas, 12, XMUINT2(5, 1840), XMUINT2(122, 52), XMUINT2(10, 10), XMINT2(24, 1), 0.08f);

		anim->CreateAnimation(L"Struggle", atlas, 2, XMUINT2(5, 2055), XMUINT2(58, 36), XMUINT2(10, 10), XMINT2(0, -7), 0.085f);

		anim->CreateAnimation(L"Throw", atlas, 9, XMUINT2(5, 2130), XMUINT2(106, 55), XMUINT2(10, 10), XMINT2(6, 3), 0.08f);
		anim->CreateAnimation(L"spr_kissyface_returnaxe", atlas, 5, XMUINT2(5, 1671), XMUINT2(69, 42), XMUINT2(10, 10), XMINT2(-14, -4), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_tug", atlas, 6, XMUINT2(5, 2391), XMUINT2(58, 41), XMUINT2(10, 10), XMINT2(5, -4), 0.125f);



		anim->CreateAnimation(L"spr_kissyface_tobattle", atlas, 9, XMUINT2(5, 2289), XMUINT2(52, 63), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);


		anim->CreateAnimation(L"spr_kissyface_walk", atlas, 10, XMUINT2(5, 2471), XMUINT2(39, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_axe", atlas, 1, XMUINT2(5, 2559), XMUINT2(26, 80), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_broken_axe", atlas, 1, XMUINT2(5, 2678), XMUINT2(106, 5), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_casual_idle", atlas, 1, XMUINT2(5, 2722), XMUINT2(40, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_chain", atlas, 1, XMUINT2(5, 2810), XMUINT2(11, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_hitgrenade_idle", atlas, 1, XMUINT2(5, 2853), XMUINT2(37, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"Idle", atlas, 1, XMUINT2(5, 2942), XMUINT2(37, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
	}

	kissyface->GetComponent<Animator2D>()->Play(L"spr_kissyface_sharpenaxe", true);
	//kissyface->GetComponent<Animator2D>()->Play(L"Dead", true);
	scene->AddGameObject(kissyface, eLayerType::Monster);

	{
		GameObject* const parent = new GameObject();
		parent->GetComponent<Transform>()->SetScale(0.5f, 0.5f, 1.f);


		parent->SetParent(kissyface);
		scene->AddGameObject(parent, eLayerType::Monster);

		{
			GameObject* const axe = new GameObject();

			axe->SetName(L"Axe");
			axe->GetComponent<Transform>()->SetFlipx(true);
			axe->AddComponent<Animator2D>();
			axe->AddComponent<RectCollider2D>();
			axe->AddComponent<AxeMovement>();
			axe->AddComponent<AfterImage>();
			axe->AddComponent<MonsterAttack>();

			//axe->AddComponent<Rigidbody2D>();

			axe->GetComponent<RectCollider2D>()->SetSize(22.f, 58.f);
			axe->GetComponent<Animator2D>()->TurnOffVisiblelity();
			axe->GetComponent<AxeMovement>()->SetKissyfaace(kissyface);

			Animator2D* const anim = axe->GetComponent<Animator2D>();
			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

			anim->CreateAnimation(L"spr_kissyface_axe", atlas, 1, XMUINT2(5, 2559), XMUINT2(26, 80), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

			anim->Play(L"spr_kissyface_axe", true);


			kissyface->GetComponent<KissyfaceAI>()->SetAxe(axe);
			scene->AddGameObject(axe, eLayerType::MonsterAttack);
			axe->SetParent(parent);
		}

		{
			GameObject* const brokenAxe = new GameObject();

			brokenAxe->SetName(L"BrokenAxe");
			brokenAxe->AddComponent<Animator2D>();

			Animator2D* const anim = brokenAxe->GetComponent<Animator2D>();
			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

			anim->CreateAnimation(L"spr_kissyface_broken_axe", atlas, 1, XMUINT2(5, 2678), XMUINT2(106, 5), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);


			anim->Play(L"spr_kissyface_broken_axe", true);

			brokenAxe->SetParent(kissyface);
			brokenAxe->GetComponent<Animator2D>()->TurnOffVisiblelity();
			brokenAxe->GetComponent<Transform>()->SetPosition(-3.f, -22.f, 0.f);

			kissyface->GetComponent<KissyfaceAI>()->SetBrokenAxe(brokenAxe);
			scene->AddGameObject(brokenAxe, eLayerType::Default);

		}

		{
			GameObject* const head = new GameObject();

			head->SetParent(kissyface);
			head->SetName(L"Head");

			head->AddComponent<Animator2D>();
			head->AddComponent<RectCollider2D>();
			head->AddComponent<Rigidbody2D>();
			head->AddComponent<HeadMovement>();
			head->AddComponent<Rect2DInterpolation>();

			//Collider
			{
				head->GetComponent<RectCollider2D>()->SetSize(10.f, 10.f);
				head->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 0.f));
			}

			//Rigidbody
			{
				head->GetComponent<Rigidbody2D>()->TurnOffGravity();
				head->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);
			}


			head->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);


			Animator2D* const anim = head->GetComponent<Animator2D>();
			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

			anim->CreateAnimation(L"HeadFly", atlas, 6, XMUINT2(5, 449), XMUINT2(17, 14), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
			anim->CreateAnimation(L"HeadFlyLoop", atlas, 6, XMUINT2(5, 502), XMUINT2(17, 12), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
			anim->CreateAnimation(L"HeadLand", atlas, 8, XMUINT2(5, 553), XMUINT2(46, 15), XMUINT2(10, 10), XMINT2(11, 3), 0.09f);

			//anim->Play(L"HeadFly", true);
			anim->TurnOffVisiblelity();

			head->GetComponent<Transform>()->SetPosition(-20.f, -8.f, 0.f);

			kissyface->GetComponent<KissyfaceAI>()->SetHead(head);
			scene->AddGameObject(head, eLayerType::Monster);

		}
	}

	return kissyface;
}

GameObject* GameObjectBuilder::InstantiateHeadHunter(Scene* const scene)
{
	GameObject* const headHunter = new GameObject();

	headHunter->GetComponent<Transform>()->SetPosition(250.f, -220.f, 0.f);
	headHunter->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);

	headHunter->SetName(L"HeadHunter");
	headHunter->AddComponent<Rigidbody2D>();
	headHunter->AddComponent<Rect2DInterpolation>();
	headHunter->AddComponent<RectCollider2D>();
	headHunter->AddComponent<Animator2D>();
	headHunter->AddComponent<HeadHunterAI>();
	headHunter->AddComponent<RewindComponent>();
	headHunter->AddComponent<AfterImage>();

	headHunter->GetComponent<AfterImage>()->SetCreateDeltaTime(0.01f);
	headHunter->GetComponent<AfterImage>()->SetAlphaTime(1.2f);
	headHunter->GetComponent<AfterImage>()->SetAlphaMaxTime(2.0f);

	//Collider
	{
		headHunter->GetComponent<RectCollider2D>()->SetSize(28.f, 52.f);
		headHunter->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));
	}

	//Rigidbody
	{
		headHunter->GetComponent<Rigidbody2D>()->TurnOnGravity();
		headHunter->GetComponent<Rigidbody2D>()->SetGravityAccel(2500.f);
		headHunter->GetComponent<Rigidbody2D>()->SetGravityVelocityLimit(2500.f);
		headHunter->GetComponent<Rigidbody2D>()->SetVelocityLimit(2500.f);
	}

	headHunter->GetComponent<HeadHunterAI>()->CreateAnimation();

	headHunter->GetComponent<Transform>()->SetFlipx(true);

	scene->AddGameObject(headHunter, eLayerType::Monster);


	{
		//Hand
		GameObject* const hand = headHunter->GetComponent<HeadHunterAI>()->CreateHand();
		
		hand->AddComponent<RewindComponent>();		
		hand->SetParent(headHunter);		
		headHunter->GetComponent<HeadHunterAI>()->SetHand(hand);
		scene->AddGameObject(hand, eLayerType::Monster);
		

		{
			//Lazer

			//GameObject* const lazerMask = GameObjectBuilder::Default2D(L"LazerMask");
			//lazerMask->GetComponent<Transform>()->SetPosition(527.f, 3.f, 0.f);
			//lazerMask->GetComponent<Transform>()->SetScale(1.f, 0.01f, 1.f);

			//lazerMask->SetParent(hand);
			//scene->AddGameObject(lazerMask, eLayerType::Default);
		}
	}

	/**/

	return headHunter;
}

GameObject* GameObjectBuilder::InstantiateDoor(Scene* const scene)
{
	GameObject* const  door = new GameObject();

	door->SetName(L"Door");
	door->AddComponent<Animator2D>();
	door->AddComponent<RectCollider2D>();
	door->AddComponent<DoorController>();
	door->AddComponent<RewindComponent>();


	door->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	door->GetComponent<RectCollider2D>()->SetSize(25.f, 70.f);


	{
		Animator2D* const anim = door->GetComponent<Animator2D>();
		anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Door_dooratlas);

		anim->CreateAnimation(L"Stand", atlas, 1, XMUINT2(5, 536), XMUINT2(80, 64), XMUINT2(10, 10), XMINT2(20, 0), 0.075f);
		anim->CreateAnimation(L"Open", atlas, 20, XMUINT2(5, 34), XMUINT2(80, 64), XMUINT2(10, 10), XMINT2(20, 0), 0.075f);

		anim->Play(L"Stand", true);
	}

	scene->AddGameObject(door, eLayerType::Door);

	return door;
}

GameObject* GameObjectBuilder::InstantiateClubDoor(Scene* const scene)
{
	GameObject* const  clubDoor = new GameObject();

	clubDoor->SetName(L"Door");
	clubDoor->AddComponent<Animator2D>();
	clubDoor->AddComponent<RectCollider2D>();
	clubDoor->AddComponent<DoorController>();
	clubDoor->AddComponent<RewindComponent>();

	clubDoor->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	clubDoor->GetComponent<RectCollider2D>()->SetSize(25.f, 70.f);

	{
		Animator2D* const anim = clubDoor->GetComponent<Animator2D>();
		anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Door_dooratlas);

		anim->CreateAnimation(L"Stand", atlas, 1, XMUINT2(5, 639), XMUINT2(80, 64), XMUINT2(10, 10), XMINT2(20, 0), 0.075f);
		anim->CreateAnimation(L"Open", atlas, 20, XMUINT2(5, 285), XMUINT2(80, 64), XMUINT2(10, 10), XMINT2(20, 0), 0.075f);

		anim->Play(L"Stand", true);
	}

	scene->AddGameObject(clubDoor, eLayerType::Door);

	return clubDoor;
}

GameObject* GameObjectBuilder::Slash()
{
	GameObject* const slash = new GameObject();

	slash->AddComponent<Animator2D>();
	slash->AddComponent<CircleCollider2D>();
	slash->AddComponent<SlashComponent>();




	//Slash->AddComponent<RewindComponent>();

	slash->GetComponent<CircleCollider2D>()->SetRadius(40.f);

	Animator2D* const animator = slash->GetComponent<Animator2D>();

	animator->GetMaterial()->SetShader(
		gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));

	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);

	animator->CreateAnimation(L"Slash", atlas, 6, XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

	//Slash->SetParent(player);
	//player->GetComponent<PlayerController>()->SetSlash(Slash);

	{
		//Animation2D* anim = animator->FindAnimationOrNull(L"Slash");
	}

	slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

	return slash;
}

GameObject* GameObjectBuilder::InstantiatePlayer(Scene* const scene)
{
	GameObject* const player = GameObjectBuilder::Player();

	player->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
	player->GetComponent<Animator2D>()->SetMaterial(gResourceManager->FindOrNull<Material>(L"PlayerAnimation2D"));

	scene->AddGameObject(player, eLayerType::Player);

	//Add Slash
	{
		GameObject* const Slash = new GameObject();

		Slash->AddComponent<Animator2D>();
		Slash->AddComponent<RectCollider2D>();
		Slash->AddComponent<RewindComponent>();
		Slash->AddComponent<SlashComponent>();

		Slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		Slash->GetComponent<RectCollider2D>()->SetSize(50.f, 30.f);
		Slash->GetComponent<RectCollider2D>()->SetOffset(Vector2(30.f, 0.f));

		Animator2D* const animator = Slash->GetComponent<Animator2D>();
		animator->SetMaterial(gResourceManager->FindOrNull<Material>(L"PlayerAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);
		animator->CreateAnimation(L"Slash", atlas, 6,
			XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

		Slash->SetParent(player);
		player->GetComponent<PlayerController>()->SetSlash(Slash);
		scene->AddGameObject(Slash, eLayerType::PlayerAttack);
	}

	return player;

}

GameObject* GameObjectBuilder::InstantiateGlobalLight2D(Scene* const scene, const eLayerType type)
{
	GameObject* const light = new GameObject();
	light->SetName(L"GlobalLight2D");
	light->AddComponent<Light2D>();

	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::DIRECTIONAL);
	light->GetComponent<Light2D>()->SetRadius(300.f);
	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));

	light->GetComponent<Transform>()->SetPosition(100, 0.f, 0.f);

	scene->AddGameObject(light, type);

	return light;
}

void GameObjectBuilder::AddUI(Scene* const scene)
{

#pragma region UIGameOBject
	//UI
	const Vector2 screenSize = Vector2(1280, 720);
	const float hudPosY = screenSize.y / 2.f - 23.f;

	//UI Cursur
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");

		obj->AddComponent<CursorMovement>();

		//obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::Mouse);
	}

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHud");

		const Vector2 pos = helper::RenderTargetToWorldUI(Vector2(screenSize.x / 2.f, 23.f), screenSize);

		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	constexpr float timerPosX = -8.f;

	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudTimer");

		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Timer
	{

		GameObject* const obj = GameObjectBuilder::Default2D(L"UITimer");
		obj->SetName(L"UITimer");
		obj->AddComponent<UIEffect>();

		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);


		//GameManager::GetInstance()->SetUITimer(obj);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIShift00");

		obj->AddComponent<ShiftController>();

		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIBattery");

		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);

		for (UINT i = 0; i < 11; ++i)
		{
			//UI BatteryPart
			{
				GameObject* const part = GameObjectBuilder::Default2D(L"UIBatteryPart");

				part->SetName(L"UIBatteryPart" + std::to_wstring(i));
				part->GetComponent<Transform>()->SetPosition(-25.5f + i * 5.f, 0.5f, 0.f);
				part->SetParent(obj);
				scene->AddGameObject(part, eLayerType::UI);
			}
		}

	}

	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudItem");

		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftItem");

		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightItem");

		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftClick");

		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightClick");

		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}



#pragma endregion

}



GameObject* GameObjectBuilder::AddCamera(Scene* const scene)
{
	//UI
	//const Vector2 screenSize = gEngine->GetRenderTargetSize();	
	const Vector2 screenSize = Vector2(1280, 720); //Katana Scene Size
	GameObject* result = nullptr;

	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();
		result = mainCamera;
		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();
		mainCamera->AddComponent<FolowPlayer>();
		mainCamera->AddComponent<RewindComponent>();
		mainCamera->AddComponent<RectCollider2D>();

		mainCamera->GetComponent<RectCollider2D>()->SetSize(screenSize);


		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();

		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::Mouse);
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::BackGround);

		scene->AddGameObject(mainCamera, eLayerType::Camera);

		//backGorund Camera
		{
			GameObject* const backgroundCamera = new GameObject();

			backgroundCamera->AddComponent<Camera>();
			backgroundCamera->AddComponent<RewindComponent>();


			backgroundCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -110.f);
			backgroundCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::BackGround);
			backgroundCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
			backgroundCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);

			backgroundCamera->GetComponent<Camera>()->TurnOffAllLayer();
			backgroundCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::BackGround);

			backgroundCamera->SetParent(mainCamera);
			scene->AddGameObject(backgroundCamera, eLayerType::Default);
		}
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);

		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::Mouse);

		scene->AddGameObject(uiCamera, eLayerType::Default);
	}

	return result;
}

GameObject* GameObjectBuilder::CreateBullet(Vector3 direction, Vector3 position)
{
	GameObject* bullet = new GameObject();


	bullet->AddComponent<BulletMovement>();
	bullet->AddComponent<RewindComponent>();
	bullet->AddComponent<RectCollider2D>();

	bullet->GetComponent<BulletMovement>()->mDir = Vector3(direction.x, direction.y, 0.f);
	bullet->GetComponent<RectCollider2D>()->SetSize(20.f, 20.f);
	bullet->GetComponent<Transform>()->SetPosition(position);

	return bullet;
}

GameObject* GameObjectBuilder::CreateBullet(Vector3 direction, Vector3 position, eBulletType type)
{
	GameObject* bullet = CreateBullet(direction, position);
	bullet->AddComponent<Animator2D>();

	BulletMovement* bulletMovement = bullet->GetComponent<BulletMovement>();
	bulletMovement->SetBulletType(type);

	switch (type)
	{
	case eBulletType::MonsterBullet:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Particle_particle);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 79), XMUINT2(34, 2), XMUINT2(10, 10), XMINT2(0, 0), 0.1f);
	}
	break;
	case eBulletType::PlayerBullet:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Particle_particle);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 79), XMUINT2(34, 2), XMUINT2(10, 10), XMINT2(0, 0), 0.1f);
		bulletMovement->SetIsPlayerBullet(true);
		bulletMovement->SetIsRotationMode(true);
		bulletMovement->SetIsScaleMode(false);		
	}
	break;
	case eBulletType::PlayerBust:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Emotion_emotion);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 469), XMUINT2(46, 64), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		bulletMovement->SetIsPlayerBullet(true);
		bulletMovement->SetIsRotationMode(true);
		bulletMovement->SetIsScaleMode(false);
	}
	break;
	case eBulletType::PlayerKinfe:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Emotion_emotion);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 572), XMUINT2(42, 42), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		bulletMovement->SetIsPlayerBullet(true);
		bulletMovement->SetIsRotationMode(true);
		bulletMovement->SetIsScaleMode(false);
	}
	break;
	case eBulletType::PlayerBeer1:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Emotion_emotion);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 34), XMUINT2(24, 48), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		bulletMovement->SetIsPlayerBullet(true);
		bulletMovement->SetIsRotationMode(true);
		bulletMovement->SetIsScaleMode(false);
	}
	break;
	case eBulletType::PlayerBeer2:
	{
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Emotion_emotion);
		bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 121), XMUINT2(24, 48), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		bulletMovement->SetIsPlayerBullet(true);
		bulletMovement->SetIsRotationMode(true);
		bulletMovement->SetIsScaleMode(false);
	}
		break;
	default:
		assert(false);
		break;
	}	

	bullet->GetComponent<Animator2D>()->Play(L"Bullet", false);
	return bullet;
}
