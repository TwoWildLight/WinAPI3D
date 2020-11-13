#pragma once
#include "LightWindows.h"

class Keyboard
{
	friend class Window;
public:
	enum class State
	{
		FREE,
		DOWN,
		HOLD,
		RELEASE
	};

private:
	static constexpr UINT nKey = 256;
	static State stateTable[nKey];
	static State prevStateTable[nKey];
	static bool bAutoRepeat;

private:
	static void Clear();
	static void Update();
	static void OnKeyPress(DWORD key) { stateTable[key] = State::DOWN; }
	static void OnKeyRelease(DWORD key) { stateTable[key] = State::FREE; }

public:
	static bool KeyIsFree(DWORD key) { return stateTable[key] == State::FREE; }
	static bool KeyIsDown(DWORD key) { return stateTable[key] == State::DOWN; }
	static bool KeyIsHold(DWORD key) { return stateTable[key] == State::HOLD; }
	static bool KeyIsRelease(DWORD key) { return stateTable[key] == State::RELEASE; }

	static void EnableAutoRepeat() { bAutoRepeat = true; }
	static void DisableAutoRepeat() { bAutoRepeat = false; };
};