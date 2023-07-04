#include "pch.h"
#include "Transform.h"
#include "EngineMath.h"

Transform::Transform()
	: Component(eComponentType::Transform)
	, mPosition(Vector3::Zero)
	, mRotation(Vector3::Zero)
	, mScale(Vector3::One)
	, mForward(Vector3::Forward)
	, mRight(Vector3::Right)
	, mUp(Vector3::Up)
{
}

Transform::~Transform()
{
}

void Transform::initialize()
{
}

void Transform::update()
{
}

void Transform::lateUpdate()
{
	mWorld = Matrix::Identity;

	const Matrix scale = Matrix::CreateScale(mScale);

	Matrix rotation = {};
	rotation  = Matrix::CreateRotationX(Deg2Rad(mRotation.x));
	rotation *= Matrix::CreateRotationY(Deg2Rad(mRotation.y));
	rotation *= Matrix::CreateRotationZ(Deg2Rad(mRotation.z));

	Matrix position = {};
	position.Translation(mPosition);

	mWorld *= scale;
	mWorld *= rotation;
	mWorld *= position;

	GameObject* const parent = GetOwner()->GetParentOrNull();

	if (GetOwner()->GetParentOrNull())
	{
		//�θ�������� ����.
		//�θ� �̹� ����� �Ǿ��־���Ѵ�.
		mWorld *= parent->GetComponent<Transform>()->mWorld;
	}

	//FIXME
	mUp = XMVector3TransformNormal(Vector3::Up, mWorld);
	mForward = XMVector3TransformNormal(Vector3::Forward, mWorld);
	mRight = XMVector3TransformNormal(Vector3::Right, mWorld);
}

