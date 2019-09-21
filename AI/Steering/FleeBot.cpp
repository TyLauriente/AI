#include "FleeBot.h"


FleeBot::FleeBot(AI::AIWorld& world)
	: BaseBot(world)
{
	m_steering.AddBehaviour<AI::FleeBehaviour>();
	m_steering.GetBehaviour<AI::FleeBehaviour>("Flee")->SetActive(true);
	m_agent.MaxSpeed() = MAX_SPEED;
	m_agent.Mass() = MASS;
}

FleeBot::~FleeBot()
{

}

void FleeBot::XInitialize()
{
	m_texture_id = X::LoadTexture("Seek.png");
	m_agent.Position() = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}


void FleeBot::Update(float deltaTime)
{
	SetTarget({ X::GetMouseScreenX() * 1.0f, X::GetMouseScreenY() * 1.0f });
	if(X::Math::MagnitudeSqr(m_agent.Destination() - m_agent.Position()* 1.0f) < RANGE * RANGE)
	{
		m_agent.Velocity() = m_agent.Velocity() + m_steering.Calculate();
	}

	KeepOnScreen();

	SetRotation();
	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void FleeBot::SetTarget(X::Math::Vector2 target)
{
	m_agent.Destination() = target;
}

void FleeBot::SetRotation()
{
	X::Math::Vector2 direction = m_agent.Velocity();
	m_rotation = atan2(direction.y, direction.x) + X::Math::kPi * 0.5f;
}


