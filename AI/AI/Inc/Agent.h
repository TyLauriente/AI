#ifndef INCLUDED_AI_AGENT_H
#define INCLUDED_AI_AGENT_H

#include <XEngine.h>

namespace AI {

class Agent;
class AIWorld;

class Agent
{
public:
	Agent(AIWorld& world);
	virtual ~Agent();

	X::Math::Matrix3 LocalToWorld() const;

	AIWorld& World() const						{ return m_World; }
	
	X::Math::Vector2& Position()				{ return m_Position; }
	const X::Math::Vector2& Position() const	{ return m_Position; }
	
	X::Math::Vector2& Velocity()				{ return m_Velocity; }
	const X::Math::Vector2& Velocity() const	{ return m_Velocity; }

	X::Math::Vector2& Destination()				{ return m_Destination; }
	const X::Math::Vector2& Destination() const { return m_Destination; }

	X::Math::Vector2& Heading()					{ return m_Heading; }
	const X::Math::Vector2& Heading() const		{ return m_Heading; }

	float& MaxSpeed()							{ return mMaxSpeed; }
	float MaxSpeed() const						{ return mMaxSpeed; }

	float& Mass()								 { return m_mass; }

	float& CollisionRadius()					 { return m_collisionRadius; }

protected:
	AIWorld& m_World;
	X::Math::Vector2 m_Position;
	X::Math::Vector2 m_Velocity;
	X::Math::Vector2 m_Destination;
	X::Math::Vector2 m_Heading;
	float m_mass;
	float mMaxSpeed;
	float m_collisionRadius;
};

using AgentList = std::vector<Agent*>;

} // namespace AI

#endif // #include INCLUDED_AI_AGENT_H