#include "pch.h"
#include "Collide2DTestScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "UIEffect.h"
#include "Bugiman.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include "LerpTest.h"
#include <Engine/CollisionManagement2D.h>
#include "InputMovementTest.h"
#include "ChildTest.h"
#include "ParentTest.h"
Collide2DTestScene::Collide2DTestScene()
	: Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Bullet);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Mouse);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Satellite);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Mouse, eLayerType::Satellite);
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
		
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
		
		obj->GetComponent<Transform>()->SetPosition(-500.f, 200.f, 121.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(200.f, 100.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
		
		AddGameObject(obj, eLayerType::Default);
	
		{
			GameObject* const child = GameObjectBuilder::Default2D(L"UICursor");
		
			child->AddComponent<RectCollider2D>();
			child->AddComponent<PlayerMovementTest>();
		
			child->GetComponent<PlayerMovementTest>()->mbRight = false;
			child->GetComponent<Transform>()->SetPosition(300.f, 0.f, 251.f);
			child->GetComponent<RectCollider2D>()->SetSize(Vector2(100.f, 100.f));
		
			child->SetParent(obj);
			AddGameObject(child, eLayerType::Default);
		
			{
				GameObject* const child2 = GameObjectBuilder::Default2D(L"UICursor");
		
				child2->AddComponent<RectCollider2D>();
				child2->AddComponent<PlayerMovementTest>();
		
				child2->GetComponent<PlayerMovementTest>()->mbRight = false;
				child2->GetComponent<Transform>()->SetPosition(300.f, 0.f, 771.f);
				child2->GetComponent<RectCollider2D>()->SetSize(Vector2(100.f, 100.f));
		
				child2->SetParent(child);
				AddGameObject(child2, eLayerType::Default);
		
				{
					GameObject* const child3 = GameObjectBuilder::Default2D(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(-300.f, 0.f, 122.f);
					child3->GetComponent<CircleCollider2D>()->SetRadius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::Default2D(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(300.f, 0.f, 14.f);
					child3->GetComponent<CircleCollider2D>()->SetRadius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::Default2D(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(0.f, 300.f, 471.f);
					child3->GetComponent<CircleCollider2D>()->SetRadius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::Default2D(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
					child3->AddComponent<ParentTest>();
					
					child3->GetComponent<Transform>()->SetPosition(0.f, -300.f, 81.f);
					child3->GetComponent<CircleCollider2D>()->SetRadius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
		
					{
						GameObject* const child4 = GameObjectBuilder::Default2D(L"UICursor");
		
						child4->AddComponent<CircleCollider2D>();
						child4->AddComponent<ChildTest>();
		
						child4->GetComponent<Transform>()->SetPosition(500.f, 0.f, 441.f);
						child4->GetComponent<CircleCollider2D>()->SetRadius(20.f);
		
						child4->SetParent(child3);
						AddGameObject(child4, eLayerType::Default);
					}
				}
		
			}
		
		
		}
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(300.f, 0.f, 133.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(500.f, 100.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(-300.f, -300.f, 12.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(500.f, 20.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(-100.f, -500.f, 200.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(1000.f, 100.f));
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(250, -150, 100.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 10.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(500, 20));
		obj->GetComponent<PlayerMovementTest>()->mbRight = true;
	
		AddGameObject(obj, eLayerType::Default);
	
		{
			GameObject* const child = GameObjectBuilder::Default2D(L"UICursor");
	
			child->AddComponent<RectCollider2D>();
	
			child->GetComponent<Transform>()->SetPosition(100, 50 - 10, 50.f);
			child->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
			child->GetComponent<RectCollider2D>()->SetSize(Vector2(100, 100));
			child->GetComponent<RectCollider2D>()->SetOffset(Vector2(0, 100));
	
			child->SetParent(obj);
			AddGameObject(child, eLayerType::Default);
		}
	
	
	}
	
	
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<CircleCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetScale(1.f, 1.f, 1.f);
	
		obj->GetComponent<Transform>()->SetPosition(750, -350, 500.f);		
		obj->GetComponent<CircleCollider2D>()->SetRadius(100.f);		
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<CircleCollider2D>();		
	
	
		obj->GetComponent<Transform>()->SetPosition(550, -350, 500.f);
		obj->GetComponent<CircleCollider2D>()->SetRadius(100.f);
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<CircleCollider2D>();
		obj->AddComponent<InputMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 10.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		obj->GetComponent<CircleCollider2D>()->SetRadius(150.f);
	
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const parent = GameObjectBuilder::Default2D(L"UICursor");

		parent->AddComponent<RectCollider2D>();
		parent->AddComponent<ParentTest>();

		parent->GetComponent<RectCollider2D>()->SetSize(100.f, 100.f);

		AddGameObject(parent, eLayerType::Default);
	}

	{
		GameObject* const parent = GameObjectBuilder::Default2D(L"UICursor");

		parent->AddComponent<CircleCollider2D>();
		parent->AddComponent<ParentTest>();

		parent->GetComponent<CircleCollider2D>()->SetRadius(50.f);

		AddGameObject(parent, eLayerType::Default);
	}
	
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();		
	
		obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 10.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(300.f, 100.f));
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
	
		obj->GetComponent<Transform>()->SetPosition(1000.f, -800.f, 10.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, -30.f);
		obj->GetComponent<RectCollider2D>()->SetSize(Vector2(300.f, 100.f));
	
		AddGameObject(obj, eLayerType::Default);
	}

#pragma region UIGameOBject
	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();
	const float hudPosY = gEngine->GetRenderTargetSize().y / 2.f - 23.f;

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHud");
	
		const Vector2 pos = helper::RenderTargetToWorldUI(Vector2(screenSize.x / 2.f, 23.f), screenSize);
	
		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	constexpr float timerPosX = -8.f;
	
	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudTimer");
	
		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Timer
	{
	
		GameObject* const obj = GameObjectBuilder::Default2D(L"UITimer");
	
		obj->AddComponent<UIEffect>();
	
		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIShift00");
	
		obj->AddComponent<ShiftController>();
	
		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIBattery");
	
		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudItem");
	
		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftItem");
	
		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightItem");
	
		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftClick");
	
		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightClick");
	
		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}

#pragma endregion

#pragma region CursurAndCameraGameObject
	//Cursur
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");
	
		obj->AddComponent<CircleCollider2D>();
		obj->AddComponent<CursorMovement>();
	
		obj->GetComponent<CircleCollider2D>()->SetRadius(50.f);
	
		AddGameObject(obj, eLayerType::Mouse);
	}	

	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);

		AddGameObject(mainCamera, eLayerType::Default);
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

		AddGameObject(uiCamera, eLayerType::Default);
	}
#pragma endregion
}

Collide2DTestScene::~Collide2DTestScene()
{
}

Scene* Collide2DTestScene::Clone()
{
	return nullptr;
}
