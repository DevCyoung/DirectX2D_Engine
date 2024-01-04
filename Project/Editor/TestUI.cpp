#include "pch.h"
#include "TestUI.h"

TestUI::TestUI()
{
	SetTitle("Resource Viewer");
}

TestUI::~TestUI()
{
}

void TestUI::drawForm()
{
	ImGui::Begin("Resource Viewer");	
	ImGui::Text("hello world!");
	ImGui::End();
}
