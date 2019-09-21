#include "SeekBot.h"

SeekBot::SeekBot(AI::AIWorld& world)
	: BaseBot(world)
{
	m_steering.AddBehaviour<AI::SeekBehaviour>();
	m_steering.GetBehaviour<AI::SeekBehaviour>("Seek")->SetActive(true);
	m_agent.MaxSpeed() = MAX_SPEED;
	m_agent.Mass() = MASS;
}

SeekBot::~SeekBot()
{
	
}

void SeekBot::XInitialize()
{
	m_texture_id = X::LoadTexture("Seek.png");
	m_agent.Position() = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f};
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}


void SeekBot::Update(float deltaTime)
{
	SetTarget({ X::GetMouseScreenX() * 1.0f, X::GetMouseScreenY() * 1.0f });
	m_agent.Velocity() = m_agent.Velocity() + m_steering.Calculate();
	SetRotation();
	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void SeekBot::SetTarget(X::Math::Vector2 target)
{
	m_agent.Destination() = target;
}

void SeekBot::SetRotation()
{
	X::Math::Vector2 direction = m_agent.Velocity();
	m_rotation = atan2(direction.y, direction.x) + X::Math::kPi * 0.5f;
}