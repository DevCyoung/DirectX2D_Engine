#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderTargetRenderer.h"
#include "EngineMath.h"
#include "GameSystem.h"

Camera::Camera()
	: Component(eComponentType::Camera)	
	, mRenderTargetSize(Vector2::Zero)
	, mLayerMask(0XFFFFFFFF)
	, mNear(1.0f)
	, mFar(10000.0f)
	, mFOV(60.0f)
	, mSize(1.0f)
	, mAspectRatio(1.0f)
	, mView(Matrix::Identity)
	, mProjection(Matrix::Identity)
	, mProjectionType(eCameraProjectionType::Orthographic)
	, mCameraType(eCameraPriorityType::End)
{
}

Camera::~Camera()
{
}

void Camera::CalculateCamera()
{
	const Transform* const P_TRANSFORM = GetOwner()->GetComponent<Transform>();
	const Vector3& POSITION = P_TRANSFORM->GetWorldMatrix().Translation();

	// View Translate Matrix
	mView = Matrix::Identity;
	mView *= Matrix::CreateTranslation(-POSITION);

	// View Rotation Matrix
	const Vector3& UP = P_TRANSFORM->GetUp();
	const Vector3& RIGHT = P_TRANSFORM->GetRight();
	const Vector3& FORWARD = P_TRANSFORM->GetForward();

	Matrix viewRotate = {};

	viewRotate._11 = RIGHT.x;	viewRotate._12 = UP.x;	viewRotate._13 = FORWARD.x;
	viewRotate._21 = RIGHT.y;	viewRotate._22 = UP.y;	viewRotate._23 = FORWARD.y;
	viewRotate._31 = RIGHT.z;	viewRotate._32 = UP.z;	viewRotate._33 = FORWARD.z;

	mView *= viewRotate;

	mAspectRatio = mRenderTargetSize.x / mRenderTargetSize.y;

	switch (mProjectionType)
	{
	case eCameraProjectionType::Perspective:
		mProjection = Matrix::CreatePerspectiveFieldOfViewLH(Deg2Rad(mFOV), mAspectRatio, mNear, mFar);
		break;
	case eCameraProjectionType::Orthographic:
	{
		const float ORTHOGRAPHIC_RATIO = mSize / 1.0f;
		const float WIDTH = mRenderTargetSize.x * ORTHOGRAPHIC_RATIO;
		const float HEIGHT = mRenderTargetSize.y * ORTHOGRAPHIC_RATIO;

		mProjection = Matrix::CreateOrthographicLH(WIDTH, HEIGHT, mNear, mFar);
	}
	break;
	default:
		Assert(false, ASSERT_MSG_INVALID);
		break;
	}
}

void Camera::initialize()
{
	Assert(mRenderTargetSize != Vector2::Zero, ASSERT_MSG_NULL);

	GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->RegisterRenderCamera(this);
}

void Camera::update()
{
}

void Camera::lateUpdate()
{
	CalculateCamera();
}
