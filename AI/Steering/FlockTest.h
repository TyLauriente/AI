#pragma once


#include <XEngine.h>
#include<AI.h>
#include "FlockBot.h"

const int AMOUNT_OF_FLOCKBOTS = 100;

class FlockTest
{
public:
	FlockTest();
	~FlockTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

	void SetTarget(X::Math::Vector2 target);

protected:
	FlockBot* m_flockBot[AMOUNT_OF_FLOCKBOTS];
	AI::AIWorld m_world;
};

