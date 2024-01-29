#include "pch.h"
#include "Content.h"

#include "ResourceManager.h"

#include <Engine/Engine.h> 
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include <Engine/TimeManager.h>

#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/GameObject.h>
#include <Engine/Camera.h>
#include <Engine/Transform.h>
#include "SoundManager.h"
#include "CameraInputMoveMent.h"
#include <Engine/SpriteRenderer.h>
#include <Engine/MeshRenderer.h>
Content::Content()
{
	Scene* testScene = new Scene;

	//main Camera
	{
		const Vector2 screenSize = Vector2(1280, 720);
		GameObject* const mainCamera = new GameObject();		
		mainCamera->AddComponent<Camera>();
		mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -3000.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();		

		mainCamera->SetName(L"mainCamera");

		mainCamera->GetComponent<Transform>()->SetPosition(Vector3(772.f, 2250.f, -3690.f));
		//mainCamera->GetComponent<Transform>()->SetRotation(Vector3(24.f, 4.f, 0.f));


		testScene->AddGameObject(mainCamera, eLayerType::Default);
	}



	{
		Material* const material = new Material();
		//Texture* texture =  gResourceManager->FindAndLoad<Texture>(L"\\texture\\TILE_01.tga");
		Texture* texture = gResourceManager->FindAndLoad<Texture>(L"\\texture\\TILE_01.tga");

		Texture* texture2 =
			gResourceManager->FindAndLoad<Texture>(L"\\texture\\TILE_01_N.tga");

		Shader* shader = 
			gResourceManager->FindAndLoad<Shader>(L"Std3D");

		Mesh* panelMesh =
			gResourceManager->FindAndLoad<Mesh>(L"Panel");

		material->SetShader(shader);
		material->SetTexture(TEX_0, texture);
		material->SetTexture(TEX_1, texture2);
		gResourceManager->Insert<Material>(L"default mat", material);


		{
			GameObject* obj = new GameObject();
			obj->AddComponent<MeshRenderer>();
			obj->GetComponent<MeshRenderer>()->SetMaterial(material);
			obj->GetComponent<MeshRenderer>()->SetMesh(panelMesh);
			obj->SetName(L"Map");
			Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
			rotation.x = 90;
			obj->GetComponent<Transform>()->SetRotation(rotation);
			testScene->AddGameObject(obj, eLayerType::TileMap);
		}		

		{
			GameObject* obj = new GameObject();
			obj->AddComponent<MeshRenderer>();

			obj->GetComponent<MeshRenderer>()->SetMaterial(material);
			obj->GetComponent<MeshRenderer>()->SetMesh(panelMesh);

			obj->GetComponent<Transform>()->SetPosition(100.f, 100.f, 0.f);
			obj->SetName(L"Map");
			//Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
			//rotation.x = 90;
			//obj->GetComponent<Transform>()->SetRotation(rotation);
			testScene->AddGameObject(obj, eLayerType::TileMap);
		}
	}
	////Material
	//{
	//	Material* const material =
	//		MaterialBuilder::Sprite2D(
	//			eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_Tilemap);
	//	gResourceManager->Insert(L"TestMap", material);
	//}

	////Map
	//{
	//	GameObject* const tile = GameObjectBuilder::Default2D(L"TestMap");
	//	testScene->AddGameObject(tile, eLayerType::TileMap);
	//}

	//Object


	SceneManager::GetInstance()->LoadScene(testScene);
}

Content::~Content()
{
	//TimeManager::deleteInstance();
	//SoundManager::deleteInstance();
	//KatanaZeroSystem::deleteInstance();
}

