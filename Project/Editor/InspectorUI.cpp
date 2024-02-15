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
#include <ImGUI/imgui_filter.h>

#include <Engine/Texture.h>
#include <Engine/Material.h>
#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/ComputeShader.h>
#include <Engine/EnumResource.h>

#include "TextureUI.h"
#include "MaterialUI.h"
#include "MeshUI.h"
#include "ShaderUI.h"
#include "ComputeShaderUI.h"

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
	, mResource(nullptr)
{
	SetTitle("InspectorUI");
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::Register(GameObject* Object)
{
	mGameObject = Object;
	mResource = nullptr;
}

void InspectorUI::Register(Resource* resource)
{
	mResource = resource;
	mGameObject = nullptr;
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

		ImGui::Separator();

		static std::vector<std::string> selectItems;
		
		for (UINT i = 0; i < static_cast<UINT>(eComponentType::End); ++i)
		{
			eComponentType type = static_cast<eComponentType>(i);
			std::string str = helper::String::WStrToStr(GetComponentName(type));
			selectItems.push_back(str);
		}
		for (UINT i = 0; i < static_cast<UINT>(eScriptComponentType::End); ++i)
		{
			eScriptComponentType type = static_cast<eScriptComponentType>(i);
			std::string str = helper::String::WStrToStr(GetScriptComponentName(type));
			selectItems.push_back(str);
		}

		static bool showComponentSelect = true;
		int selectItem = 0;
		std::string ComponentSelect = "Component Select##";
		ComponentSelect += std::to_string(mGameObject->GetID());
		ImGui::SelectComboAutoSelectDemo(ComponentSelect.c_str(),
			selectItems, selectItem, &showComponentSelect);

		if (selectItem != -1)
		{		
			//component
			if (selectItem < static_cast<UINT>(eComponentType::End))				
			{									
				eComponentType type = static_cast<eComponentType>(selectItem);
				if (!mGameObject->GetComponentOrNull(type))
				{
					mGameObject->AddComponent(CreateComponentByEnum(type));
				}				
			}
			else
			{
				selectItem -= static_cast<UINT>(eComponentType::End);
				eScriptComponentType type = static_cast<eScriptComponentType>(selectItem);
				if (!mGameObject->GetComponentOrNull(type))
				{
					mGameObject->AddComponent(CreateScriptComponentByEnum(type));
				}
			}
		}

		selectItems.clear();
	}
	else if (mResource != nullptr)
	{
		eResourceType type = mResource->GetType();
		switch (type)
		{
		case eResourceType::Texture:
			TextureUI(static_cast<Texture*>(mResource));
			break;
		case eResourceType::Mesh:
			MeshUI(static_cast<Mesh*>(mResource));
			break;
		case eResourceType::Material:
			MaterialUI(static_cast<Material*>(mResource));
			break;
		case eResourceType::Shader:
			ShaderUI(static_cast<Shader*>(mResource));
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
			//PreUI(static_cast<Prefab*>(mResource));
			break;
		case eResourceType::ComputeShader:
			ComputeShaderUI(static_cast<ComputeShader*>(mResource));
			break;
		case eResourceType::AudioClip:
			break;		
		default:
			Assert(false, ASSERT_MSG_INVALID);
			break;
		}
	}

	ImGui::End();
}

void InspectorUI::update()
{

}
