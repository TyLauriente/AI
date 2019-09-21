#pragma once

#include<XEngine.h>
#include<AI.h>
#include"AIWorld.h"

namespace AI
{

	class AvoidBehaviour : public AI::SteeringBehaviour
	{
	public:
		AvoidBehaviour();

		virtual ~AvoidBehaviour();

		X::Math::Vector2 Calculate(Agent& agent) override;
		const char* GetName() const;

		void SetSightRange(float range) { m_sightRange = range; }
		float GetSightRange() { return m_sightRange; }

		bool LineIntersectsCircle(Agent& agent, X::Math::Vector2 sight1, X::Math::Vector2 sight2, X::Math::Circle obstacle);

		X::Math::Circle FindNearestObstacle(Agent& agent, X::Math::Vector2 direction);

		float& AvoidWeight() { return m_avoidWeight; }

	private:
		float m_sightRange = 0.0f;
		float m_avoidWeight = 2.0f;
	};

} // NAMESPACE AI