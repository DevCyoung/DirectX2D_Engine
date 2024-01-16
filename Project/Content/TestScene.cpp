#include "pch.h"
#include "TestScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
#include <Engine/Engine.h>
#include <Engine/Color.h>

#include "CameraInputMoveMent.h"
#include "InputMovementTest.h"

TestScene::TestScene()
{
	const Vector2& SCREEN_SIZE = gEngine->GetRenderTargetSize();

	//{
	//	Material* const material =
	//		MaterialBuilder::Sprite2D(
	//			eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_spr_vaultdoor_open_spr_vaultdoor_open_0);
	//	
	//	material->SetTexture(gResourceManager->Find<Texture>(L"TextureCS"));
	//	gResourceManager->Insert(L"TextureCS", material);
	//}

	{
		GameObject* const obj = new GameObject;

		obj->AddComponent<RectCollider2D>();		

		obj->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.f);
		//obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 45.f);
		obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

		obj->GetComponent<RectCollider2D>()->SetSize(100.f, 100.f);

		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = new GameObject;

		obj->AddComponent<LineCollider2D>();
		obj->AddComponent<InputMovementTest>();

		obj->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.f);
		obj->GetComponent<LineCollider2D>()->SetPoints(50.f, 50.f, 100.f, 50.f);


		AddGameObject(obj, eLayerType::Default);
	}

	//{
	//	GameObject* const obj = new GameObject;
	//	
	//	obj->AddComponent<RectCollider2D>();
	//	obj->GetComponent<RectCollider2D>()->SetSize(400, 400);
	//
	//	AddGameObject(obj, eLayerType::Default);
	//}

#pragma region Camera
	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(SCREEN_SIZE);
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
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(SCREEN_SIZE);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		AddGameObject(uiCamera, eLayerType::Default);
	}

#pragma endregion
}

TestScene::~TestScene()
{
}

Scene* TestScene::Clone()
{
	return nullptr;
}
