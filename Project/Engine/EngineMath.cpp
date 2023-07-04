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
	Vector2 ScreenToWorldScreen(const Vector2& RENDER_TARGET_MOUSE_POS,
		const Vector2& RENDER_TARGET_SIZE)
	{
		return Vector2(RENDER_TARGET_MOUSE_POS.x - RENDER_TARGET_SIZE.x / 2, 
			-RENDER_TARGET_MOUSE_POS.y + RENDER_TARGET_SIZE.y / 2);
	}

	Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_POS,
		const Vector2& RENDER_TARGET_SIZE,
		const Vector3& CAMERA_POS,
		const float CAMERA_SIZE)
	{
		const Vector2 CAMERA_2D_POS = Vector2(CAMERA_POS.x, CAMERA_POS.y);

		return ScreenToWorldScreen(RENDER_TARGET_POS * CAMERA_SIZE, RENDER_TARGET_SIZE * CAMERA_SIZE) + CAMERA_2D_POS;
	}

	Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
		const Vector2& RENDER_TARGET_SIZE,
		const Camera* const P_CAMERA)
	{
		const Vector2 MOUSE_WORLD_2D_POS = ScreenToWorld2D(RENDER_TARGET_MOUSE_POS,
			RENDER_TARGET_SIZE,
			P_CAMERA->GetComponent<Transform>()->GetPosition(),
			P_CAMERA->GetCameraSize());

		return MOUSE_WORLD_2D_POS;
	}

	Vector2 WindowScreenMouseToWorld2D(const Camera* const P_CAMERA)
	{		
		const Vector2& WINDOW_SCREEN_SIZE	= gEngine->GetWindowScreenSize();
		const Vector2& RENDER_TARGET_SIZE	= gEngine->GetRenderTargetSize();
		const Vector2& WINDOW_MOUSE_POS		= gInput->GetWindowMousePos();		
		const Vector2 RENDER_TARGET_MOUSE_POS	= WINDOW_MOUSE_POS * (RENDER_TARGET_SIZE / WINDOW_SCREEN_SIZE);

		const Vector2 MOUSE_WORLD_2D_POS = ScreenToWorld2D(RENDER_TARGET_MOUSE_POS,
			RENDER_TARGET_SIZE,
			P_CAMERA);

		return MOUSE_WORLD_2D_POS;
	}


	float LerpCosBtwZeroAndOne(const float VALUE)
	{
		return (cos(VALUE) + 1.f) / 2.f;
	}

	float LerpSinBtwZeroAndOne(const float VALUE)
	{
		return (sin(VALUE) + 1.f) / 2.f;
	}

}
