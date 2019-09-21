#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"SteeringBehaviour.h"
#include"AvoidBehaviour.h"
#include"SeekBehaviour.h"
#include"WanderBehaviour.h"


class AvoidBot : public BaseBot
{
public:
	AvoidBot(AI::AIWorld& world);
	~AvoidBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(const X::Math::Vector2& target);

	void SetRotation();

	std::vector<X::Math::Circle> GetObstacles() { return m_agent.World().GetObstacles(); }


private:
	const float MAX_SPEED = 500.0f;
	const float MASS = 30.0f;
	const float CIRCLE_DISTANCE = 300.0f;
	const float SIGHT_RANGE = 100.0f;
	const float DIRECTION_CHANGE = 100.0f;
	const float TARGET_TIME = 0.5f;
	float m_targetTimer = 0.0f;
	std::list<X::Math::Vector2> m_previousVelocities;
	int m_velocities = 0;
};
