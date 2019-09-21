#pragma once


#include <XEngine.h>
#include<AI.h>
#include "SeekBot.h"


class SeekTest
{
public:
	SeekTest();
	~SeekTest();

	void XInitialize();

	void Update(float deltaTime);

	void Render();

	void SetTarget(X::Math::Vector2 target);

protected:
	SeekBot* m_seekBot;
	AI::AIWorld m_seekWorld;
};

