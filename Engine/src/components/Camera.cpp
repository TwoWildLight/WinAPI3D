#include "Camera.h"
#include "../core/Graphics.h"
#include "../core/Keyboard.h"
#include "../core/Mouse.h"

Camera::Camera(const Graphics& gfx, const Vector3& vPos, const Vector3& vDir, const Vector3& vUp)
	:
	gfx(gfx),
	Object(Object::Tag::ENTITY)
{
	SetPosition(vPos);
	SetDirection(vDir, vUp);

	fFieldOfView = PI_F / 2.0f;
	fSensitivity = 1.0f;
	fSpeed = 1.0f;
	type = Type::STATIC_VIEW;
	controlMode = ControlMode::MOUSE_MOVE;
}

void Camera::SetControlMode(ControlMode cm)
{
	controlMode = cm;
}

void Camera::SetFOV(float fovX)
{
	fFieldOfView = fovX;
}

void Camera::SetSensitivity(float sense)
{
	fSensitivity = sense;
}

void Camera::SetSpeed(float factor)
{
	fSpeed = factor;
}

void Camera::SetType(Type t)
{
	type = t;
}

float Camera::GetFOV() const
{
	return fFieldOfView;
}

float Camera::GetSensitivity() const
{
	return fSensitivity;
}

Camera::ControlMode Camera::GetControlMode() const
{
	return controlMode;
}

float Saturate(float val, float min, float max)
{
	if (val > max) return max;
	if (val < min) return min;
	return val;
}

void Camera::Update(float deltaTime)
{
	if (GetActiveWindow() == nullptr) return;
	Vector3 ang = GetAngle();
	float pitch = ang.x;
	float yaw = ang.y;

	switch (controlMode)
	{
	case ControlMode::KEYBOARD_ARROW:
		if (Keyboard::KeyIsHold(VK_UP))	{
			pitch = Saturate(-deltaTime + ang.x, -PI_F / 2.0f, PI_F / 2.0f);
		}
		if (Keyboard::KeyIsHold(VK_DOWN))	{
			pitch = Saturate(deltaTime + ang.x, -PI_F / 2.0f, PI_F / 2.0f);
		}
		if (Keyboard::KeyIsHold(VK_LEFT))	{
			yaw = ang.y - deltaTime;
		}
		if (Keyboard::KeyIsHold(VK_RIGHT)) {
			yaw = ang.y + deltaTime;
		}
		break;
	case ControlMode::MOUSE_MOVE:
		pitch = yaw = 0.0f;
		while (auto delta = Mouse::GetRawDelta())
		{
			pitch += delta->y;
			yaw += delta->x;
		}
		float unit = fFieldOfView / (float)gfx.GetWidth() / 2.0f;
		pitch *= unit;
		yaw *= unit;

		pitch = Saturate(pitch + ang.x, -PI_F / 2.0f, PI_F / 2.0f);
		yaw += ang.y;
		break;
	}
	
	SetAngle({ pitch, yaw, 0.0f });
	
	if (type == Type::FREE_VIEW)
	{
		if (Keyboard::KeyIsHold('W')) SetPosition(GetPosition() + GetDirection() * deltaTime * fSpeed);
		if (Keyboard::KeyIsHold('A')) SetPosition(GetPosition() - GetRightSide() * deltaTime * fSpeed);
		if (Keyboard::KeyIsHold('S')) SetPosition(GetPosition() - GetDirection() * deltaTime * fSpeed);
		if (Keyboard::KeyIsHold('D')) SetPosition(GetPosition() + GetRightSide() * deltaTime * fSpeed);
		if (Keyboard::KeyIsHold(VK_SPACE)) SetPosition(GetPosition() + Vector3{ 0.0f, fSpeed* deltaTime, 0.0f });
		if (Keyboard::KeyIsHold(VK_CONTROL)) SetPosition(GetPosition() - Vector3{ 0.0f, fSpeed* deltaTime, 0.0f });
	}
}

Matrix Camera::GetViewMatrix()
{
	return Matrix::LookAt(
		GetPosition(),
		GetDirection(),
		GetUpside()
	);
}

Matrix Camera::GetProjectionMatrix()
{
	float aspectRatio = (float)gfx.GetWidth() / gfx.GetHeight();
	return Matrix::Projection(fFieldOfView, aspectRatio, 0.2f, 100.0f);
}