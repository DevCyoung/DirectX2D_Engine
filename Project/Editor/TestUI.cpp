#include "pch.h"
#include "TestUI.h"

TestUI::TestUI()
{
	SetTitle("TestUI");
}

TestUI::~TestUI()
{
}

void TestUI::drawForm()
{
	//ImGui::ShowDemoWindow();
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!!");
	ImGui::Text("This is some useful text.");               // Display some text (you can use a format
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	if (ImGui::Button("Button"))
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	ImGui::End();
}
