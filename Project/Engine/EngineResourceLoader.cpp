#include "pch.h"
#include "EngineResourceLoader.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "ComputeShader.h"
#include "StructVertex.h"
#include "EngineMath.h"

void EngineResourceLoader::loadResource()
{
	loadMesh();
	loadShader();
	loadComputeShader();
	loadTexture();
}

void EngineResourceLoader::loadMesh()
{
	//fill rect mesh
	{
		constexpr UINT VERTEX_COUNT = 4;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexArray[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.4f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexArray[1].color = Vector4(0.0f, 0.3f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 0.0f);

		vertexArray[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexArray[2].color = Vector4(0.0f, 0.0f, 0.4f, 1.0f);
		vertexArray[2].uv = Vector2(1.0f, 1.0f);

		vertexArray[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexArray[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexArray[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		gResourceManager->Insert(L"FillRect2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line rect mesh
	{
		constexpr UINT VERTEX_COUNT = 4;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexArray[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexArray[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 0.0f);

		vertexArray[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexArray[2].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[2].uv = Vector2(1.0f, 1.0f);

		vertexArray[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexArray[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);


		gResourceManager->Insert(L"LineRect2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//fill circle mesh
	{
		constexpr UINT VERTEX_COUNT = 100;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2

		// pivot
		vertexArray[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		const float anglePer = 360.f / (VERTEX_COUNT - 1);

		for (int i = 1; i < VERTEX_COUNT; ++i)
		{
			const float y = sin(Deg2Rad(anglePer * (i - 1))) * 0.5f;
			const float x = cos(Deg2Rad(anglePer * (i - 1))) * 0.5f;

			const float uvx = x * 0.5f;
			const float uvy = -y * 0.5f;


			//cos(Rad2DE)

			vertexArray[i].pos = Vector3(x, y, 0.0f);
			vertexArray[i].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
			vertexArray[i].uv = Vector2(uvx, uvy);
		}

		std::vector<UINT> indexes;
		indexes.reserve(VERTEX_COUNT);

		//pivot
		for (int i = 0; i < VERTEX_COUNT - 2; ++i)
		{
			indexes.push_back(0);
			indexes.push_back(1 + i);
			indexes.push_back(2 + i);
		}

		indexes.push_back(1);
		indexes.push_back(0);
		indexes.push_back(VERTEX_COUNT - 1);




		gResourceManager->Insert(L"FillCircle2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line circle mesh
	{
		constexpr UINT VERTEX_COUNT = 100;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2

		// pivot
		vertexArray[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		const float anglePer = 360.f / (VERTEX_COUNT);

		for (int i = 0; i < VERTEX_COUNT; ++i)
		{
			const float x = cos(Deg2Rad(anglePer * (i - 1))) * 0.5f;
			const float y = sin(Deg2Rad(anglePer * (i - 1))) * 0.5f;

			const float uvx = x + 0.5f;
			const float uvy = -y + 0.5f;

			vertexArray[i].pos = Vector3(x, y, 0.0f);
			vertexArray[i].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
			vertexArray[i].uv = Vector2(uvx, uvy);
		}

		std::vector<UINT> indexes;
		indexes.reserve(VERTEX_COUNT);

		//pivot
		for (int i = 0; i < VERTEX_COUNT; ++i)
		{
			indexes.push_back(i);
		}
		indexes.push_back(0);

		gResourceManager->Insert(L"LineCircle2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line mesh
	{
		constexpr UINT VERTEX_COUNT = 2;
		tVertex vertexArray[VERTEX_COUNT] = {};

		vertexArray[0].pos = Vector3(-0.5f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.0f, 0.0f);
		vertexArray[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);

		gResourceManager->Insert(L"Line",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}
}

void EngineResourceLoader::loadTexture()
{
	{
		Texture* const defaultTexture = new Texture(1024, 1024,
			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
			D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
			D3D11_USAGE::D3D11_USAGE_DEFAULT);

		gResourceManager->Insert(L"TextureCS", defaultTexture);
	}

	{
		/*XMUINT2 size = { static_cast<UINT>(gEngine->GetRenderTargetSize().x),  
						 static_cast<UINT>(gEngine->GetRenderTargetSize().y)};*/
		//FIXME 다시 고칠것 하드코딩으로 해결

		XMUINT2 size = { static_cast<UINT>(1280),
						 static_cast<UINT>(720) };

		Texture* const copyRenderTargetTexture = new Texture(size.x, size.y,
			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
			D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
			D3D11_USAGE::D3D11_USAGE_DEFAULT);

		gResourceManager->Insert(L"CopyRenderTargetTexture", copyRenderTargetTexture);
	}

	//Noise
	{

	}

}

void EngineResourceLoader::loadShader()
{
	//Animation2D
	{
		Shader* const animationShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSAnimation2D.hlsl", L"main",
				L"\\Shader\\PSAnimation2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"Animation2D", animationShader);
	}

	//Fill2D Debug
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSFillDebug2D.hlsl", L"main",
				L"\\Shader\\PSFillDebug2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"FillDebug2D", debugShader);
	}

	//Grid2D Debug
	{
		Shader* const debugGridShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSGrid2D.hlsl", L"main",
				L"\\Shader\\PSGrid2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"DebugGrid2D", debugGridShader);
	}

	//Line2D Debug
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
				L"\\Shader\\VSLineDebug2D.hlsl", L"main",
				L"\\Shader\\PSLineDebug2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"LineDebug2D", debugShader);
	}

	//Sprite 
	{
		Shader* const sprite2DShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSSprite2D.hlsl", L"main",
				L"\\Shader\\PSSprite2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"Sprite2D", sprite2DShader);
	}

	//UI
	{
		Shader* const UIShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSUI2D.hlsl", L"main",
				L"\\Shader\\PSUI2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"UI2D", UIShader);
	}

	//Light

	//Light Sprite
	{
		Shader* const sprite2DShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSLightSprite2D.hlsl", L"main",
				L"\\Shader\\PSLightSprite2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"LightSprite2D", sprite2DShader);
	}

	//Light Animation2D
	{
		Shader* const animationShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSLightAnimation2D.hlsl", L"main",
				L"\\Shader\\PSLightAnimation2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);

		gResourceManager->Insert(L"LightAnimation2D", animationShader);
	}

	//AfterImage
	{
		Shader* const animationShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSAfterImage.hlsl", L"main",
				L"\\Shader\\PSAfterImage.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);

		gResourceManager->Insert(L"AfterImage", animationShader);
	}

	//Next Scene
	{
		Shader* const animationShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSNextScene.hlsl", L"main",
				L"\\Shader\\PSNextScene.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::LessEqual,
				eBSType::AlphaBlend);

		gResourceManager->Insert(L"NextScene", animationShader);
	}

	//Post Process
	{
		Shader* const grayPostProcess =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSGrayPostProcess.hlsl", L"main",
				L"\\Shader\\PSGrayPostProcess.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::NoWrite,
				eBSType::AlphaBlend);

		gResourceManager->Insert(L"GrayPostProcess", grayPostProcess);
	}

	{
		Shader* const wavePostProcess =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSWave.hlsl", L"main",
				L"\\Shader\\PSWave.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::NoWrite,
				eBSType::AlphaBlend);

		gResourceManager->Insert(L"WavePostProcess", wavePostProcess);
	}
}

void EngineResourceLoader::loadComputeShader()
{
	//stdCS
	{
		ComputeShader* const stdCS =
			new ComputeShader(L"\\Shader\\stdCS.hlsl", L"main");

		gResourceManager->Insert(L"StdCS", stdCS);
	}
}
