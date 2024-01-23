#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/EngineMath.h>
#include <Engine/Engine.h>
//#include "GameObjectBuilder.h"
//#include "BulletMovement.h"
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include <Engine/GameSystem.h>

using namespace helper;
using namespace helper::math;

CursorMovement::CursorMovement()
	: ScriptComponent(eScriptComponentType::CursorMovement)
	, mDelay(0.f)
{
}



CursorMovement::~CursorMovement()
{
}

void CursorMovement::onCollisionEnter(Collider2D* other)
{
	(void)other;
}

void CursorMovement::initialize()
{
}

void CursorMovement::update()
{
	RenderTargetRenderer* const renderTargetRenderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	Transform* const transform = GetOwner()->GetComponent<Transform>();
	const Camera* const P_MAIN_CAMERA = renderTargetRenderer->GetRegisteredRenderCamera(eCameraPriorityType::UI);
	const Vector3& MOUSE_WORLD_3D_POS = WindowScreenMouseToWorld3D(P_MAIN_CAMERA);
	Vector3 mousePos = MOUSE_WORLD_3D_POS;
	mousePos.z = 0.f;

	transform->SetPosition(mousePos);
}

void CursorMovement::fixedUpdate()
{

}

void CursorMovement::lateUpdate()
{
}
