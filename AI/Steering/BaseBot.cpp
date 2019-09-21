#include"BaseBot.h"
#include "SeekBehaviour.h"


BaseBot::BaseBot(AI::AIWorld& world)
	: m_agent{ world}
	, m_texture_id{ 0 }
	, m_steering{ m_agent }
	, m_rotation{ 0.0f }
{
	
}

BaseBot::~BaseBot()
{
	m_steering.Purge();
}


void BaseBot::XInitialize()
{
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}

void BaseBot::Update(float deltaTime)
{
	deltaTime;
}


void BaseBot::Render()
{
	X::DrawSprite(m_texture_id, m_agent.Position(), m_rotation);
}

X::Math::Vector2 BaseBot::Truncate(X::Math::Vector2 vec, float amount)
{
	if (vec.x > amount)
	{
		vec.x = amount;
	}
	else if (vec.x < -amount)
	{
		vec.x = -amount;
	}

	if (vec.y > amount)
	{
		vec.y = amount;
	}
	else if (vec.y < -amount)
	{
		vec.y = -amount;
	}
	return vec;
}

void BaseBot::KeepOnScreen()
{
	if (m_agent.Position().x > m_screenWidth)
	{
		m_agent.Position().x = 0.0f;
	}
	else if (m_agent.Position().x < 0)
	{
		m_agent.Position().x = m_screenWidth;
	}
	if (m_agent.Position().y > m_screenHeight)
	{
		m_agent.Position().y = 0.0f;
	}
	else if (m_agent.Position().y < 0)
	{
		m_agent.Position().y = m_screenHeight;
	}
}