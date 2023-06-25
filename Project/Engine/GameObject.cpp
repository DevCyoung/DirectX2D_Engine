#include "pch.h"
#include "GameObject.h"

namespace engine
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mEngineComponents{0, }
	{
		//��� ������Ʈ�� �ݵ�� Transform �� �������ִ´�.
		AddComponent(new Transform);
	}

	GameObject::~GameObject()
	{
		memory::safe::DeleteVec(mUserComponents);
		memory::unsafe::DeleteArray(mEngineComponents);
	}

	
	
	void GameObject::initialize()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->initialize();
			}
		}

		for (Script* const script : mUserComponents)
		{
			script->initialize();
		}
	}

	void GameObject::update()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->update();
			}
		}

		for (Script* const script : mUserComponents)
		{
			script->update();
		}

	}

	void GameObject::lateUpdate()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->lateUpdate();
			}
		}

		for (Script* const script : mUserComponents)
		{
			script->lateUpdate();
		}
	}

	void GameObject::render(/*mGraphicDevice*/)
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->render();
			}
		}


		for (Script* const script : mUserComponents)
		{
			script->render();
		}
	}
}