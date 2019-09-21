#include"Precompiled.h"
#include"SteeringBehaviour.h"

X::Math::Vector2 AI::SteeringBehaviour::Calculate(Agent& agent)
{
	return { 0, 0 };
}


const char* AI::SteeringBehaviour::GetName() const
{
	return "Default";
}

X::Math::Vector2 AI::SteeringBehaviour::Truncate(X::Math::Vector2 vec, float amount) const
{
	if (vec.x > amount)
	{
		vec.x = amount;
	}
	if (vec.y > amount)
	{
		vec.y = amount;
	}
	return vec;
}