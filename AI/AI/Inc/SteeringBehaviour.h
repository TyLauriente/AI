#pragma once

#include<XEngine.h>

namespace AI
{

class Agent;

class SteeringBehaviour
{
public:
	SteeringBehaviour() : m_active{ false } {}
	virtual ~SteeringBehaviour() {}

	virtual X::Math::Vector2 Calculate(Agent& agent) = 0;
	virtual const char* GetName() const = 0;

	X::Math::Vector2 Truncate(X::Math::Vector2 vec, float amount) const;

	void SetActive(bool active) { m_active = active; }
	bool IsActive() const		{ return m_active; }

protected:
	bool m_active;
};

} // Namspace AI