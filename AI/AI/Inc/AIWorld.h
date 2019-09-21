#ifndef INCLUDED_AI_AIWORLD_H
#define INCLUDED_AI_AIWORLD_H

#include "Agent.h"
#include "Entity.h"
#include "Graph.h"

namespace AI {

class AIWorld
{
public:
	typedef std::vector<X::Math::Circle> Obstacles;
	typedef std::vector<X::Math::LineSegment> Walls;

	AIWorld();
	~AIWorld();

	void RegisterAgent(Agent* agent);
	void UnregisterAgent(Agent* agent);

	void RegisterEntity(Entity* entity);
	void UnregisterEntity(Entity* entity);

	AgentList GetNeighborAgents(const X::Math::Circle& range);

	bool HasLOS(const X::Math::LineSegment& line);

	void AddObstacles(const X::Math::Circle& obstacle);
	const Obstacles& GetObstacles() const { return m_obstacles; }

	void RemoveObstacle(const X::Math::Circle& obstacle);
	void RemoveWall(const X::Math::LineSegment& wall);

	void AddWall(const X::Math::LineSegment& wall);
	const Walls& GetWalls() const { return m_walls; }

	Graph& GetNavGraph()				{ return m_navGraph; }
	const Graph& GetNavGraph() const	{ return m_navGraph; }

	AgentList& GetAgents()			{ return m_agents; }

	EntityList& GetEntities() { return m_entities; }


private:
	AgentList m_agents;
	EntityList m_entities;
	Obstacles m_obstacles;
	Walls m_walls;
	Graph m_navGraph;
	bool m_initialized;
};

} // namespace AI

#endif // #include INCLUDED_AI_AIWORLD_H