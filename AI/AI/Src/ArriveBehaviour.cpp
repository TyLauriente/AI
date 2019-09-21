#include"Precompiled.h"
#include"ArriveBehaviour.h"

using namespace AI;

ArriveBehaviour::ArriveBehaviour()
	: SteeringBehaviour()
{

}

ArriveBehaviour::~ArriveBehaviour()
{

}

X::Math::Vector2 ArriveBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 desiredVelocity = (agent.Destination() - agent.Position());
	if (desiredVelocity != X::Math::Vector2{ 0.0f, 0.0f })
	{
		desiredVelocity = X::Math::Normalize(desiredVelocity) * agent.MaxSpeed();
	}
	float distance = X::Math::Magnitude(agent.Destination() - agent.Position());
	
	if (distance <= m_slowingRadius)
	{
		desiredVelocity = (desiredVelocity * ((distance / m_slowingRadius)));
		if (desiredVelocity.x > agent.MaxSpeed() || desiredVelocity.x < agent.MaxSpeed() * -1)
		{
			desiredVelocity.x = (desiredVelocity.x > 0) ? agent.MaxSpeed() : agent.MaxSpeed() * -1;
		}
		if (desiredVelocity.y > agent.MaxSpeed() || desiredVelocity.y < agent.MaxSpeed() * -1)
		{
			desiredVelocity.y = (desiredVelocity.y > 0) ? agent.MaxSpeed() : agent.MaxSpeed() * -1;
		}
		desiredVelocity -= agent.Velocity();
		return desiredVelocity;
	}
	else
	{
		desiredVelocity = (desiredVelocity - agent.Velocity()) / agent.Mass();
		return desiredVelocity;
	}

}

const char* ArriveBehaviour::GetName() const
{
	return "Arrive";
}