#include "pch.h"
#include "EngineMath.h"

/*
* ���� ���� ����ϴ� UI ��ǥ��� ������ ��ǥ��� �����ϰ� ����մϴ�.
* ������ ��ǥ��� ���� ����� (0, 0)�̰� ������ �ϴ��� (width, height)�Դϴ�.
*/

namespace helper
{
	Vector2 WindowScreenToUIPostion(const Vector2& screenPos, const Vector2& screenSize)
	{
		return Vector2(screenPos.x - screenSize.x / 2, -screenPos.y + screenSize.y / 2);
	}
}
