#include "WanderBot.h"

WanderBot::WanderBot(AI::AIWorld& world)
	: BaseBot(world)
{
	m_steering.AddBehaviour<AI::WanderBehaviour>();
	m_steering.GetBehaviour<AI::WanderBehaviour>("Wander")->SetActive(true);
	m_steering.GetBehaviour<AI::WanderBehaviour>("Wander")->CircleDistance() = CIRCLE_DISTANCE;
	m_steering.GetBehaviour<AI::WanderBehaviour>("Wander")->CircleRadius() = DIRECTION_CHANGE;


	m_agent.MaxSpeed() = MAX_SPEED;
	m_agent.Mass() = MASS;
}



WanderBot::~WanderBot()
{

}

void WanderBot::XInitialize()
{
	m_texture_id = X::LoadTexture("Seek.png");
	m_agent.Position() = { 0.0f, X::GetScreenHeight() * 0.5f - 60.0f };
	m_agent.Velocity() = { 5.0f, 0.0f };
	m_agent.CollisionRadius() = X::GetSpriteWidth(m_texture_id) * 0.7f;
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}


void WanderBot::Update(float deltaTime)
{
	m_agent.Velocity() = m_agent.Velocity() + m_steering.Calculate();
	KeepOnScreen();
	if (m_previousVelocities.size() > 9)
	{
		m_previousVelocities.pop_front();
		m_previousVelocities.push_back(m_agent.Velocity());
	}
	else
	{
		m_previousVelocities.push_back(m_agent.Velocity());
	}
	SetRotation();
	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void WanderBot::SetTarget(const X::Math::Vector2& target)
{
	m_agent.Destination() = target;
}

void WanderBot::SetRotation()
{
	X::Math::Vector2 avgVelocity{ 0.0f, 0.0f };
	int velCount = 0;
	for (const auto& vel : m_previousVelocities)
	{
		avgVelocity += vel;
		++velCount;
	}
	if (velCount > 0)
	{
		avgVelocity /= static_cast<float>(velCount);
	}
	X::Math::Vector2 direction = avgVelocity;
	m_rotation = atan2(direction.y, direction.x) + X::Math::kPi * 0.5f;
}
