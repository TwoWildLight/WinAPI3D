#pragma once

class Pulsar
{
protected:
	const float fFrequency;
	float fElapsed = 0.0f;

public:
	Pulsar(float frequency) : fFrequency(frequency) {}
	virtual ~Pulsar() = default;

	void Set() 
	{
		fElapsed = 0.0f;
	}

	bool Update(float fDeltaTime) 
	{ 
		return (fElapsed += fDeltaTime) >= fFrequency;
	}

	bool UpdateAndSet(float fDeltaTime)
	{
		if ((fElapsed += fDeltaTime) >= fFrequency)
		{
			fElapsed = 0.0f;
			return true;
		}
		return false;
	}
};