#include "FlockBot.h"

FlockBot::FlockBot(AI::AIWorld& world)
	: BaseBot(world)
{
	m_steering.AddBehaviour<AI::FlockBehaviour>()->SetActive(true);
	m_steering.GetBehaviour<AI::FlockBehaviour>("Flock")->NeighborRadius() = NEIGHBOR_RADIUS;
	m_steering.GetBehaviour<AI::FlockBehaviour>("Flock")->AllignmentWeight() = 2.5f;
	m_steering.GetBehaviour<AI::FlockBehaviour>("Flock")->CohesionWeight() = 2.0f;
	m_steering.GetBehaviour<AI::FlockBehaviour>("Flock")->SeperationWeight() = 2.3f;
	
	m_steering.AddBehaviour<AI::WanderBehaviour>()->SetActive(true);
	m_steering.GetBehaviour<AI::WanderBehaviour>("Wander")->CircleDistance() = CIRCLE_DISTANCE;
	m_steering.GetBehaviour<AI::WanderBehaviour>("Wander")->CircleRadius() = DIRECTION_CHANGE;

	m_steering.AddBehaviour<AI::AvoidBehaviour>()->SetActive(true);
	m_steering.GetBehaviour<AI::AvoidBehaviour>("Avoid")->SetSightRange(SIGHT_RANGE);
	m_steering.GetBehaviour<AI::AvoidBehaviour>("Avoid")->AvoidWeight() = 
		m_steering.GetBehaviour<AI::FlockBehaviour>("Flock")->TotalWeight();

	m_agent.MaxSpeed() = MAX_SPEED;
	m_agent.Mass() = MASS;
	int random = X::Random(0, 3);
	if (random == 0)
	{
		m_agent.Velocity() = { 1, 0 };
	}
	else if(random == 1)
	{
		m_agent.Velocity() = { -1, 0 };
	}
	else if (random == 2)
	{
		m_agent.Velocity() = { 0, 1 };

	}
	else
	{
		m_agent.Velocity() = { 0, -1 };
	}
}

FlockBot::~FlockBot()
{
	m_agent.World().UnregisterAgent(&m_agent);
}

void FlockBot::XInitialize()
{
	m_texture_id = X::LoadTexture("Flock.png");
	m_agent.Position() = { X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f };
	m_agent.CollisionRadius() = static_cast<float>(X::GetSpriteHeight(m_texture_id) * 1.5f);
	m_screenWidth = static_cast<float>(X::GetScreenWidth());
	m_screenHeight = static_cast<float>(X::GetScreenHeight());
	m_agent.Position() = { static_cast<float>(X::Random(0, static_cast<int>(m_screenWidth))), 
		static_cast<float>(X::Random(0, static_cast<int>(m_screenHeight))) };
}


void FlockBot::Update(float deltaTime)
{
	m_agent.Velocity() = m_agent.Velocity() + m_steering.Calculate();
	
	if ((m_agent.Velocity().x > MAX_SPEED || m_agent.Velocity().y > MAX_SPEED) ||
		(m_agent.Velocity().x < -MAX_SPEED || m_agent.Velocity().y < -MAX_SPEED))
	{
		m_agent.Velocity() = X::Math::Normalize(m_agent.Velocity()) * MAX_SPEED;
	}
	if (m_previousVelocities.size() > 9)
	{
		m_previousVelocities.pop_front();
		m_previousVelocities.push_back(m_agent.Velocity());
	}
	else
	{
		m_previousVelocities.push_back(m_agent.Velocity());
	}
	std::string test = std::to_string((1.0f / deltaTime));
	X::DrawScreenText(test.c_str(), 0.0f, 0.0f, 24.0f, X::Math::Vector4::Green());
	SetRotation();
	//if (m_agent.Position().x > m_screenWidth || m_agent.Position().x < 0)
	//{
	//	m_agent.Velocity().x *= -1;
	//}
	//if (m_agent.Position().y > m_screenHeight || m_agent.Position().y < 0)
	//{
	//	m_agent.Velocity().y *= -1;
	//}

	KeepOnScreen();

	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void FlockBot::SetTarget(X::Math::Vector2 target)
{
	m_agent.Destination() = target;
}

void FlockBot::SetRotation()
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