#pragma once


#include <XEngine.h>
#include<vector>
#include<AI.h>
#include "AvoidBot.h"


class AvoidTest
{
public:
	AvoidTest();
	~AvoidTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

	void SetTarget(X::Math::Vector2 target);

protected:
	AvoidBot * m_avoidBot;
	AI::AIWorld m_world;
};

