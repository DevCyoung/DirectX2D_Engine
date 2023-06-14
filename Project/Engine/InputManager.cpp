#include "pch.h"
#include "InputManager.h"	
#include "Engine.h"

namespace engine
{

	using namespace engine::math;

	static int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON,
	};	

	InputManager::InputManager()
		: mKeyInfos()
		, mMousePos(Vector2::Zero)
	{
	}

	InputManager::~InputManager()
	{
	}



	void InputManager::initialize()
	{
		assert(!sInstance);
		sInstance = new InputManager();

		sInstance->mKeyInfos.reserve(static_cast<size_t>(eKeyCode::END));
		for (UINT i = 0; i < static_cast<UINT>(eKeyCode::END); ++i)
		{
			tKeyInfo keyInfo = {};

			keyInfo.key = static_cast<eKeyCode>(i);
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			sInstance->mKeyInfos.push_back(keyInfo);
		}
	}

	void InputManager::update()
	{
		if (GetFocus())
		{
			for (tKeyInfo& keyInfo : mKeyInfos)
			{
				const UINT index = static_cast<UINT>(keyInfo.key);

				if (GetAsyncKeyState(ASCII[index]) & 0x8000)
				{
					if (keyInfo.bPressed == false)
					{
						keyInfo.state = eKeyState::Down;
						keyInfo.bPressed = true;
					}
					else
					{
						keyInfo.state = eKeyState::Pressed;
					}
				}
				else
				{
					if (keyInfo.bPressed == true)
					{
						keyInfo.state = eKeyState::Up;
						keyInfo.bPressed = false;
					}
					else
					{
						keyInfo.state = eKeyState::None;
					}
				}
			}


			
			POINT mousePos = {};
			GetCursorPos(&mousePos);

			ScreenToClient(gEngine->GetHwnd(), &mousePos);

			mMousePos.x = static_cast<float>(mousePos.x);
			mMousePos.y = static_cast<float>(mousePos.y);
		}
		else
		{		
			for (tKeyInfo& keyInfo : mKeyInfos)
			{				
				if (eKeyState::Down == keyInfo.state || eKeyState::Pressed == keyInfo.state)
				{
					keyInfo.state = eKeyState::Up;
				}
				else if (eKeyState::Up == keyInfo.state)
				{
					keyInfo.state = eKeyState::None;
				}

				keyInfo.bPressed = false;

			}
		}
	}

}