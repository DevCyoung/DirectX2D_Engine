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
#include <Engine/Light3D.h>
#include <Engine/Texture.h>
#include <Engine/FBXLoader.h>
#include <Engine/EnumResource.h>
#include <Engine/String.h>
eResourceType GetResTypeByExt(const std::wstring& _relativepath)
{
	wchar_t szExt[50] = {};
	_wsplitpath_s(_relativepath.c_str(), 0, 0, 0, 0, 0, 0, szExt, 50);
	std::wstring strExt = szExt;

	if (L".mdat" == strExt)
		return eResourceType::End;
	else if (L".pref" == strExt)
		return eResourceType::Prefab;
	else if (L".mesh" == strExt)
		return eResourceType::Mesh;
	else if (L".mtrl" == strExt)
		return eResourceType::Material;
	else if (L".png" == strExt || L".jpg" == strExt
		|| L".jpeg" == strExt || L".bmp" == strExt
		|| L".tga" == strExt || L".dds" == strExt)
		return eResourceType::Texture;
	else if (L".mp3" == strExt || L".wav" == strExt || L".oga" == strExt)
		return eResourceType::Sound;
	else
		return eResourceType::End;
}

//GPT
#include <filesystem>
namespace fs = std::filesystem;
void listFiles(const std::wstring& path) 
{
	for (const auto& entry : fs::directory_iterator(path)) 
	{
		if (fs::is_regular_file(entry.path())) 
		{
			std::wstring path2 = entry.path();

			std::wstring len = gPathManager->GetResourcePath();
			path2 = path2.substr(len.length());
			eResourceType type = GetResTypeByExt(path2);

			switch (type)
			{
			case eResourceType::Texture:
				gResourceManager->Load<Texture>(path2);
				break;
			case eResourceType::Mesh:
				//gResourceManager->Load<Mesh>(path2);
				break;
			case eResourceType::Material:
				//gResourceManager->Load<Material>(path2);
				break;
			case eResourceType::Shader:
				//gResourceManager->Load<Material>(sha);
				//gResourceManager->Load<Material>(path2);
				break;
			case eResourceType::Animation:
				break;
			case eResourceType::Font:
				break;
			case eResourceType::Sound:
				break;
			case eResourceType::Scene:
				break;
			case eResourceType::Prefab:
				break;
			case eResourceType::ComputeShader:
				break;
			case eResourceType::AudioClip:
				break;
			case eResourceType::End:
				break;
			default:
				break;
			}

			(void)path2;
			(void)path2;
		}
		else if (fs::is_directory(entry.path())) 
		{
			listFiles(entry.path().wstring());
		}
	}
}
//GPT

Content::Content()
{
	{
		listFiles(gPathManager->GetResourcePath());

		//FBXLoadManager::Initialize();		
		//std::wstring relativePath = L"\\Fbx\\monster.fbx";

		//FBXLoader::LoadFBX(relativePath);
		//FBXLoader::FbxInstantiate(relativePath);

		//FBXLoadManager::GetInstance()->Load(relativePath);

	}
	Scene* testScene = new Scene;

	//gResourceManager->Load<Texture>(L"\\Texture\\Dragon_Bump_Col2.jpg");
	//gResourceManager->Load<Texture>(L"\\Texture\\Dragon_ground_color.jpg");
	//gResourceManager->Load<Texture>(L"\\Texture\\Dragon_Nor.jpg");
	//gResourceManager->Load<Texture>(L"\\Texture\\Dragon_Nor_mirror2.jpg");


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
		/*Texture* texture = gResourceManager->FindAndLoad<Texture>(L"\\texture\\TILE_01.tga");
		Texture* texture2 =
			gResourceManager->FindAndLoad<Texture>(L"\\texture\\TILE_01_N.tga");*/

		Shader* shader = 
			gResourceManager->FindAndLoad<Shader>(L"Std3D");

		//Mesh* panelMesh =
		//	gResourceManager->FindAndLoad<Mesh>(L"Panel");

		//Mesh* houseMesh =
		//	gResourceManager->FindAndLoad<Mesh>(L"houseMesh");

		material->SetShader(shader);
		//material->SetTexture(TEX_0, texture);
		//material->SetTexture(TEX_1, texture2);
		gResourceManager->Insert<Material>(L"default mat", material);


		//{
		//	GameObject* obj = FBXLoader::FbxInstantiate(L"\\Fbx\\house.fbx");
		//	//obj->AddComponent<MeshRenderer>();

		//	//obj->GetComponent<MeshRenderer>()->SetMaterial(material, 0);
		//	//obj->GetComponent<MeshRenderer>()->SetMesh(panelMesh);
		//	obj->SetName(L"House");
		//	Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
		//	//rotation.x = 90;
		//	obj->GetComponent<Transform>()->SetRotation(rotation);
		//	testScene->AddGameObject(obj, eLayerType::TileMap);
		//}		

		//{
		//	GameObject* obj = FBXLoader::FbxInstantiate(L"\\Fbx\\monster.fbx");
		//	obj->GetComponent<Transform>()->SetPosition(100.f, 1.f, 0.f);
		//	obj->SetName(L"monster");
		//	Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
		//	//rotation.x -= 90;
		//	obj->GetComponent<Transform>()->SetRotation(rotation);
		//	obj->GetComponent<Transform>()->SetScale(100.f, 100.f, 100.f);
		//	testScene->AddGameObject(obj, eLayerType::TileMap);
		//}

		{
			GameObject* obj = FBXLoader::FbxInstantiate(L"\\Fbx\\black.fbx");
			obj->GetComponent<Transform>()->SetPosition(100.f, 1.f, 0.f);
			obj->SetName(L"Dragon");
			Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
			//rotation.x -= 90;
			obj->GetComponent<Transform>()->SetRotation(rotation);
			obj->GetComponent<Transform>()->SetScale(10.f, 10.f, 10.f);
			testScene->AddGameObject(obj, eLayerType::TileMap);
		}

		//{
		//	GameObject* obj = FBXLoader::FbxInstantiate(L"\\Fbx\\c9990.fbx");
		//	obj->GetComponent<Transform>()->SetPosition(100.f, 1.f, 0.f);
		//	obj->SetName(L"Sekrio");
		//	Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
		//	//rotation.x -= 90;
		//	obj->GetComponent<Transform>()->SetRotation(rotation);
		//	obj->GetComponent<Transform>()->SetScale(100.f, 100.f, 100.f);
		//	testScene->AddGameObject(obj, eLayerType::TileMap);
		//}

		//{
		//	GameObject* obj = FBXLoader::FbxInstantiate(L"\\Fbx\\sphere.fbx");
		//	obj->GetComponent<Transform>()->SetPosition(100.f, 1.f, 0.f);
		//	obj->SetName(L"Dragon2");
		//	Vector3 rotation = obj->GetComponent<Transform>()->GetRotation();
		//	//rotation.x -= 90;
		//	obj->GetComponent<Transform>()->SetRotation(rotation);
		//	obj->GetComponent<Transform>()->SetScale(100.f, 100.f, 100.f);
		//	testScene->AddGameObject(obj, eLayerType::TileMap);
		//}

	}

	{
		GameObject* obj = new GameObject();
		obj->AddComponent<Light3D>();
		obj->SetName(L"Light3D");

		testScene->AddGameObject(obj, eLayerType::Light);
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
	//FBXLoadManager::DeleteInstance();
}
