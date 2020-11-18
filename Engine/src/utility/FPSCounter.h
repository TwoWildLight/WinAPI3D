#pragma once
#include <utility/Pulsar.h>
#include <vector>
#include <numeric>

class FPSCounter
{
private:
	std::vector<float> fpsTable;
	size_t currentIndex = 0u;

public:
	FPSCounter(size_t tableSize) : fpsTable(tableSize) {}
	virtual ~FPSCounter() = default;

public:
	void Update(float fDeltaTime)
	{
		fpsTable[currentIndex++] = fDeltaTime;
		if (currentIndex == fpsTable.size())
		{
			currentIndex = 0u;
		}
	}

	float GetAverageFPS() const
	{
		return 1.0f / (std::accumulate(fpsTable.begin(), fpsTable.end(), 0.0f) / fpsTable.size());
	}
};