#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"FleeBehaviour.h"


class FleeBot : public BaseBot
{
public:
	FleeBot(AI::AIWorld& world);
	~FleeBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(X::Math::Vector2 target);

	void SetRotation();

private:
	const float MAX_SPEED = 700.0f;
	const float MASS = 30.0f;
	const float RANGE = 200.0f;
};
