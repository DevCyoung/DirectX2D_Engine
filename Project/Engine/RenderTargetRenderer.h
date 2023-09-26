#pragma once
#include <d3d11.h>
#include "Singleton.h"
#include "EnumRenderType.h"
#include "StructBuffer.h"

class Camera;
class RenderComponent;
class DebugRenderer2D;
class Light2D;

class RenderTargetRenderer
{
	friend class Camera;
	friend class RenderComponent;
	friend class Light2D;
	friend class Scene;

public:
	RenderTargetRenderer();
	virtual ~RenderTargetRenderer();

	void Render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const;

	Camera* GetRegisteredRenderCameraOrNull(const eCameraPriorityType priorityType) const
	{		
		return mCameras[static_cast<UINT>(priorityType)];
	}

	Camera* GetRegisteredRenderCamera(const eCameraPriorityType priorityType) const
	{		
		Assert(mCameras[static_cast<UINT>(priorityType)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(priorityType)];
	}


	DebugRenderer2D* GetDebugRenderer2D() const { Assert(mDebugRenderer, WCHAR_IS_NULLPTR); return mDebugRenderer; }

	void TurnOnAllCamera()  { mCameraMask = 0XFFFFFFFF; }
	void TurnOffAllCamera() { mCameraMask = 0; }

	void TurnOnCamera(const eCameraPriorityType priorityType) 
	{
		mCameraMask |= (1 << static_cast<UINT>(priorityType));
	}

	void TurnOffCamera(const eCameraPriorityType priorityType)
	{
		mCameraMask &= ~(1 << static_cast<UINT>(priorityType));
	}

	void TurnOnDebugRenderer() { mbDebugRender = true; }
	void TurnOffDebugRenderer() { mbDebugRender = false; }

private:
	void registerRenderCamera(Camera* const camera);
	void registerRenderComponent(RenderComponent* const renderComponent);
	void registerLightInfo(const tLightInfo& light2DInfo);

	void zSortRenderObjectArray(const eRenderPriorityType priorityType);
	void flush();

private:
	DebugRenderer2D* mDebugRenderer;
	Camera* mCameras[static_cast<UINT>(eCameraPriorityType::End)];
	std::vector<RenderComponent*> mRenderComponentsArray[static_cast<UINT>(eRenderPriorityType::End)];
	std::vector<RenderComponent*> mPostProcessComponents;
	std::vector<tLightInfo> mLight2DInfos;
	bool mbDebugRender;
	UINT mCameraMask;
};
