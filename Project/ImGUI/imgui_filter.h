#pragma once
// Add this header file to enable use of ComboAutoSelect demo function
#include <vector>
#include <array>
#include <span>
#include <string>
namespace ImGui
{
	void ShowComboAutoSelectDemo(bool* p_open = nullptr);
	void ShowComboFilterDemo(bool* p_open = nullptr);
	void SelectComboAutoSelectDemo(const char* title, const std::vector<std::string>& vector, 
		int& selected_item, bool* p_open = nullptr);
}