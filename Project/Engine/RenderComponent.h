#pragma once
#include "Component.h"

class Mesh;
class Material;
class Camera;

class RenderComponent : public Component
{
	friend class RenderTargetRenderer;

protected:
	RenderComponent(const eComponentType componentType);
	virtual ~RenderComponent();
	RenderComponent(const RenderComponent&) = delete;
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

protected:
	virtual void update() override;

private:
	virtual void initialize() override;	
	virtual void lateUpdate() override;
	virtual void render(const Camera* const camera) = 0;

protected:	
	bool mbVisible;
	Mesh* mMesh; 
	Material* mMaterial;
};
