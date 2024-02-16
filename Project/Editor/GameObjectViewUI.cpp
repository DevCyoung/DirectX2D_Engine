#include "pch.h"
#include "GameObjectViewUI.h"
#include <Engine/SceneManager.h>
#include <Engine/Layer.h>
#include <Engine/String.h>
#include <Engine/GameObject.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"
GameObjectViewUI::GameObjectViewUI()
{
}

GameObjectViewUI::~GameObjectViewUI()
{
}

void GameObjectViewUI::update()
{	
}

void GameObjectViewUI::drawForm()
{
	Scene* curScene = SceneManager::GetInstance()->GetCurrentScene();
	ImGui::Begin("GameObjectViewUI");

	for (UINT i = 0; i < static_cast<UINT>(eLayerType::End); ++i)
	{
		Layer& layer = curScene->GetLayer(static_cast<eLayerType>(i));

		std::vector<GameObject*>& gameObjects = layer.GetGameObjects();

		for (GameObject* gameObject : gameObjects)
		{
			
			std::string itemName = helper::String::WStrToStr(gameObject->GetName());
			ImGui::Bullet();
			ImGui::Selectable(itemName.c_str(), false);
			if (ImGui::IsItemClicked())
			{
				ImGui::SetMouseCursor(0);
				PanelUI* inspectorUI =
					PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI");
				static_cast<InspectorUI*>(inspectorUI)->Register(gameObject);
			}
		}

	}

	//ImGui::Text("Hello world!");
	ImGui::End();
}
