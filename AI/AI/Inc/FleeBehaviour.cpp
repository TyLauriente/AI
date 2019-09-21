#include "Precompiled.h"
#include "FleeBehaviour.h"


AI::FleeBehaviour::FleeBehaviour()
{

}

AI::FleeBehaviour::~FleeBehaviour()
{

}

X::Math::Vector2 AI::FleeBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 desiredVelocity = X::Math::Normalize(agent.Position() - agent.Destination()) * agent.MaxSpeed();
	desiredVelocity = ((desiredVelocity - agent.Velocity()) / agent.Mass());
	return desiredVelocity;
}

const char* AI::FleeBehaviour::GetName() const
{
	return NAME;
}