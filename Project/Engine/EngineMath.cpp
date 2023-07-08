#include "pch.h"
#include "Engine.h"
#include "EngineMath.h"
#include "Camera.h"
#include "Transform.h"
#include "InputManager.h"

/*
* ���� ���� ����ϴ� UI ��ǥ��� ������ ��ǥ��� �����ϰ� ����մϴ�.
* ������ ��ǥ��� ���� ����� (0, 0)�̰� ������ �ϴ��� (width, height)�Դϴ�.
*/

namespace helper
{
	Vector2 RenderTargetToWorldUI(const Vector2& renderTargetMousePos, const Vector2& renderTargetSize)
	{
		return Vector2(renderTargetMousePos.x - renderTargetSize.x / 2, -renderTargetMousePos.y + renderTargetSize.y / 2);
	}

	Vector3 ScreenMouseToWorld3D(const Vector3& screenMousePos, const Vector2& screenSize, const Camera* const camera)
	{
		Viewport viewport = {};
		viewport.width = screenSize.x;
		viewport.height = screenSize.y;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		const Vector3& mouseWorldPos3D = 
			viewport.Unproject(screenMousePos, camera->GetProjection(), camera->GetView(), Matrix::Identity);

		return mouseWorldPos3D;
	}

	Vector3 WindowScreenMouseToWorld3D(const Camera* const camera)
	{		
		const Vector2& WINDOW_MOUSE_2D_POS	= gInput->GetWindowMousePos();		
		const Vector3& WINDOW_MOUSE_3D_POS	= Vector3(WINDOW_MOUSE_2D_POS.x, WINDOW_MOUSE_2D_POS.y, 0.0f);
		const Vector2& WINDOW_SCREEN_SIZE	= gEngine->GetWindowScreenSize();
		
		return ScreenMouseToWorld3D(WINDOW_MOUSE_3D_POS, WINDOW_SCREEN_SIZE, camera);
	}

	float LerpCosBtwZeroAndOne(const float x)
	{
		return (cos(x) + 1.f) / 2.f;
	}

	float LerpSinBtwZeroAndOne(const float x)
	{
		return (sin(x) + 1.f) / 2.f;
	}
}

#pragma region dummy
//
//Vector2 ScreenToWorldScreen(const Vector2& RENDER_TARGET_MOUSE_POS,
//	const Vector2& RENDER_TARGET_SIZE);
//
////2D Camera
//Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
//	const Vector2& RENDER_TARGET_SIZE,
//	const Vector3& CAMERA_POS,
//	const float CAMERA_SIZE);
//
//Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
//	const Vector2& RENDER_TARGET_SIZE,
//	const Camera* const P_CAMERA);
//
//Vector2 WindowScreenMouseToWorld2D(const Camera* const P_CAMERA);


//Vector2 ScreenToWorldScreen(const Vector2& RENDER_TARGET_MOUSE_POS,
//	const Vector2& RENDER_TARGET_SIZE)
//{
//	Assert(false, WCHAR_IS_INVALID_TYPE);
//
//	return Vector2(RENDER_TARGET_MOUSE_POS.x - RENDER_TARGET_SIZE.x / 2,
//		-RENDER_TARGET_MOUSE_POS.y + RENDER_TARGET_SIZE.y / 2);
//}
//
//Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_POS,
//	const Vector2& RENDER_TARGET_SIZE,
//	const Vector3& CAMERA_POS,
//	const float CAMERA_SIZE)
//{
//	Assert(false, WCHAR_IS_INVALID_TYPE);
//
//	const Vector2 CAMERA_2D_POS = Vector2(CAMERA_POS.x, CAMERA_POS.y);
//
//	return ScreenToWorldScreen(RENDER_TARGET_POS * CAMERA_SIZE, RENDER_TARGET_SIZE * CAMERA_SIZE) + CAMERA_2D_POS;
//}
//
//Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
//	const Vector2& RENDER_TARGET_SIZE,
//	const Camera* const P_CAMERA)
//{
//	Assert(false, WCHAR_IS_INVALID_TYPE);
//
//	const Vector2 MOUSE_WORLD_2D_POS = ScreenToWorld2D(RENDER_TARGET_MOUSE_POS,
//		RENDER_TARGET_SIZE,
//		P_CAMERA->GetComponent<Transform>()->GetPosition(),
//		P_CAMERA->GetCameraSize());
//
//	return MOUSE_WORLD_2D_POS;
//}
//
//Vector2 WindowScreenMouseToWorld2D(const Camera* const P_CAMERA)
//{
//	Assert(false, WCHAR_IS_INVALID_TYPE);
//
//	const Vector2& WINDOW_SCREEN_SIZE = gEngine->GetWindowScreenSize();
//	const Vector2& RENDER_TARGET_SIZE = gEngine->GetRenderTargetSize();
//	const Vector2& WINDOW_MOUSE_POS = gInput->GetWindowMousePos();
//	const Vector2 RENDER_TARGET_MOUSE_POS = WINDOW_MOUSE_POS * (RENDER_TARGET_SIZE / WINDOW_SCREEN_SIZE);
//
//	const Vector2 MOUSE_WORLD_2D_POS = ScreenToWorld2D(RENDER_TARGET_MOUSE_POS,
//		RENDER_TARGET_SIZE,
//		P_CAMERA);
//
//	return MOUSE_WORLD_2D_POS;
//}
#pragma endregion