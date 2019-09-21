#include"FreeForAllAgent.h"
#include<AI.h>
#include<functional>



FreeForAllAgent::FreeForAllAgent(AI::AIWorld& world, X::Math::Vector2 home)
	: m_world{ world }
	, m_agent{ world }
	, m_stateMachine{ new AI::StateMachine<FreeForAllAgent>(*this) }
	, m_home{ home }
	, pathPlanner{ m_agent }
	, hp{ 100 }
	, ammo{ 10 }
	, m_dead{ false }
	, steering{ new AI::SteeringModule(m_agent) }
{
	m_agent.Position() = home;
	m_stateMachine->AddState<KillOpponents>();
	m_stateMachine->AddState<CollectAmmo>();
	m_stateMachine->ChangeState(0);
	m_agent.Mass() = MASS;
	m_agent.MaxSpeed() = MAX_SPEED;

	steering->AddBehaviour<AI::SeekBehaviour>()->SetActive(true);
	steering->AddBehaviour<AI::ArriveBehaviour>();

	
}

FreeForAllAgent::~FreeForAllAgent()
{

}

void FreeForAllAgent::XInitialize(TileMap& map)
{
	m_textureId = X::LoadTexture("Agent.png");
	pathPlanner.Init(map.GetRows(), map.GetColumns(), map.GetTileSize());
	m_agent.CollisionRadius() = static_cast<float>(X::GetSpriteWidth(m_textureId));
}

void FreeForAllAgent::Update(float deltaTime)
{
	m_stateMachine->Update(deltaTime);
}

void FreeForAllAgent::Render()
{
	if (path.size() > 1)
	{
		X::Math::Vector2 current = path[0];
		X::Math::Vector2 next = path[1];
		uint32_t index = 2;
		while (!(current == path.back()))
		{
			X::DrawScreenLine(current, next, X::Math::Vector4::Magenta());
			current = next;
			if (index < path.size())
			{
				next = path[index];
				index++;
			}
		}
	}
	X::DrawScreenText(("HP: " + std::to_string(hp)).c_str(), m_agent.Position().x - 30.0f, m_agent.Position().y - 70.0f, 15.0f, X::Math::Vector4::Red());
	X::DrawScreenText(("AMMO: " + std::to_string(ammo)).c_str(), m_agent.Position().x - 30.0f, m_agent.Position().y - 50.0f, 15.0f, X::Math::Vector4::DarkBlue());
	float rotation = atan2(m_agent.Heading().y, m_agent.Heading().x) + X::Math::kPi * 0.5f;
	X::DrawSprite(m_textureId, m_agent.Position(), rotation);
}

void FreeForAllAgent::SetCostFunction(std::function<void(AI::Graph::Coordinate, AI::Graph::Coordinate)> costFunction)
{
	pathPlanner.SetCostFunction(costFunction);
}
