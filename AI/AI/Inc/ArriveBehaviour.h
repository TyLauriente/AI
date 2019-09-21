#pragma once

#include<XEngine.h>
#include<AI.h>
#include"AIWorld.h"

namespace AI
{

class ArriveBehaviour : public AI::SteeringBehaviour
{
public:
	ArriveBehaviour();

	virtual ~ArriveBehaviour();

	X::Math::Vector2 Calculate(Agent& agent) override;
	const char* GetName() const;

	float& SlowingRadius() { return m_slowingRadius; }

private:
	float m_slowingRadius;
};

} // NAMESPACE AI