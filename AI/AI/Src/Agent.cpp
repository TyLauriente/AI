#include "Precompiled.h"
#include "Agent.h"

#include "AIWorld.h"

using namespace AI;

Agent::Agent(AIWorld& world)
	: m_World(world)
	, m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Destination(0.0f, 0.0f)
	, m_Heading(0.0f, 1.0f)
	, m_mass(1.0f)
	, mMaxSpeed(0.0f)
{
	m_World.RegisterAgent(this);
}

Agent::~Agent()
{
	m_World.UnregisterAgent(this);
}

X::Math::Matrix3 Agent::LocalToWorld() const
{
	return X::Math::Matrix3(
		-m_Heading.y, m_Heading.x, 0.0f,
		m_Heading.x, m_Heading.y, 0.0f,
		m_Position.x, m_Position.y, 1.0f
	);
}