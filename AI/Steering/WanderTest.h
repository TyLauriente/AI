#pragma once


#include <XEngine.h>
#include<vector>
#include<AI.h>
#include "WanderBot.h"


class WanderTest
{
public:
	WanderTest();
	~WanderTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

protected:
	WanderBot* m_wanderBot;
	AI::AIWorld m_world;
};

