#include "pch.h"
#include "EditorUIInitialize.h"
#include "PanelUIManager.h"

#include "TestUI.h"
#include "TestUI2.h"
#include "ESCUI.h"
#include "InspectorUI.h"
#include "EditorViewUI.h"
#include "GameViewUI.h"
#include "LogUI.h"
void EditorUIInitialize()
{		
	AddPanel(new TestUI);
	AddPanel(new TestUI2);	
	AddPanel(new ESCUI);
	AddPanel(new InspectorUI);
	AddPanel(new EditorViewUI);
	AddPanel(new GameViewUI);
	AddPanel(new LogUI);
}

void AddPanel(PanelUI* const panelUI)
{
	Assert(panelUI, ASSERT_MSG_NULL);

	PanelUIManager::GetInstance()->AddPanel(panelUI);
}
