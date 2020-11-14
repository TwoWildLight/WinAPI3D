#pragma once
#include "../utility/Vector.h"
#include "../utility/Matrix.h"

class Object abstract
{
public:
	enum class Tag
	{
		ENVIRONMENT,
		ENTITY,
	};

private:
	Tag tag;

	//std::unique_ptr<Model> pModel;
	//std::unique_ptr<Collider> pCollider;

	float fMass;
	float fFriction;

	Vector3 vPosition;
	Vector3 vDirection;
	Vector3 vUpside;
	Vector3 vAngle;
	Vector3 vForce;
	Vector3 vTorque;
	Vector3 vScale;

public:
	Object(Tag tag, float fMass = 1.0f, float fFriction = 0.03f);
	virtual ~Object() = default;

public:
	/*void LoadModel(Graphics& gfx, const std::string& filePath, float scale = 1.0f);*/

	void SetPosition(const Vector3& v);
	void SetDirection(const Vector3& vLook, const Vector3& vUp);
	void SetAngle(const Vector3& vAng);
	void AddForce(const Vector3& vForc);
	void SetForce(const Vector3& vForc);
	void AddTorque(const Vector3& vTorq);
	void SetScale(const Vector3& vFactor);

	Tag GetTag() const;
	/*Model* GetModel() const;
	Collider* GetCollider() const;*/

	float GetMass() const;
	float GetFriction() const;

	Vector3 GetPosition() const;
	Vector3 GetDirection() const;
	Vector3 GetUpside() const;
	Vector3 GetRightSide() const;
	Vector3 GetAngle() const;
	Vector3 GetForce() const;
	Vector3 GetTorque() const;
	Vector3 GetScale() const;
	Matrix GetTransform() const;
	Matrix GetRotation() const;

	virtual void Update(float fDletaTime) {}
};