#pragma once

#include<XEngine.h>
#include "BaseBot.h"
#include"SeekBehaviour.h"


class SeekBot : public BaseBot
{
public:
	SeekBot(AI::AIWorld& world);
	~SeekBot();

	void XInitialize() override;

	void Update(float deltaTime) override;

	void SetTarget(X::Math::Vector2 target);

	void SetRotation();

private:
	const float MAX_SPEED = 700.0f;
	const float MASS = 30.0f;

};
