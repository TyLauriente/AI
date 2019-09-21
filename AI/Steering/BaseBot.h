#pragma once

#include<XEngine.h>
#include<AI.h>
#include "AIWorld.h"


class BaseBot
{
public:
	BaseBot(AI::AIWorld& world);
	~BaseBot();

	virtual void XInitialize();

	virtual void Update(float deltaTime);

	void Render();

	X::Math::Vector2 Truncate(X::Math::Vector2 vec, float amount);

	X::Math::Vector2& GetPosition() { return m_agent.Position(); }

	void KeepOnScreen();

protected:
	AI::Agent m_agent;
	X::TextureId m_texture_id;
	AI::SteeringModule m_steering;
	float m_rotation;
	float m_screenWidth;
	float m_screenHeight;
};
