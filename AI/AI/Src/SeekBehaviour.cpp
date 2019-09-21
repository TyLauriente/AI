#include "Precompiled.h"
#include "SeekBehaviour.h"

AI::SeekBehaviour::SeekBehaviour()
{

}

AI::SeekBehaviour::~SeekBehaviour()
{

}

X::Math::Vector2 AI::SeekBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 desiredVelocity = (agent.Destination() - agent.Position());
	if (desiredVelocity != X::Math::Vector2{0.0f, 0.0f})
	{
		desiredVelocity = X::Math::Normalize(desiredVelocity) * agent.MaxSpeed();
		desiredVelocity = (desiredVelocity - agent.Velocity()) / agent.Mass();
	}
	return desiredVelocity;
}

const char* AI::SeekBehaviour::GetName() const
{
	return NAME;
}