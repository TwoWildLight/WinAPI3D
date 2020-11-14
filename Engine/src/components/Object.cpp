#include "Object.h"
//#include "../physics/BoundingSphere.h"
//#include "../physics/BoundingBox.h"

Object::Object(Tag tag, float fMass, float fFriction)
	:
	tag(tag),
	fMass(fMass),
	fFriction(fFriction)
{
	//switch (type)
	//{
	//case Collider::Type::BOUNDING_SPHERE:
	//	pCollider = std::make_unique<BoundingSphere>();
	//	break;
	//case Collider::Type::BOUNDING_BOX:
	//	pCollider = std::make_unique<BoundingBox>();
	//	break;
	//}

	vDirection = { 0.0f, 0.0f, 1.0f };
	vUpside = { 0.0f, 1.0f, 0.0f };
	vScale = { 1.0f, 1.0f, 1.0f };
}

//void Object::LoadModel(Graphics& gfx, const std::string& filePath, float scale)
//{
//	pModel = std::make_unique<Model>(gfx, filePath, scale);
//}

void Object::SetPosition(const Vector3 & v)
{
	vPosition = v;
}

void Object::SetDirection(const Vector3& vLook, const Vector3& vUp)
{
	vDirection = Vector3::Normalize(vLook);
	vUpside = Vector3::Normalize(vUp);
	
	auto mRotation = Matrix::LookAt(
		{ 0.0f, 0.0f, 0.0f },
		vDirection,
		vUpside
	);

	vAngle = Matrix::ToEuler(mRotation);
}

void Object::SetAngle(const Vector3& vAng)
{
	vAngle = vAng;
	Matrix mRotation = Matrix::Rotation(vAngle);
	vDirection = Vector3{ 0.0f, 0.0f, 1.0f } *mRotation;
	vUpside = Vector3{ 0.0f, 1.0f, 0.0f } * mRotation;
}

void Object::AddForce(const Vector3& vForc)
{
	vForce += vForc;
}

void Object::SetForce(const Vector3& vForc)
{
	vForce = vForc;
}

void Object::AddTorque(const Vector3& vTorq)
{
	vTorque += vTorq;
}

void Object::SetScale(const Vector3& vFactor)
{
	vScale = vFactor;
}

Object::Tag Object::GetTag() const
{
	return tag;
}

//Model* Object::GetModel() const
//{
//	return pModel.get();
//}
//
//Collider* Object::GetCollider() const
//{
//	// TO DO : Return Updated Collider
//
//	return pCollider.get();
//}

float Object::GetMass() const
{
	return fMass;
}

float Object::GetFriction() const
{
	return fFriction;
}

Vector3 Object::GetPosition() const
{
	return vPosition;
}

Vector3 Object::GetDirection() const
{
	return vDirection;
}

Vector3 Object::GetUpside() const
{
	return vUpside;
}

Vector3 Object::GetRightSide() const
{
	return Vector3::Cross(vUpside, vDirection);
}

Vector3 Object::GetAngle() const
{
	return vAngle;
}

Vector3 Object::GetForce() const
{
	return vForce;
}

Vector3 Object::GetTorque() const
{
	return vTorque;
}

Vector3 Object::GetScale() const
{
	return vScale;
}

Matrix Object::GetTransform() const
{
	return
		Matrix::Scaling(vScale) * 
		Matrix::Rotation(vAngle) *
		Matrix::Translation(vPosition);
}

Matrix Object::GetRotation() const
{
	return Matrix::Rotation(vAngle);
}