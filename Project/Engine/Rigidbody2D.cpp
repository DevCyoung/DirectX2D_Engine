#include "pch.h"
#include "Rigidbody2D.h"
#include "Transform.h"
#include "TimeManager.h"


Rigidbody2D::Rigidbody2D()
	: Component(eComponentType::Rigidbody2D)
	, mForce(0.f)
	, mFriction(0.f)
	, mFrictionScale(1.f)
	, mVelocityLimit(500.f)
	, mGravityLimit(1000.f)
	, mGravityAccel(100.f)
	, mbGravityUse(false)
	, mbGround(false)
	, mMass(1.f)
{
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::initialize()
{
}

void Rigidbody2D::update()
{
}

void Rigidbody2D::fixedUpdate()
{
	// F = M x A
	// ���ӵ� ���ϱ�
	Vector2 vAccel = mForce / mMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ŵ
	mVelocity += vAccel * gDeltaTime;

	// �߷��� ����ϴ� ����, ���� �־�� ������ ����
	// �߷��� ���� ������ ������ �ٷ� ����
	if ((mbGravityUse && mbGround) || mbGravityUse == false)
	{
		// ���� ���ӵ�
		Vector2 vFriction = -mVelocity;
		if (vFriction != Vector2::Zero)
		{
			vFriction.Normalize();
			vFriction *= (mFriction * mFrictionScale * mMass * gDeltaTime);
		}

		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (mVelocity.Length() <= vFriction.Length())
		{
			mVelocity = Vector2::Zero;
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			mVelocity += vFriction;
		}
	}

	// �߷� ���� + ���� ���� ==> �߷�
	if (mbGravityUse && mbGround == false)
	{
		Vector2 vGravityAccel = Vector2(0.f, mGravityAccel);
		mVelocity -= vGravityAccel * gDeltaTime;
	}


	// �ӵ� ���� ����(��, ��)
	// �߷��� ����ϴ� ���, �¿� �̵��� �߷¹���(�Ʒ�) �� �ӵ������� ���� �����Ѵ�.
	if (mbGravityUse)
	{
		if (mVelocityLimit < fabsf(mVelocity.x))
		{
			mVelocity.x = (mVelocity.x / fabsf(mVelocity.x)) * mVelocityLimit;
		}

		if (mGravityLimit < fabsf(mVelocity.y))
		{
			mVelocity.y = (mVelocity.y / fabsf(mVelocity.y)) * mGravityLimit;
		}
	}

	// �߷��� ������� ������, ��� �������ε� �ӵ� ������ �Ǵ�.
	else
	{
		if (mVelocityLimit < mVelocity.Length())
		{
			// ���� �ӵ��� �Ѱ��� ���
			mVelocity.Normalize();
			mVelocity *= mVelocityLimit;
		}
	}

	// ������Ʈ�� ��ġ
	Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ŵ
	Pos.x += mVelocity.x * gDeltaTime;
	Pos.y += mVelocity.y * gDeltaTime;

	GetOwner()->GetComponent<Transform>()->SetPosition(Pos);

	mForce = Vector2::Zero;
}

void Rigidbody2D::lateUpdate()
{

}
