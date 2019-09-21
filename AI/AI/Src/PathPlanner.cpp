#include"Precompiled.h"
#include"PathPlanner.h"
#include"Agent.h"
#include<XEngine.h>

using namespace AI;

PathPlanner::PathPlanner(Agent& agent)
	: m_agent{ agent }
{

}

PathPlanner::~PathPlanner()
{

}

void PathPlanner::Init(uint32_t rows, uint32_t collumns, float unitSize)
{
	m_rows = rows;
	m_collumns = collumns;
	m_unitSize = unitSize;
}

void PathPlanner::SetCostFunction(std::function<void(Graph::Coordinate, Graph::Coordinate)> setCostFunc)
{
	m_setCostFunction = setCostFunc;
}

bool PathPlanner::RequestPath(const X::Math::Vector2& destination)
{
	m_path.clear();
	if (m_agent.World().HasLOS({ m_agent.Position(), destination }))
	{
		m_path.push_back(destination);
		return true;
	}
	else
	{
		if (m_agent.World().GetNavGraph().GetNode(ConvertToCoordinate(destination)).blocked)
		{
			return false;
		}
		m_agent.World().GetNavGraph().FindPath(ConvertToCoordinate(m_agent.Position()),
			ConvertToCoordinate(destination), m_setCostFunction);
		std::vector<Graph::Coordinate> path = m_agent.World().GetNavGraph().GetPath();
		for (const auto& node : path)
		{
			m_path.push_back(ConvertToPosition(node));
		}
		/*TODO
		Run Path Smoothing
		..
		...
		....
		*/
	}
	return true;
}

bool PathPlanner::RequestPath(uint32_t entityId)
{
	std::vector<Entity*> entities = m_agent.World().GetEntities();
	for (const auto& entity : entities)
	{
		if (entity->GetId() == entityId)
		{
			return RequestPath(entity->GetPosition());
		}
	}
	return false;
}

Graph::Coordinate PathPlanner::ConvertToCoordinate(X::Math::Vector2 pos)
{
	float unitSize = m_agent.World().GetNavGraph().UnitSize();
	return { static_cast<uint32_t>((pos.x > 0) ? pos.x / unitSize : 0), 
		static_cast<uint32_t>((pos.y > 0) ? pos.y / unitSize : 0) };
}

X::Math::Vector2 PathPlanner::ConvertToPosition(Graph::Coordinate coord)
{
	float unitSize = m_agent.World().GetNavGraph().UnitSize();
	return { static_cast<float>(coord.x * unitSize),
		static_cast<float>(coord.y * unitSize) };
}