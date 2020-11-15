#pragma once

class Context
{
public:
	enum class Topology
	{
		NONE,
		LINE_LIST,
		TRIANGLE_LIST,
	};

private:
	Topology topology = Topology::NONE;

public:
	Topology GetTopology() const
	{
		return topology;
	}
	void SetTopology(Topology t)
	{
		topology = t;
	}
};