#include "Precompiled.h"
#include "AIWorld.h"

#include "Agent.h"
#include "Graph.h"

using namespace AI;

AIWorld::AIWorld()
{
	
}

AIWorld::~AIWorld()
{
}

void AIWorld::RegisterAgent(Agent* agent)
{
	m_agents.push_back(agent);
}

void AIWorld::UnregisterAgent(Agent* agent)
{
	auto iter = std::find(m_agents.begin(), m_agents.end(), agent);

	if (iter != m_agents.end())
	{
		m_agents.erase(iter);
	}
}

void AIWorld::RegisterEntity(Entity* entity)
{
	m_entities.push_back(entity);
}


void AIWorld::UnregisterEntity(Entity* entity)
{
	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);

	if (iter != m_entities.end())
	{
		m_entities.erase(iter);
	}
}

AgentList AIWorld::GetNeighborAgents(const X::Math::Circle& range)
{
	AgentList neighbors;
	for (auto& agent : m_agents)
	{
		if (!(agent->Position().x == range.center.x && agent->Position().y == range.center.y))
		{
			if (X::Math::MagnitudeSqr(range.center - agent->Position()) < range.radius * range.radius)
			{
				neighbors.push_back(agent);
			}
		}
	}
	return neighbors;
}

bool AIWorld::HasLOS(const X::Math::LineSegment& line)
{
	for (const auto& obstacle : m_obstacles)
	{
		if (X::Math::Intersect(line, obstacle))
		{
			return false;
		}
	}
	for (const auto& wall : m_walls)
	{
		if (X::Math::Intersect(line, wall))
		{
			return false;
		}
	}	
	return true;
}

void AIWorld::AddObstacles(const X::Math::Circle& obstacle)
{
	m_obstacles.push_back(obstacle);
}

void AIWorld::RemoveObstacle(const X::Math::Circle& obstacle)
{
	for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		if ((*it) == obstacle)
		{
			m_obstacles.erase(it);
			break;
		}
	}
}

void AIWorld::RemoveWall(const X::Math::LineSegment& wall)
{
	for (auto it = m_walls.begin(); it != m_walls.end(); ++it)
	{
		if ((*it) == wall)
		{
			m_walls.erase(it);
			break;
		}
	}
}

void AIWorld::AddWall(const X::Math::LineSegment& wall)
{
	m_walls.push_back(wall);
}