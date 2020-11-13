#pragma once
#include "LightWindows.h"
#include <queue>
#include <optional>

class Mouse
{
	friend class Window;
private:
	enum class State
	{
		FREE,
		DOWN,
		HOLD,
		RELEASE
	};

private:
	static State lButtonState;
	static State rButtonState;
	static State prevLBState;
	static State prevRBState;

	static int pos_x;
	static int pos_y;

	static std::queue<POINT> rawDeltas;

	static float wheel;

	static bool bInWindow;

private:
	static void Clear();
	static void Update();
	static void OnLBPressed() { lButtonState = State::DOWN; }
	static void OnLBRelease() { lButtonState = State::RELEASE; }
	static void OnRBPressed() { rButtonState = State::DOWN; }
	static void OnRBRelease() { rButtonState = State::RELEASE; }
	static void OnMove(int x, int y) { pos_x = x; pos_y = y; }
	static void OnRawMove(int x, int y);
	static void OnWheelScroll(float distance) { wheel = distance; }

public:
	static bool LBIsFree() { return lButtonState == State::FREE; }
	static bool LBIsDown() { return lButtonState == State::DOWN; }
	static bool LBIsHold() { return lButtonState == State::HOLD; }
	static bool LBIsRelease() { return lButtonState == State::RELEASE; }
	static bool RBIsFree() { return rButtonState == State::FREE; }
	static bool RBIsDown() { return rButtonState == State::DOWN; }
	static bool RBIsHold() { return rButtonState == State::HOLD; }
	static bool RBIsRelease() { return rButtonState == State::RELEASE; }

	static int GetPosX() { return pos_x; }
	static int GetPosY() { return pos_y; }
	static std::optional<POINT> GetRawDelta();

	static void SetPosX(int x_in) { pos_x = x_in; }
	static void SetPosY(int y_in) { pos_y = y_in; }

	static bool WheelIsUp() { return wheel > 0.0f; }
	static bool WheelIsDown() { return wheel < 0.0f; }
};