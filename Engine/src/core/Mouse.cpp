#include "Mouse.h"
#include <shellapi.h>

Mouse::State Mouse::lButtonState = State::FREE;
Mouse::State Mouse::rButtonState = State::FREE;
Mouse::State Mouse::prevLBState = Mouse::State::FREE;
Mouse::State Mouse::prevRBState = Mouse::State::FREE;
int Mouse::pos_x;
int Mouse::pos_y;
std::queue<POINT> Mouse::rawDeltas;
float Mouse::wheel;
bool Mouse::bInWindow;

void Mouse::Clear()
{
	lButtonState = State::FREE;
	rButtonState = State::FREE;
	prevLBState = State::FREE;
	prevRBState = State::FREE;
	wheel = 0.0f;
}

void Mouse::Update()
{
	if (lButtonState == State::DOWN && prevLBState == State::DOWN)
		lButtonState = State::HOLD;

	if (lButtonState == State::RELEASE && prevLBState == State::RELEASE)
		lButtonState = State::FREE;

	if (rButtonState == State::DOWN && prevRBState == State::DOWN)
		rButtonState = State::HOLD;

	if (rButtonState == State::DOWN && prevRBState == State::DOWN)
		rButtonState = State::HOLD;

	prevLBState = lButtonState;
	prevRBState = rButtonState;
	wheel = 0.0f;
}

void Mouse::OnRawMove(int x, int y)
{
	rawDeltas.push({ x, y });
}

std::optional<POINT> Mouse::GetRawDelta()
{
	if (rawDeltas.empty())
	{
		return std::nullopt;
	}
	auto res = rawDeltas.front();
	rawDeltas.pop();
	return res;
}