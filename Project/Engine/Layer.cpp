#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
	:mGameObjects()
{
}

Layer::~Layer()
{
	mem::del::DeleteVectorElements(&mGameObjects);
}

void Layer::initialize()
{
	for (GameObject* const gameObject : mGameObjects)
	{
		if (gameObject->mState == GameObject::eState::Active)
		{
			gameObject->initialize();
		}
	}
}

void Layer::update()
{
	for (GameObject* const gameObject : mGameObjects)
	{
		if (gameObject->mState == GameObject::eState::Active)
		{
			gameObject->update();
		}
	}
}

void Layer::fixedUpdate()
{
	for (GameObject* const gameObject : mGameObjects)
	{
		if (gameObject->mState == GameObject::eState::Active)
		{
			gameObject->fixedUpdate();
		}
	}
}

void Layer::lateUpdate()
{
	for (GameObject* const gameObject : mGameObjects)
	{
		if (gameObject->mState == GameObject::eState::Active)
		{
			gameObject->lateUpdate();
		}
	}	
}

void Layer::lastUpdate()
{
	for (GameObject* const gameObject : mGameObjects)
	{
		if (gameObject->mState == GameObject::eState::Active)
		{
			gameObject->lastUpdate();
		}
	}
}
