#pragma once
#include "Object.h"

class Graphics;

class Camera : public Object
{
public:
	enum class Type
	{
		STATIC_VIEW,
		FREE_VIEW
	};
	enum class ControlMode
	{
		STATIC,
		KEYBOARD_ARROW,
		MOUSE_MOVE
	};
private:
	const Graphics& gfx;

	Type type;
	ControlMode controlMode;

	float fFieldOfView;
	float fSensitivity;
	float fSpeed;

public:
	Camera(const Graphics& gfx, const Vector3& vPos, const Vector3& vDir = { 0.0f, 0.0f, 1.0f }, const Vector3& vUp = { 0.0f, 1.0f, 0.0f });
	virtual ~Camera() = default;

public:
	void SetControlMode(ControlMode cm);
	void SetFOV(float fovX);
	void SetSensitivity(float sense);
	void SetSpeed(float factor);
	void SetType(Type t);

	float GetFOV() const;
	float GetSensitivity() const;
	ControlMode GetControlMode() const;

	virtual void Update(float deltaTime) override;

	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();
};