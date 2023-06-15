#include "pch.h"
#include "Component.h"

namespace engine
{
	Component::Component(const eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::initialize()
	{

	}

	void Component::update()
	{

	}

	void Component::lateUpdate()
	{

	}

	void Component::render()
	{

	}
}