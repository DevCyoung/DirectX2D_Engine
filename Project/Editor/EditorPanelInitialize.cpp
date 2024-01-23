#include "pch.h"
#include "EditorPanelInitialize.h"
#include "PanelUIManager.h"

#include "TestUI.h"
#include "TestUI2.h"
#include "ESCUI.h"
#include "InspectorUI.h"
#include "EditorViewUI.h"
#include "GameViewUI.h"
#include "LogUI.h"
#include "GameObjectViewUI.h"
#include "ResourceViewUI.h"

void EditorPanelInitialize()
{		
	AddPanel(new TestUI);
	AddPanel(new TestUI2);	
	AddPanel(new ESCUI);
	AddPanel(new InspectorUI);
	AddPanel(new ResourceViewUI);
	AddPanel(new EditorViewUI);
	AddPanel(new GameViewUI);
	AddPanel(new GameObjectViewUI);
	AddPanel(new LogUI);
}

void AddPanel(PanelUI* const panelUI)
{
	Assert(panelUI, ASSERT_MSG_NULL);

	PanelUIManager::GetInstance()->AddPanel(panelUI);
}
