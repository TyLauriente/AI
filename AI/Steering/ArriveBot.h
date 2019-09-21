#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"ArriveBehaviour.h"


class ArriveBot : public BaseBot
{
public:
	ArriveBot(AI::AIWorld& world);
	~ArriveBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(X::Math::Vector2 target);

	void SetRotation();

private:
	const float MAX_SPEED = 600.0f;
	const float MASS = 15.0f;
	const float RANGE = 100.0f;
};
