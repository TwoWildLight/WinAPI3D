#include "Keyboard.h"

Keyboard::State Keyboard::stateTable[Keyboard::nKey] = {};
Keyboard::State Keyboard::prevStateTable[Keyboard::nKey] = {};
bool Keyboard::bAutoRepeat = false;

void Keyboard::Clear()
{
	for (int iKey = 0; iKey < nKey; iKey++)
	{
		stateTable[iKey] = State::FREE;
	}
}

void Keyboard::Update()
{
	for (int iKey = 0; iKey < nKey; iKey++)
	{
		if (stateTable[iKey] == State::DOWN && prevStateTable[iKey] == State::DOWN)
			stateTable[iKey] = State::HOLD;

		if (stateTable[iKey] == State::RELEASE && prevStateTable[iKey] == State::RELEASE)
			stateTable[iKey] = State::FREE;

		prevStateTable[iKey] = stateTable[iKey];
	}
}