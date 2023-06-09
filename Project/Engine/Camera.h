#pragma once
#include "Component.h"
#include "EnumRenderType.h"

REGISTER_COMPONENT_TYPE(Camera);

class RenderTargetRenderer;

enum class eLayerType;

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	float GetFOV() const { return mFOV; }
	float GetNear() const { return mNear; }
	float GetFar() const { return mFar; }
	float GetCameraSize() const { return mSize; }
	float GetAspectRatio() const { return mAspectRatio; }
	const Matrix& GetView() const { return mView; }
	const Matrix& GetProjection() const { return mProjection; }
	eCameraPriorityType GetPriorityType () const { return mCameraType; }
	UINT GetLayerMask() const { return mLayerMask; }
	eCameraProjectionType GetProjectionType() const { return mProjectionType; }

	void Set3DFOV(const float fov) { mFOV = fov; }
	void SetNear(const float cameraNear) { mNear = cameraNear; }
	void SetFar(const float cameraFar) { mFar = cameraFar; }
	void Set2DSize(const float camera2DSize) { mSize = camera2DSize; }
	void SetRenderTargetSize(const Vector2& renderTargetSize) { mRenderTargetSize = renderTargetSize; };
	void SetProjectionType(const eCameraPriorityType cameraPriorityType) { mCameraType = cameraPriorityType; }
	void SetProjectiontType(const eCameraProjectionType projectionType) { mProjectionType = projectionType; }

	void TurnOnLayer(const  eLayerType layerType)  { mLayerMask |=  (1 <<  static_cast<UINT>(layerType)); }
	void TurnOffLayer(const eLayerType layerType)  { mLayerMask &= ~(1 <<  static_cast<UINT>(layerType)); }

	void TurnOnAllLayer()  { mLayerMask = 0XFFFFFFFF; }
	void TurnOffAllLayer() { mLayerMask = 0; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

private:
	Vector2 mRenderTargetSize;

	UINT mLayerMask;

	float mNear;
	float mFar;
	float mFOV;
	float mSize;
	float mAspectRatio;

	Matrix mView;
	Matrix mProjection;

	eCameraProjectionType mProjectionType;
	eCameraPriorityType mCameraType;
};
