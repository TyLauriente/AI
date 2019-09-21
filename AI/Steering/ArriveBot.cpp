#include "ArriveBot.h"


ArriveBot::ArriveBot(AI::AIWorld& world)
	: BaseBot(world)
{
	m_steering.AddBehaviour<AI::ArriveBehaviour>();
	m_steering.GetBehaviour<AI::ArriveBehaviour>("Arrive")->SetActive(true);
	m_steering.GetBehaviour<AI::ArriveBehaviour>("Arrive")->SlowingRadius() = RANGE;
	m_agent.MaxSpeed() = MAX_SPEED;
	m_agent.Mass() = MASS;
}

ArriveBot::~ArriveBot()
{
	
}

void ArriveBot::XInitialize()
{
	m_texture_id = X::LoadTexture("Seek.png");
	m_agent.Position() = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
}


void ArriveBot::Update(float deltaTime)
{
	
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		SetTarget({ X::GetMouseScreenX() * 1.0f, X::GetMouseScreenY() * 1.0f });
	}
	m_agent.Velocity() = m_agent.Velocity() + m_steering.Calculate();


	KeepOnScreen();
	SetRotation();
	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void ArriveBot::SetTarget(X::Math::Vector2 target)
{
	m_agent.Destination() = target;
}

void ArriveBot::SetRotation()
{
	X::Math::Vector2 direction = m_agent.Velocity();
	m_rotation = atan2(direction.y, direction.x) + X::Math::kPi * 0.5f;
}


