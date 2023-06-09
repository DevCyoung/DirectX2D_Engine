#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(Transform);

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();
	Transform(const Transform&) = delete;
	Transform& operator=(const Transform&) = delete;

	void SetPosition(const Vector3& position) { mPosition = position; }
	void SetRotation(const Vector3& rotation) { mRotation = rotation; }
	void SetScale(const Vector3& scale) { mScale = scale; }

	void SetPosition(const float x, const float y, const float z) { mPosition = Vector3(x, y, z); }
	void SetRotation(const float x, const float y, const float z) { mRotation = Vector3(x, y, z); }
	void SetScale(const float x, const float y, const float z) { mScale = Vector3(x, y, z); }

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetRotation() const { return mRotation; }
	const Vector3& GetScale() const { return mScale; }

	const Vector3& GetForward() const { return mForward; }
	const Vector3& GetRight() const { return mRight; }
	const Vector3& GetUp() const { return mUp; }

	const Matrix& GetWorldMatrix() const { return mWorld; }

	static Matrix CreateWorldMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

private:
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;
	Vector3 mForward;
	Vector3 mRight;
	Vector3 mUp;
	Matrix mWorld;
};
