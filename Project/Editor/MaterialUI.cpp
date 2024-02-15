#include "pch.h"
#include "MaterialUI.h"
#include <Engine/Texture.h>
#include <Engine/Material.h>
#include <Engine/ResourceManager.h>
#include <Engine/String.h>

#include <ImGUI/imgui_filter.h>

void MaterialUI(Material* material)
{
	const ResourceManager::Dictionary& dictionary =
		ResourceManager::GetInstance()->GetDictionary(eResourceType::Texture);

	std::vector<std::string> selectItems;

	ResourceManager::Dictionary::const_iterator citer = dictionary.cbegin();
	ResourceManager::Dictionary::const_iterator cend = dictionary.cend();

	ImVec2 renderTargetSize = ImVec2(200.f, 200.f);

	static int selectIdx = -1;
	static Texture* prevTex = nullptr;

	for (; citer != cend; ++citer)
	{
		std::string patah = helper::String::WStrToStr(citer->first);
		if (patah.front() != '\\')
		{
			continue;
		}
		selectItems.push_back(patah);
	}

	for (int i = 0; i <= TEX_7; ++i)
	{
		if (material->GetTextureOrNull((TEX_PARAM)i))
		{
			ID3D11ShaderResourceView* rv =
				material->GetTextureOrNull((TEX_PARAM)i)->GetSRVOrNull();
			ImGui::Image((void*)rv, renderTargetSize);
			std::string textureSelectButton = "##ShaderSelectBtn_";
			textureSelectButton += std::to_string(i);
			ImGui::SameLine();

			if (ImGui::Button(textureSelectButton.c_str(), ImVec2(18, 18)))
			{
				selectIdx = i;
				prevTex = material->GetTexture(TEX_PARAM(i));
				ImGui::OpenPopup("Stacked 111");
			}
		}
	}

	if (ImGui::Button("Add Textrue##MaterialUI"))
	{
		ImGui::OpenPopup("Stacked 222");
	}

	if (ImGui::BeginPopupModal("Stacked 111", NULL, ImGuiWindowFlags_MenuBar))
	{

		if (ImGui::Button("revert##Material"))
		{
			material->SetTexture(TEX_PARAM(selectIdx), prevTex);
		}
		ImGui::SameLine();
		if (ImGui::Button("close##Material"))
		{
			ImGui::CloseCurrentPopup();
		}

		int texOrder = 0;
		for (const std::string& item : selectItems)
		{
			Texture* tex =
				gResourceManager->FindOrNull<Texture>(helper::String::StrToWStr(item).c_str());

			if (ImGui::ImageButton(tex->GetSRVOrNull(), ImVec2(100.f, 100.f)))
			{
				material->SetTexture(TEX_PARAM(selectIdx), tex);
			}

			++texOrder;


			if (texOrder % 5 != 0)
			{
				ImGui::SameLine();
			}

		}

		ImGui::EndPopup();
	}


	if (ImGui::BeginPopupModal("Stacked 222", NULL, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::Button("close##Material"))
		{
			ImGui::CloseCurrentPopup();
		}

		int texOrder = 0;

		static int texNum = 0;

		ImGui::InputInt("##Material Input Int", &texNum);

		for (const std::string& item : selectItems)
		{
			Texture* tex =
				gResourceManager->FindOrNull<Texture>(helper::String::StrToWStr(item).c_str());

			if (ImGui::ImageButton(tex->GetSRVOrNull(), ImVec2(100.f, 100.f)))
			{
				material->SetTexture(TEX_PARAM(texNum), tex);
			}

			++texOrder;


			if (texOrder % 5 != 0)
			{
				ImGui::SameLine();
			}

		}

		ImGui::EndPopup();
	}
}
