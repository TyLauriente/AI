#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"FlockBehaviour.h"
#include"WanderBehaviour.h"
#include"SeekBehaviour.h"
#include"AvoidBehaviour.h"


class FlockBot : public BaseBot
{
public:
	FlockBot(AI::AIWorld& world);
	~FlockBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(X::Math::Vector2 target);

	void SetRotation();

	std::vector<X::Math::Circle> GetObstacles() { return m_agent.World().GetObstacles(); }

private:
	const float MAX_SPEED = 100.0f;
	const float MASS = 15.0f;
	const float NEIGHBOR_RADIUS = 100.0f;
	const float CIRCLE_DISTANCE = 500.0f;
	const float DIRECTION_CHANGE = 300.0f;
	const float SIGHT_RANGE = 100.0f;
	std::list<X::Math::Vector2> m_previousVelocities;
	int m_velocities = 0;
};
