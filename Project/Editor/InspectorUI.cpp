#include "pch.h"
#include "InspectorUI.h"
#include "ResourceUI.h"

//#include <Engine/SceneManager.h>
//#include <Engine/ResourceManager.h>
//#include <Engine/GameSystem.h>
//#include <Engine/GameObject.h>
//#include <Engine/String.h>
//#include <Engine/Texture.h>
//#include <Engine/EnumResource.h>

#include <Engine/EnumComponent.h>
#include <Content/EnumScriptComponent.h>
#include <Engine/GameObject.h>
//#include <Engine/Component.h>
#include <Engine/ScriptComponent.h>
#include <Engine/String.h>
#include "ComponentUIRender.h"

static void RenderComponentName(std::string str)
{
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f , 0.0f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f , 0.2f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.2f , 0.8f, 0.6f));
	ImGui::Button(str.c_str());
	ImGui::PopStyleColor(3);
	ImGui::PopID();
}

InspectorUI::InspectorUI()
	: mGameObject(nullptr)
{
	SetTitle("InspectorUI");
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::drawForm()
{	
	ImGui::Begin("InspectorUI");
	//mResourceUI.render();

	//Ãß»óÈ­
	if (nullptr != mGameObject)
	{
		std::string name = helper::String::WStrToStr(mGameObject->GetName());
		ImGui::Bullet();
		ImGui::Text("%s\t\t\t%d", name.c_str(), mGameObject->GetID());		

		for (int i = 0; i < static_cast<UINT>(eComponentType::End); ++i)
		{
			Component* engineComponent = 
				mGameObject->GetComponentOrNull(static_cast<eComponentType>(i));
			if (engineComponent)
			{				
				eComponentType type = engineComponent->GetType();
				std::wstring wstr = GetComponentName(type);
				std::string str = helper::String::WStrToStr(wstr);		
				RenderComponentName(str);
				ComponentUIRender(engineComponent);					
			}
		}
		
		std::vector<ScriptComponent*>& scriptComponents = 
			mGameObject->GetScriptComponents();

		for (ScriptComponent* scriptCompnent : scriptComponents)
		{		
			eScriptComponentType type = scriptCompnent->GetScriptType();
			std::wstring wstr = GetScriptComponentName(type);
			std::string str = helper::String::WStrToStr(wstr);
			RenderComponentName(str);
			ComponentUIRender(scriptCompnent);
		}
	}

	ImGui::End();
}

void InspectorUI::update()
{

}
