#include "pch.h"
#include "GameVIewUI.h"

#include <Engine/Engine.h>
#include <Engine/Texture.h>
#include <Engine/InputManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/SceneManager.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/GraphicDeviceDx11.h>

#include "AlphaHelper.h"

#include <Engine/TimeManager.h>
void GameVIewUI::update()
{
	Texture* renderTex = ResourceManager::GetInstance()->Find<Texture>(L"/Editor/HDRenderTexture");
	Texture* depThTex = ResourceManager::GetInstance()->Find<Texture>(L"/Editor/HDDepthTexture");
	Scene* currentScene = SceneManager::GetInstance()->GetCurrentScene();	
	FLOAT backgroundColor[4] = {0.f, 1.0f, 1.f, 1.f};
	//currentScene->Render()

	gGraphicDevice->ClearRenderTarget(
		renderTex->GetAddressOf(),
		depThTex->GetDSV(), backgroundColor);

	currentScene->Render(
		static_cast<UINT>(renderTex->GetWidth()),
		static_cast<UINT>(renderTex->GetHeight()),
		renderTex->GetAddressOf(),
		depThTex->GetDSV());	

	//둘다 UAV여야함 /Editor/HDCopy
	//LARGE_INTEGER start;
	//TimeManager::GetInstance()->StartTime(&start);
	Texture* rwTex = gResourceManager->Find<Texture>(L"/Editor/HDRWTexture");
	Texture* rwTex2 = gResourceManager->Find<Texture>(L"/Editor/HDCopyRWTexture");
	gGraphicDevice->CopyResource(rwTex2->GetID3D11Texture2D(), renderTex->GetID3D11Texture2D());
	TextureAlphaTo(rwTex, rwTex2, 1.f);
	gGraphicDevice->CopyResource(renderTex->GetID3D11Texture2D(), rwTex->GetID3D11Texture2D());
	//float time = TimeManager::GetInstance()->EndTime(&start);
	Engine::GetInstance()->OmSet();
}
void GameVIewUI::drawForm()
{
	Texture* renderTex = ResourceManager::GetInstance()->Find<Texture>(L"/Editor/HDRenderTexture");
	ID3D11ShaderResourceView* texture = renderTex->GetSRV();

	//ImGui::SetNextWindowSize(ImVec2(renderTex->GetWidth(), renderTex->GetHeight()), ImGuiCond_FirstUseEver);
	ImGui::Begin("Game View");
	ImGui::SetNextWindowBgAlpha(0.00F);
	ImGui::Image((void*)texture, ImVec2(1280, 720));
	ImGui::End();
}
