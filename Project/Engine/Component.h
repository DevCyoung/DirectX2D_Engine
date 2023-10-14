#pragma once
#include "Entity.h"
#include "GameObject.h"

class Component : public Entity
{
	friend class GameObject;

protected:
	Component(const eComponentType COMPONENT_TYPE);
public:
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

public:
	GameObject* GetOwner() const { Assert(mOwner, WCHAR_IS_NULLPTR); return mOwner; }	
	eComponentType GetType() const { return mType; }

private:
	virtual void initialize();
	virtual void update();
	virtual void fixedUpdate();
	virtual void lateUpdate();
	virtual void lastUpdate();

private:
	eComponentType mType;
	GameObject* mOwner;
};

