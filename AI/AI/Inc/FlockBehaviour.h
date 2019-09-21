#pragma once

#include"SteeringBehaviour.h"
#include "AIWorld.h"

namespace AI
{

class FlockBehaviour: public SteeringBehaviour
{
public:

	FlockBehaviour();

	~FlockBehaviour();

	X::Math::Vector2 Calculate(Agent& agent) override;

	const char* GetName() const override;

	float& NeighborRadius() { return m_neighborRadius; }

	float& AllignmentWeight() { return m_allignmentWeight; }
	float& CohesionWeight() { return m_cohesionWeight; }
	float& SeperationWeight() { return m_seperationWeight; }
	
	float TotalWeight() { return m_allignmentWeight * m_cohesionWeight * m_seperationWeight; }


private:
	const char* NAME = "Flock";
	float m_neighborRadius = 0.0f;
	float m_allignmentWeight = 1.0f;
	float m_cohesionWeight = 1.0f;
	float m_seperationWeight = 1.0f;
};

} // NAMESPACE AI
