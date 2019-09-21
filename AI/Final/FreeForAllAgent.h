#pragma once


#include<XEngine.h>
#include<AI.h>
#include"TileMap.h"

const float STOP_DISTANCE = 150.0f;
const float MAX_SPEED = 50.0f;
const float MASS = 1.0f;


class FreeForAllAgent
{
public:

	FreeForAllAgent(AI::AIWorld& world, X::Math::Vector2 home);

	~FreeForAllAgent();

	void XInitialize(TileMap& map);

	void Update(float deltaTime);

	void Render();

	AI::Agent& GetAgent() { return m_agent; }

	void Kill() { m_dead = true; }

	void SetCostFunction(std::function<void(AI::Graph::Coordinate, AI::Graph::Coordinate)> costFunction);


	std::vector<X::Math::Vector2> path;
	AI::PathPlanner pathPlanner;
	AI::SteeringModule* steering;
	int currentTarget;
	int hp;
	int ammo;
private:
	AI::AIWorld& m_world;
	AI::Agent m_agent;
	AI::StateMachine<FreeForAllAgent>* m_stateMachine;
	const X::Math::Vector2 m_home;
	X::TextureId m_textureId;
	bool m_dead;
};


/*
===========================================================================
===================================States==================================
===========================================================================
*/


class KillOpponents : public AI::State<FreeForAllAgent>
{
public:
	X::Math::Vector2 target;

	void Enter(FreeForAllAgent& agent) override
	{

	}

	void Update(FreeForAllAgent& agent, float deltaTime) override
	{
		if (agent.hp <= 0)
		{
			agent.Kill();
		}
		else
		{
			X::Math::Vector2 newTarget{ (agent.GetAgent().World().GetAgents()[0]->Position()) };
			if (newTarget == agent.GetAgent().Position())
			{
				newTarget = (agent.GetAgent().World().GetAgents()[1]->Position());
			}
			float bestDistance = X::Math::DistanceSqr(agent.GetAgent().Position(), newTarget);
			for (auto& a : agent.GetAgent().World().GetAgents())
			{
				float distance = X::Math::DistanceSqr(agent.GetAgent().Position(), a->Position());
				if (distance < bestDistance || bestDistance == 0.0f)
				{
					bestDistance = distance;
					newTarget = a->Position();
				}
			}
			
			if (target != newTarget)
			{
				target = newTarget;
				agent.path.clear();
				agent.pathPlanner.RequestPath(target);
				agent.path = agent.pathPlanner.GetPath();
				agent.currentTarget = 0;
				if (agent.path.size() != 0)
				{
					agent.GetAgent().Destination() = agent.path[0];
				}
				agent.steering->GetBehaviour<AI::SeekBehaviour>("Seek")->SetActive(true);
				agent.steering->GetBehaviour<AI::ArriveBehaviour>("Arrive")->SetActive(false);
			}
			if (agent.path.size() != 0)
			{
				if (agent.steering->GetBehaviour<AI::SeekBehaviour>("Seek")->IsActive())
				{
					if (agent.currentTarget == agent.path.size() - 1)
					{
						agent.steering->GetBehaviour<AI::SeekBehaviour>("Seek")->SetActive(false);
						agent.steering->GetBehaviour<AI::ArriveBehaviour>("Arrive")->SetActive(true);
					}
					else
					{
						if (X::Math::DistanceSqr(agent.GetAgent().Position(), agent.GetAgent().Destination()) <= STOP_DISTANCE * STOP_DISTANCE)
						{
							agent.currentTarget++;
							agent.GetAgent().Destination() = agent.path[agent.currentTarget];
						}
					}
				}
			}
			agent.GetAgent().Velocity() += agent.steering->Calculate();
			agent.GetAgent().Position() += agent.GetAgent().Velocity() * deltaTime;
		}
	}

	void Exit(FreeForAllAgent& agent) override
	{

	}
};




class CollectAmmo : public AI::State<FreeForAllAgent>
{
public:

	void Enter(FreeForAllAgent& agent) override
	{

	}

	void Update(FreeForAllAgent& agent, float deltaTime) override
	{

	}

	void Exit(FreeForAllAgent& agent) override
	{

	}
};