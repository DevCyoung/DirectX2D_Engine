#include "pch.h"
#include "Transform.h"
#include "EngineMath.h"
#include "GameObject.h"

Transform::Transform()
	: Component(eComponentType::Transform)
	, mPosition(Vector3::Zero)
	, mRotation(Vector3::Zero)
	, mScale(Vector3::One)
	, mForward(Vector3::Forward)
	, mRight(Vector3::Right)
	, mUp(Vector3::Up)
	, mWorld(Matrix::Identity)
{
}

Transform::~Transform()
{
}

Matrix Transform::CreateWorldMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
	Matrix world = Matrix::Identity;

	Matrix scaleMatrix = Matrix::CreateScale(scale);

	Matrix rotationMatrix = {};
	rotationMatrix = Matrix::CreateRotationX(Deg2Rad(rotation.x));
	rotationMatrix *= Matrix::CreateRotationY(Deg2Rad(rotation.y));
	rotationMatrix *= Matrix::CreateRotationZ(Deg2Rad(rotation.z));

	Matrix positionMatrix = {};
	positionMatrix.Translation(position);

	world *= scaleMatrix;
	world *= rotationMatrix;
	world *= positionMatrix;

	return world;
}

void Transform::initialize()
{
}

void Transform::update()
{
}

void Transform::lateUpdate()
{
	mWorld = Transform::CreateWorldMatrix(mPosition, mRotation, mScale);

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

