#pragma once


#include <XEngine.h>
#include<AI.h>
#include "ArriveBot.h"


class ArriveTest
{
public:
	ArriveTest();
	~ArriveTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

	void SetTarget(X::Math::Vector2 target);

protected:
	ArriveBot* m_arriveBot;
	AI::AIWorld m_seekWorld;
};

