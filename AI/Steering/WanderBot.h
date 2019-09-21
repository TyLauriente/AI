#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"SteeringBehaviour.h"
#include"AvoidBehaviour.h"
#include"SeekBehaviour.h"
#include"WanderBehaviour.h"


class WanderBot : public BaseBot
{
public:
	WanderBot(AI::AIWorld& world);
	~WanderBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(const X::Math::Vector2& target);

	void SetRotation();

	std::vector<X::Math::Circle> GetObstacles() { return m_agent.World().GetObstacles(); }


private:
	const float MAX_SPEED = 500.0f;
	const float MASS = 10.0f;
	const float CIRCLE_DISTANCE = 400.0f;
	const float DIRECTION_CHANGE = 200.0f;
	std::list<X::Math::Vector2> m_previousVelocities;
	int m_velocities = 0;
};
