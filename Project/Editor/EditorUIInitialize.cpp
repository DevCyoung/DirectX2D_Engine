#include "pch.h"
#include "EditorUIInitialize.h"
#include "PanelUIManager.h"

#include "TestUI.h"
#include "TestUI2.h"
#include "ESCUI.h"
#include "InspectorUI.h"

void EditorUIInitialize()
{		
	AddPanel(new TestUI);
	AddPanel(new TestUI2);	
	AddPanel(new ESCUI);
	AddPanel(new InspectorUI);
}

void AddPanel(PanelUI* const panelUI)
{
	Assert(panelUI, WCHAR_IS_NULLPTR);

	PanelUIManager::GetInstance()->AddPanel(panelUI);
}
