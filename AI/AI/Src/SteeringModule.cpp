#include"Precompiled.h"
#include"SteeringModule.h"

using namespace AI;

SteeringModule::SteeringModule(Agent& agent)
	: m_agent{ agent }
{}

SteeringModule::~SteeringModule()
{
	
}

void SteeringModule::Purge()
{
	m_behaviours.clear();
}

X::Math::Vector2 SteeringModule::Calculate()
{
	X::Math::Vector2 total;

	for (auto& b : m_behaviours)
	{
		if (b->IsActive())
		{
			total += b->Calculate(m_agent);
		}
	}
	return total;
}
