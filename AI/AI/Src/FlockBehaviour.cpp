#include "Precompiled.h"
#include "FlockBehaviour.h"

AI::FlockBehaviour::FlockBehaviour()
{

}

AI::FlockBehaviour::~FlockBehaviour()
{

}

X::Math::Vector2 AI::FlockBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 steering{ 0.0f, 0.0f };
	X::Math::Vector2 allignment{ 0.0f, 0.0f };
	X::Math::Vector2 cohesion{ 0.0f, 0.0f };
	X::Math::Vector2 seperation{ 0.0f, 0.0f };

	const auto& neighborList = agent.World().GetNeighborAgents({ agent.Position(), m_neighborRadius });
	int neighborCount = neighborList.size();
	for (const auto& otherAgent : neighborList)
	{
		//Alignment
		allignment += otherAgent->Velocity();
		//Cohesion
		cohesion += otherAgent->Position();
		//Seperation
		seperation += (otherAgent->Position() - agent.Position()) * -1;
	}
	if (neighborCount > 0)
	{
		if (allignment.x != 0 || allignment.y != 0)
		{
			allignment = X::Math::Normalize(allignment / neighborCount);
		}
		if (cohesion.x != 0 || cohesion.y != 0)
		{
			cohesion = X::Math::Normalize((cohesion / neighborCount) - agent.Position());
		}
		if (seperation.x != 0 || seperation.y != 0)
		{
			seperation = X::Math::Normalize(seperation / neighborCount);
		}

		if (&agent == agent.World().GetAgents().front())
		{
			X::DrawScreenLine(agent.Position(), agent.Position() + allignment * 60.0f, X::Math::Vector4::Green());
			X::DrawScreenLine(agent.Position(), agent.Position() + cohesion * 60.0f, X::Math::Vector4::LightBlue());
			X::DrawScreenLine(agent.Position(), agent.Position() + seperation * 60.0f, X::Math::Vector4::Red());
			X::DrawScreenLine(agent.Position(), agent.Position() + X::Math::Normalize(agent.Velocity()) * 60.0f, X::Math::Vector4::White());
			X::DrawScreenCircle({ agent.Position(), m_neighborRadius }, X::Math::Vector4::White());
		}
	}
	else
	{
		return { 0, 0 };
	}

	steering = (allignment * m_allignmentWeight)+ (cohesion * m_cohesionWeight) + (seperation * m_seperationWeight);
	steering = (steering / agent.Mass()) * agent.MaxSpeed();
	return steering;
}

const char* AI::FlockBehaviour::GetName() const
{
	return NAME;
}