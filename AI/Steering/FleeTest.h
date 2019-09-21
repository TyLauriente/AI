#pragma once


#include <XEngine.h>
#include<AI.h>
#include "FleeBot.h"


class FleeTest
{
public:
	FleeTest();
	~FleeTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

	void SetTarget(X::Math::Vector2 target);

protected:
	FleeBot* m_fleeBot;
	AI::AIWorld m_seekWorld;
};

