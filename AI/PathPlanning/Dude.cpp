#include "Dude.h"

#include"AI.h"
#include"XEngine.h"
#include"SeekBehaviour.h"
#include"ArriveBehaviour.h"

Dude::Dude(AI::AIWorld& world)
	: m_agent{ world }
	, m_world{ world }
	, m_pathPlanner{ m_agent }
	, m_steering{ m_agent }
	, m_textureId{ 0 }
	, m_spriteWidth{ 0.0f }
	, m_spriteHeight{ 0.0f }
	, m_previousTarget{ 0.0f, 0.0f }
	, m_currentTarget{ 0 }
	, m_screenWidth{ 0.0f }
	, m_screenHeight{ 0.0f }
{
}


Dude::~Dude()
{
}

void Dude::Init(std::function<void(AI::Graph::Coordinate)> setCostFunction, uint32_t rows, uint32_t collumns, float unitSize)
{
	m_textureId = X::LoadTexture("TopDownCharacter.png");
	m_spriteWidth = static_cast<float>(X::GetSpriteWidth(m_textureId));
	m_spriteHeight = static_cast<float>(X::GetSpriteHeight(m_textureId));
	m_pathPlanner.SetCostFunction(setCostFunction);
	m_steering.AddBehaviour<AI::SeekBehaviour>()->SetActive(true);
	m_steering.AddBehaviour<AI::ArriveBehaviour>();
	m_steering.GetBehaviour<AI::ArriveBehaviour>("Arrive")->SlowingRadius() = DISTANCE_TO_STOP;
	m_agent.Mass() = MASS;
	m_agent.MaxSpeed() = SPEED;
	m_screenWidth = X::GetScreenWidth();
	m_screenHeight = X::GetScreenHeight();
	m_pathPlanner.Init(rows, collumns, unitSize);
}

//Very Messy, but it's not in the AI framework. Only a test ;)
void Dude::Update(float deltaTime, X::Math::Vector2 targetPos)
{
	if (!(targetPos.x > 0 && targetPos.y > 0 && targetPos.x < m_screenWidth && targetPos.y < m_screenHeight))
	{
		return;
	}
	if (!m_agent.World().GetNavGraph().GetNode(AI::Graph::Coordinate{ (uint32_t)targetPos.x / 50, (uint32_t)targetPos.y / 50 }).blocked)
	{
		if (m_previousTarget != targetPos)
		{
			m_previousTarget = targetPos;
			m_path.clear();
			m_pathPlanner.RequestPath(targetPos);
			m_path = m_pathPlanner.GetPath();
			m_currentTarget = 0;
			m_agent.Destination() = m_path[m_currentTarget];
			m_steering.GetBehaviour<AI::SeekBehaviour>("Seek")->SetActive(true);
			m_steering.GetBehaviour<AI::ArriveBehaviour>("Arrive")->SetActive(false);
		}
		if (m_steering.GetBehaviour<AI::SeekBehaviour>("Seek")->IsActive())
		{
			if (m_currentTarget == m_path.size() - 1)
			{
				m_steering.GetBehaviour<AI::SeekBehaviour>("Seek")->SetActive(false);
				m_steering.GetBehaviour<AI::ArriveBehaviour>("Arrive")->SetActive(true);
			}
			else
			{
				if (X::Math::DistanceSqr(m_agent.Position(), m_agent.Destination()) <= DISTANCE_TO_STOP * DISTANCE_TO_STOP)
				{
					m_currentTarget++;
					m_agent.Destination() = m_path[m_currentTarget];
					m_agent.Destination().x;
					m_agent.Destination().y;
				}
			}
		}
		m_agent.Velocity() += m_steering.Calculate();
	}
	else
	{
		m_agent.Velocity() -= m_agent.Velocity() * 0.3f;
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

	SetRotation();
	m_agent.Position() += m_agent.Velocity() * deltaTime;
}

void Dude::SetRotation()
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