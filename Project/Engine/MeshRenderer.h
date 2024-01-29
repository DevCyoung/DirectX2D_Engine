#pragma once
#include "RenderComponent.h"

REGISTER_COMPONENT_TYPE(MeshRenderer);

class MeshRenderer : public RenderComponent
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();
	//SpriteRenderer(const SpriteRenderer&);
	MeshRenderer& operator=(const MeshRenderer&) = delete;

	CLONE(MeshRenderer);
	virtual void render(const Camera* const camera);
};