//void Content::resourceInitialize()
//{
//	loadTexture();
//	loadShader();
//	loadMaterial();
//
//	Texture* const noiseTexture01 = gResourceManager->FindByEnum<Texture>(eResTexture::Noise_01);
//	gGraphicDevice->BindSRV(eShaderBindType::PS, 7, noiseTexture01);
//}
//
//void Content::loadTexture()
//{
//	for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
//	{
//		gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
//	}
//}
//
//void Content::loadShader()
//{
//
//}
//
//void Content::loadMaterial()
//{
//#pragma region HeadHunterBullet
//	{
//		Material* const tileMaterial =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::spr_kissyface_grenade_2x);
//		gResourceManager->Insert(L"HeadHunterBullet", tileMaterial);
//	}
//#pragma endregion
//
//#pragma region HeadHunterBulletCircle
//	{
//		Material* const tileMaterial =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::CircleLine);
//		gResourceManager->Insert(L"HeadHunterBulletCircleLine", tileMaterial);
//	}
//#pragma endregion
//
//#pragma region TitleMaterial
//	{
//		Material* const material = MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue,
//			eResTexture::Title_spr_title_background);
//		gResourceManager->Insert(L"TitleBackGround", material);
//	}
//
//	{
//		Material* const material = MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue,
//			eResTexture::Title_spr_title_fence);
//		gResourceManager->Insert(L"TitleFence", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Title_spr_titlegraphic_big2);
//		gResourceManager->Insert(L"TitleGraphic", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Title_spr_titlegraphic_big_1);
//		gResourceManager->Insert(L"TitleGraphic1", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Title_spr_titlegraphic_big_2);
//		gResourceManager->Insert(L"TitleGraphic2", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Title_spr_title_grass);
//		gResourceManager->Insert(L"TitleGrass", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Title_spr_title_plants_0);
//		gResourceManager->Insert(L"TitlePlant", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::TitleHud);
//		gResourceManager->Insert(L"TitleHud", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::TitleTextHud);
//		gResourceManager->Insert(L"TitleTextHud", material);
//	}
//
//
//#pragma endregion
//#pragma region Chianatown01Material
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_1);
//		gResourceManager->Insert(L"Chanatown05BackGround01", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_2);
//		gResourceManager->Insert(L"Chanatown05BackGround02", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_3);
//		gResourceManager->Insert(L"Chanatown05BackGround03", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_Tilemap);
//		gResourceManager->Insert(L"Chanatown01TileMap", material);
//	}
//#pragma endregion
//#pragma region Chianatown02Material
//	{
//		Material* const tileMaterial =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown04_Tilemap);
//		gResourceManager->Insert(L"Chanatown04TileMap", tileMaterial);
//	}
//#pragma endregion
//#pragma region Chinatown05Material
//	{
//		Material* const backgroundMaterial =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_spr_chinatown_loop_parallax_1);
//		gResourceManager->Insert(L"Chanatown05BackGround01p", backgroundMaterial);
//	}
//
//	{
//		Material* const backgroundMaterial =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_spr_chinatown_loop_parallax_2);
//		gResourceManager->Insert(L"Chanatown05BackGround02p", backgroundMaterial);
//	}
//
//	{
//		Material* const tileMaterial =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_Tilemap);
//		gResourceManager->Insert(L"Chanatown05TileMap", tileMaterial);
//	}
//#pragma endregion
//#pragma region HeadHunterMaterial
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_map);
//		gResourceManager->Insert(L"HeadHunterMap", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::LightSprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_spr_vaultdoor_open_spr_vaultdoor_open_0);
//
//		gResourceManager->Insert(L"HeadHunterMapDoor", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::layermask);
//		gResourceManager->Insert(L"LazerMask", material);
//	}
//
//#pragma endregion
//
//
//	//Animation Material
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::Opqaue, L"Animation2D", eResTexture::door);
//
//		gResourceManager->Insert(L"Animation2D", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::PostProcess, L"Animation2D", eResTexture::door);
//
//		gResourceManager->Insert(L"Text", material);
//	}
//
//	//After
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::Opqaue, L"AfterImage", eResTexture::door);
//
//		gResourceManager->Insert(L"AfterImage", material);
//	}
//
//
//	//Animation Material
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::Opqaue, L"LightAnimation2D", eResTexture::door);
//
//		gResourceManager->Insert(L"LightAnimation2D", material);
//	}
//
//	//Player Animation Material
//	{
//		{
//			Material* const material =
//				MaterialBuilder::Default2D(
//					eRenderPriorityType::Opqaue, L"LightAnimation2D", eResTexture::door);
//
//			gResourceManager->Insert(L"PlayerAnimation2D", material);
//		}
//	}
//
//	//Effect
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::PostProcess, L"NextScene", eResTexture::pixel100);
//		gResourceManager->Insert(L"NextScene", material);
//	}
//
//	//BlackOut
//	{
//		Material* const material = MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue,
//			eResTexture::pixel100);
//		gResourceManager->Insert(L"BlackOut", material);
//	}
//
//	//BlackOut2
//	{
//		Material* const material = MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue,
//			eResTexture::pixel100);
//		gResourceManager->Insert(L"BlackOut2", material);
//	}
//
//	//Slash
//	{
//		Material* const material = MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue,
//			eResTexture::pixel100);
//		gResourceManager->Insert(L"Slash", material);
//	}
//
//	//PostProcess
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::PostProcess, L"GrayPostProcess", eResTexture::door);
//
//		gResourceManager->Insert(L"GrayPostProcess", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Default2D(
//				eRenderPriorityType::PostProcess, L"WavePostProcess", eResTexture::door);
//
//		gResourceManager->Insert(L"WavePostProcess", material);
//	}
//
//
//
//	
//	loadUIMaterial();
//}
//
//void Content::loadUIMaterial()
//{
//	//Cursor
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_cursor);
//		gResourceManager->Insert(L"UICursor", material);
//	}
//
//	//Hud Bar
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud);
//		gResourceManager->Insert(L"UIHud", material);
//	}
//
//	//Hud Timer
//	{
//
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_timer_0);
//		gResourceManager->Insert(L"UIHudTimer", material);
//	}
//
//	//Timer
//	{
//
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_timer);
//		gResourceManager->Insert(L"UITimer", material);
//	}
//
//	//Shift 00
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_keyboard_shift_0);
//		gResourceManager->Insert(L"UIShift00", material);
//	}
//
//	//Shift 01
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue,eResTexture::UI_spr_keyboard_shift_1);
//		gResourceManager->Insert(L"UIShift01", material);
//	}
//
//	//Battrey
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_battery);
//		gResourceManager->Insert(L"UIBattery", material);
//	}
//
//	//Battrey part
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_battery_part);
//		gResourceManager->Insert(L"UIBatteryPart", material);
//	}
//
//	//Hud Item
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_subweapon);
//		gResourceManager->Insert(L"UIHudItem", material);
//	}
//
//	//Right Item
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_itemicons_0);
//		gResourceManager->Insert(L"UIRightItem", material);
//	}
//
//	//Left Item
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_katanaicons_0);
//		gResourceManager->Insert(L"UILeftItem", material);
//	}
//
//	//Right Click Mouse
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_right_click_1);
//		gResourceManager->Insert(L"UIRightClick", material);
//	}
//
//	//Left Click Mouse
//	{
//		Material* const material =
//			MaterialBuilder::UI2D(
//				eRenderPriorityType::Opqaue, eResTexture::UI_spr_left_click_1);
//		gResourceManager->Insert(L"UILeftClick", material);
//	}
//}
//
//void Content::testSceneInitialize()
//{
//}
