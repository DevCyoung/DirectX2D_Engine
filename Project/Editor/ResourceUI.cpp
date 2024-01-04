#include "pch.h"
#include "ResourceUI.h"
#include <Engine/String.h>
//itemUI name in resoruce relative file path
void ResourceUI::AddResourceUI(ItemUI* const itemUI)
{
	std::string relativePath = itemUI->GetName();

	const std::wstring& wRelativePath = helper::String::StrToWStr(relativePath);
	std::wstring wOutRootName;
	std::wstring wOutFilePath;

	helper::String::SplitRootNameAndFilePath(wRelativePath, &wOutRootName, &wOutFilePath);

	//myRootName
	mRootName = helper::String::WStrToStr(wOutRootName);
	std::string outFilePath = helper::String::WStrToStr(wOutFilePath);
}
