#pragma once
#include "Component.h"
#include "ScriptComponentTrait.h"

class Collider2D;

class ScriptComponent : public Component
{
	friend class GameObject;
	friend class Collider2D;

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
	virtual void lastUpdate() override;

	virtual void onCollisionEnter(Collider2D* other);
	virtual void onCollisionStay(Collider2D* other);
	virtual void onCollisionExit(Collider2D* other);

private:
	eScriptComponentType mScriptType;
};
