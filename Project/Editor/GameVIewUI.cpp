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
#include <Engine/WindowManager.h>
#include "AlphaHelper.h"

#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>
void GameVIewUI::update()
{
	//Mouse
	

	//EngineInbox.SetRenderingPosition(screen_pos.x, screen_pos.y);
	//ImGui::Image((ImTextureID)GPU_GetImageHandle(engine_screen->image), ImVec2(engine_screen->w, engine_screen->h));
	 


	//Render
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
	//Window Pos는 화면 절대 좌표이다 왼쪽상단이 0,0
	//ImGui::SetWindowPos(ImVec2(0, 0));	
	
	//ImGui::SetNextWindowBgAlpha(0.00F);
	//ImGui::SetCursorPos(ImVec2(0,0));
	ImVec2 cursurScreenPos = ImGui::GetCursorScreenPos();
	ImVec2 renderTargetSize = ImVec2(renderTex->GetWidth(), renderTex->GetHeight());

	POINT ptMousePos = {};
	GetCursorPos(&ptMousePos);
	ImVec2 mousePos = ImVec2(ptMousePos.x, ptMousePos.y);
	ImGui::Image((void*)texture, renderTargetSize);
	ImVec2 screenMousePos = ImVec2(mousePos.x - cursurScreenPos.x,
		mousePos.y - cursurScreenPos.y);
	
	ImGui::Text("cursur posX%f cursur  posY%f", cursurScreenPos.x, cursurScreenPos.y);
	ImGui::Text("mouse posX%d mouse posY%d", ptMousePos.x, ptMousePos.y);
	ImGui::Text("In Screen Mouse Pos X%f Y%f", screenMousePos.x, screenMousePos.y);
	WindowManager::GetInstance()->SetWindowScreenPos(Vector2(screenMousePos.x, screenMousePos.y));


	if (gInput->GetKeyDown(eKeyCode::Q))
	{
		ImVec2 cursurPos = ImGui::GetCursorPos(); //현재 윈도우기준
		ImVec2 windowPos = ImGui::GetWindowPos();
		//ImVec2 pos = ImGui::GetCursorScreenPos();
		int a = 3;
		(void)a;
	}

	ImGui::End();
}
