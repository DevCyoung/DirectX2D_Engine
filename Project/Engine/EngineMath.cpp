#include "pch.h"
#include "EngineMath.h"

/*
* ���� ���� ����ϴ� UI ��ǥ��� ������ ��ǥ��� �����ϰ� ����մϴ�.
* ������ ��ǥ��� ���� ����� (0, 0)�̰� ������ �ϴ��� (width, height)�Դϴ�.
*/

namespace helper
{
	Vector2 ScreenToWorldScreen(const Vector2& screenPos, 
		const Vector2& screenSize)
	{
		return Vector2(screenPos.x - screenSize.x / 2, -screenPos.y + screenSize.y / 2);
	}

	Vector2 ScreenToWorld2D(const Vector2& screenPos, 
		const Vector2& screenSize, 
		const Vector3& cameraPos,
		const float cameraSize)
	{
		Vector2 cameraPos2D = Vector2(cameraPos.x, cameraPos.y);

		return ScreenToWorldScreen(screenPos * cameraSize, screenSize * cameraSize) + cameraPos2D;
	}

	float LerpCosBtwZeroAndOne(float value)
	{		
		return (cos(value) + 1.f) / 2.f;
	}

	float LerpSinBtwZeroAndOne(float value)
	{
		return (sin(value) + 1.f) / 2.f;
	}
	
}
