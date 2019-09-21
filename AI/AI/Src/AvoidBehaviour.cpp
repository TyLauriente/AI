#include"Precompiled.h"
#include"AvoidBehaviour.h"

using namespace AI;

AvoidBehaviour::AvoidBehaviour()
	: SteeringBehaviour()
{

}

AvoidBehaviour::~AvoidBehaviour()
{

}

X::Math::Vector2 AvoidBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 normVel = X::Math::Normalize(agent.Velocity());
	X::Math::Vector2 sight1 = agent.Position() + (normVel * m_sightRange);
	X::Math::Vector2 sight2 = agent.Position() + (normVel * (m_sightRange * 0.5));
	X::Math::Vector2 desiredVelocity{ 0,0 };

	auto nearestCircle = FindNearestObstacle(agent, normVel);
	

	if (LineIntersectsCircle(agent, sight1, sight2, nearestCircle))
	{
		desiredVelocity = sight1 - nearestCircle.center;
		desiredVelocity = X::Math::Normalize(desiredVelocity);
		desiredVelocity *= agent.MaxSpeed();
		desiredVelocity = (desiredVelocity / agent.Mass()) * m_avoidWeight;
		return desiredVelocity;
	}
	
	return { 0, 0 };
	
}

const char* AvoidBehaviour::GetName() const
{
	return "Avoid";
}


bool AvoidBehaviour::LineIntersectsCircle(Agent& agent, X::Math::Vector2 sight1, X::Math::Vector2 sight2, X::Math::Circle obstacle)
{
	return X::Math::Magnitude(obstacle.center - sight1) <= obstacle.radius + agent.CollisionRadius() * 0.5f||
		X::Math::Magnitude(obstacle.center - sight2) <= obstacle.radius + agent.CollisionRadius() * 0.5f;
}

X::Math::Circle AvoidBehaviour::FindNearestObstacle(Agent& agent, X::Math::Vector2 direction)
{
	X::Math::Circle nearestCircle = agent.World().GetObstacles().front();
	float nearestDistance = X::Math::MagnitudeSqr(nearestCircle.center - agent.Position());
	for (auto obstacle : agent.World().GetObstacles())
	{
		float distance = X::Math::MagnitudeSqr(obstacle.center - agent.Position());
		if (distance < nearestDistance)
		{
			auto heading = obstacle.center - agent.Position();
			auto dot = X::Math::Dot(heading, direction);
			if (dot > 0)
			{
				nearestCircle = obstacle;
				nearestDistance = distance;
			}
		}
	}
	return nearestCircle;
}