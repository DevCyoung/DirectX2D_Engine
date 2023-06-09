#pragma once
#include "Component.h"
#include "ScriptComponentTrait.h"

class ScriptComponent : public Component
{
	friend class GameObject;
protected:
	ScriptComponent(eScriptComponentType scriptComonentType);
public:
	virtual ~ScriptComponent();
	ScriptComponent(const ScriptComponent&) = delete;
	ScriptComponent& operator=(const ScriptComponent&) = delete;

	eScriptComponentType GetScriptType() const { return mScriptType; }	

private:
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;	

private:
	eScriptComponentType mScriptType;
};
