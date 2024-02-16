#include "pch.h"
#include "ResourceViewUI.h"
#include "ResourceUI.h"

#include <Engine/SceneManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/GameSystem.h>
#include <Engine/GameObject.h>
#include <Engine/String.h>
#include <Engine/Texture.h>
#include <Engine/EnumResource.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"

ResourceViewUI::ResourceViewUI()
{
	//for (UINT i = 0; i < static_cast<UINT>(eResourceType::End); ++i)
	//{
	//	const ResourceManager::Dictionary& dictionary =
	//		ResourceManager::GetInstance()->GetDictionary(static_cast<eResourceType>(i));

	//	ResourceManager::Dictionary::const_iterator citer = dictionary.cbegin();
	//	ResourceManager::Dictionary::const_iterator cend = dictionary.cend();

	//	for (; citer != cend; ++citer)
	//	{
	//		ResourceUI* childUI = new ResourceUI;
	//		std::string relativePath = 
	//			helper::String::WStrToStr(citer->second->GetRelativePath());
	//		
	//		childUI->SetName(relativePath);
	//		childUI->SetFullName(relativePath);
	//		childUI->SetResource(citer->second);
	//		mResourceUI.AddResourceUI(childUI);
	//	}
	//}
}

ResourceViewUI::~ResourceViewUI()
{
}

std::string GetTypeName(eResourceType type)
{
	std::string result;
	switch (type)
	{
	case eResourceType::Texture:
		result = "Texture";
		break;
	case eResourceType::Mesh:
		result = "Mesh";
		break;
	case eResourceType::Material:
		result = "Material";
		break;
	case eResourceType::Shader:
		return "Sahder";
		break;
	case eResourceType::Animation:
		result = "Animation";
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
		result = "ComputeShader";
		break;
	case eResourceType::AudioClip:
		break;
	case eResourceType::End:
		break;
	default:
		Assert(false, ASSERT_MSG_INVALID);
		break;
	}

	return result;
}

void ResourceViewUI::drawForm()
{
	ImGui::Begin("ResourceViewUI");

	for (UINT i = 0; i < static_cast<UINT>(eResourceType::End); ++i)
	{
		const ResourceManager::Dictionary& dictionary =
			ResourceManager::GetInstance()->GetDictionary(static_cast<eResourceType>(i));

		//if (dictionary.size())

		ResourceManager::Dictionary::const_iterator citer = dictionary.cbegin();
		ResourceManager::Dictionary::const_iterator cend = dictionary.cend();

		std::string typeName = GetTypeName(static_cast<eResourceType>(i));		
		typeName += "##ResourceViewUI";

		if (ImGui::CollapsingHeader((typeName).c_str()))
		{
			for (; citer != cend; ++citer)
			{
				std::string relativePath =
					helper::String::WStrToStr(citer->second->GetRelativePath());
				ImGui::Bullet();
				ImGui::Selectable(relativePath.c_str(), false);
				if (ImGui::IsItemClicked())
				{
					//ImGui::SetMouseCursor(0);
					PanelUI* inspectorUI =
						PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI");
					static_cast<InspectorUI*>(inspectorUI)->Register(citer->second);
				}

			}			
		}
	}

	ImGui::End();
}

void ResourceViewUI::update()
{

}
