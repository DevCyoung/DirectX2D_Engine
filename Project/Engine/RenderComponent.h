#pragma once
#include "Component.h"

class Mesh;
class Material;
class Camera;

REGISTER_COMPONENT_TYPE(RenderComponent);

class RenderComponent : public Component
{
	friend class RenderTargetRenderer;

public:
	RenderComponent();
	virtual ~RenderComponent();
	RenderComponent(const eComponentType componentType);
	//RenderComponent(const RenderComponent&);
	RenderComponent& operator=(const RenderComponent&) = delete;

public:
	Mesh* GetMesh() const { Assert(mMesh, ASSERT_MSG_NULL); return mMesh; }
	Material* GetMaterial() const { Assert(mMaterial, ASSERT_MSG_NULL); return mMaterial; }
	bool IsVisible() const { return mbVisible; }

	void SetMesh(Mesh* const mesh) { Assert(mesh, ASSERT_MSG_NULL); mMesh = mesh; }
	void SetMaterial(Material* const material) { Assert(material, ASSERT_MSG_NULL); mMaterial = material; }
	//void SetVisible(const bool visible) { mbVisible = visible; }

	void TurnOnVisiblelity() { mbVisible = true; }
	void TurnOffVisiblelity() { mbVisible = false; }

	
	CLONE(RenderComponent)

protected:
	virtual void update() override;

private:
	virtual void initialize() override;	
	virtual void lateUpdate() override;
	virtual void render(const Camera* const camera)
	{
		(void)camera;
		Assert(false, ASSERT_MSG_INVALID);
	};

protected:	
	bool mbVisible;
	Mesh* mMesh; 
	Material* mMaterial;
};
