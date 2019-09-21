#pragma once

#include"Agent.h"
#include"Graph.h"
#include"AIWorld.h"


namespace AI
{

class PathPlanner
{
public:
	PathPlanner(Agent& agent);

	~PathPlanner();

	void Init(uint32_t rows, uint32_t collumns, float unitSize);

	void SetCostFunction(std::function<void(Graph::Coordinate, Graph::Coordinate)> setCostFunc);

	bool RequestPath(const X::Math::Vector2& destination);

	bool RequestPath(uint32_t entityType);

	const std::vector<X::Math::Vector2>& GetPath() const { return m_path; }

protected:
	Agent& m_agent;
	std::vector<X::Math::Vector2> m_path;
	std::function<void(Graph::Coordinate, Graph::Coordinate)> m_setCostFunction;

	Graph::Coordinate ConvertToCoordinate(X::Math::Vector2 pos);
	X::Math::Vector2 ConvertToPosition(Graph::Coordinate coord);

	uint32_t m_rows;
	uint32_t m_collumns;
	float m_unitSize;
};



} // NAMESPACE AI