#include "pch.h"
#include "TitleScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
#include <Engine/Engine.h>
#include <Engine/Color.h>
#include <Engine/SceneManager.h>
#include "Chinatown01Scene.h"
#include "TitleController.h"
#include "Chinatown01Scene.h"

TitleScene::TitleScene()
	: KatanaScene(eKatanaSceneType::Title)
{
	SetBackgroundColor(helper::Color::BLACK);
}
TitleScene::~TitleScene()
{

}

void TitleScene::AddMapObject()
{
}

void TitleScene::AddWallObject()
{
}

void TitleScene::AddDoorObject()
{
}

void TitleScene::AddMonsterObject()
{
}

void TitleScene::AddObject()
{
}

void TitleScene::AddLightObject()
{
}

void TitleScene::AddCameraObject()
{
}

void TitleScene::AddUIObject()
{
#pragma region UI
	//const Vector2& SCREEN_SIZE = gEngine->GetRenderTargetSize();
	const Vector2& SCREEN_SIZE = Vector2(1280, 720);

	GameObject* const backgroundParent = new GameObject();

	backgroundParent->GetComponent<Transform>()->SetPosition(0.f, 350.f, 0.f);
	backgroundParent->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
	{
		{
			GameObject* const background = GameObjectBuilder::Default2D(L"TitleBackGround");

			background->GetComponent<Transform>()->SetPosition(0.f, 0.f, 32.f);
			background->SetParent(backgroundParent);
			AddGameObject(background, eLayerType::Default);
		}

		{
			GameObject* const fence = GameObjectBuilder::Default2D(L"TitleFence");

			fence->GetComponent<Transform>()->SetPosition(0.f, 0.f, 30.f);
			fence->SetParent(backgroundParent);
			AddGameObject(fence, eLayerType::Default);
		}

		{
			GameObject* const grass = GameObjectBuilder::Default2D(L"TitleGrass");

			grass->GetComponent<Transform>()->SetPosition(0.f, -320.f, 30.f);
			grass->SetParent(backgroundParent);
			AddGameObject(grass, eLayerType::Default);
		}

		{
			GameObject* const plants = new GameObject();
			plants->GetComponent<Transform>()->SetPosition(0.f, -175.f, 30.f);
			plants->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.0f);
			//gResourceManager->LoadByEnum<Texture>(eResTexture::Atlas_Title_Plants);

			Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Title_Plants);

			plants->AddComponent<Animator2D>();

			Animator2D* const animator = plants->GetComponent< Animator2D>();

			animator->CreateAnimation(L"TitlePlant", atlas, 12, XMUINT2(5, 34),
				XMUINT2(640, 360), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);

			animator->SetBackSize(XMUINT2(3000, 3000));
			animator->Play(L"TitlePlant", true);

			plants->SetParent(backgroundParent);
			AddGameObject(plants, eLayerType::Default);
		}
	}
	AddGameObject(backgroundParent, eLayerType::Default);



	GameObject* const graphicParent = new GameObject();
	graphicParent->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 1.f);
	graphicParent->GetComponent<Transform>()->SetPosition(0.f, -10.f, 0.f);

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"TitleGraphic1");

		obj->GetComponent<Transform>()->SetPosition(0.f, 50.f, 31.f);
		obj->SetParent(graphicParent);
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"TitleGraphic2");

		obj->GetComponent<Transform>()->SetPosition(0.f, 50.f, 31.f);
		obj->SetParent(graphicParent);
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"TitleGraphic");

		obj->GetComponent<Transform>()->SetPosition(0.f, 100.f, 31.f);
		obj->SetParent(graphicParent);		
		AddGameObject(obj, eLayerType::Default);
	}
	AddGameObject(graphicParent, eLayerType::Default);


	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"TitleHud");
		obj->GetComponent<Transform>()->SetPosition(0.f, -170.f, 0.f);
		obj->GetComponent<SpriteRenderer>()->SetColorR(0.01f);
		obj->GetComponent<SpriteRenderer>()->SetColorG(0.01f);
		obj->GetComponent<SpriteRenderer>()->SetColorB(0.01f);
		obj->GetComponent<SpriteRenderer>()->SetColorA(0.45f);

		AddGameObject(obj, eLayerType::Default);

		//Text
		{
			GameObject* const childObj = new GameObject();
			childObj->AddComponent<EngineText>();

			childObj->GetComponent<EngineText>()->SetScale(25.f);
			childObj->GetComponent<EngineText>()->SetText(L"새로운 게임");
			childObj->GetComponent<EngineText>()->SetPosition(XMUINT2(580, 400));

			childObj->SetParent(obj);
			AddGameObject(childObj, eLayerType::Default);
		}

		//Text
		{
			GameObject* const childObj = new GameObject();
			childObj->AddComponent<EngineText>();

			childObj->GetComponent<EngineText>()->SetScale(25.f);
			childObj->GetComponent<EngineText>()->SetText(L"종료");
			childObj->GetComponent<EngineText>()->SetPosition(XMUINT2(620, 450));

			childObj->SetParent(obj);
			AddGameObject(childObj, eLayerType::Default);
		}

		{
			GameObject* const childObj = GameObjectBuilder::Default2D(L"TitleTextHud");

			childObj->AddComponent<TitleController>();

			childObj->GetComponent<Transform>()->SetPosition(0.f, 112.f, 0.f);
			childObj->GetComponent<SpriteRenderer>()->SetColorR(0.5f);
			childObj->GetComponent<SpriteRenderer>()->SetColorG(0.5f);
			childObj->GetComponent<SpriteRenderer>()->SetColorB(0.5f);
			childObj->GetComponent<SpriteRenderer>()->SetColorA(0.17f);

			childObj->SetParent(obj);
			AddGameObject(childObj, eLayerType::Default);
		}
	}

#pragma endregion
#pragma region Camera
	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();

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

void TitleScene::AddPlayerObject()
{
}

Scene* TitleScene::Clone()
{
	return nullptr;
}

KatanaScene* TitleScene::GetNextScene()
{
	return new Chinatown01Scene();
}
