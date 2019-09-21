#pragma once

#include<math.h>
#include"SteeringBehaviour.h"
#include "AIWorld.h"

namespace AI
{

class WanderBehaviour : public SteeringBehaviour
{
public:

	WanderBehaviour();

	~WanderBehaviour();

	X::Math::Vector2 Calculate(Agent& agent) override;

	const char* GetName() const override;

	float& CircleRadius() { return m_circleRadius; }

	float& CircleDistance() { return m_circleDistance; }

private:
	const char* NAME = "Wander";
	float m_circleRadius;
	float m_circleDistance;
	float m_angleChange;

};

} // NAMESPACE AI
