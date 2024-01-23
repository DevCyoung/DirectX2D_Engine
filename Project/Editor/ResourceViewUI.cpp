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

ResourceViewUI::ResourceViewUI()
{
	for (UINT i = 0; i < static_cast<UINT>(eResourceType::End); ++i)
	{
		const ResourceManager::Dictionary& dictionary =
			ResourceManager::GetInstance()->GetDictionary(static_cast<eResourceType>(i));

		ResourceManager::Dictionary::const_iterator citer = dictionary.cbegin();
		ResourceManager::Dictionary::const_iterator cend = dictionary.cend();

		for (; citer != cend; ++citer)
		{
			ResourceUI* childUI = new ResourceUI;
			std::string relativePath = helper::String::WStrToStr(
				citer->second->GetRelativePath());

			childUI->SetName(relativePath);
			mResourceUI.AddResourceUI(childUI);
		}
	}
}

ResourceViewUI::~ResourceViewUI()
{
}

void ResourceViewUI::drawForm()
{
	ImGui::Begin("ResourceViewUI");
	mResourceUI.render();
	ImGui::End();
}

void ResourceViewUI::update()
{

}
