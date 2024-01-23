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

	//추상화
	if (nullptr != mGameObject)
	{
		for (int i = 0; i < static_cast<UINT>(eComponentType::End); ++i)
		{
			Component* engineComponent = 
				mGameObject->GetComponentOrNull(static_cast<eComponentType>(i));
			if (engineComponent)
			{
				eComponentType type =  engineComponent->GetType();
				std::wstring wstr = GetComponentName(type);
				std::string str = helper::String::WStrToStr(wstr);
				//함수포인터
				ImGui::Text(str.c_str());		
			}
		}
		
		std::vector<ScriptComponent*>& scriptComponents = 
			mGameObject->GetScriptComponents();

		for (ScriptComponent* scriptCompnent : scriptComponents)
		{							
			eScriptComponentType type = scriptCompnent->GetScriptType();
			std::wstring wstr = GetScriptComponentName(type);
			std::string str = helper::String::WStrToStr(wstr);
			ImGui::Text(str.c_str());
		}
	}

	ImGui::End();
}

void InspectorUI::update()
{

}
