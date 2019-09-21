#include "Precompiled.h"
#include "WanderBehaviour.h"

AI::WanderBehaviour::WanderBehaviour()
	: m_circleRadius{ 0.0f }
	, m_angleChange{ 0.0f }
{

}

AI::WanderBehaviour ::~WanderBehaviour()
{

}

X::Math::Vector2 AI::WanderBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 circle = agent.Position() + X::Math::Normalize(agent.Velocity()) * m_circleDistance;
	agent.Destination() = circle + X::Math::Rotate({ m_circleRadius, 0 }, X::Random(0, 360));

	X::Math::Vector2 desiredVelocity = X::Math::Normalize(agent.Destination() - agent.Position()) * agent.MaxSpeed();
	desiredVelocity = (desiredVelocity - agent.Velocity()) / agent.Mass();
	return desiredVelocity;
}

const char* AI::WanderBehaviour::GetName() const
{
	return NAME;
}