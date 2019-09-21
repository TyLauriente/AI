#pragma once

#include<XEngine.h>
#include<AI.h>

//===================================Enemy Class

const float SIGHT_RANGE = 200;
const float SIGHT_ALERT_RANGE = 300;

class Patrol;
class Alert;
class Attack;

class Enemy
{
public:
	Enemy(X::Math::Vector2 startPos)
		: m_position{ startPos }
		, m_stateMachine{ new AI::StateMachine<Enemy>(*this) }
	{}

	void XInitialize()
	{
		m_txt_patrol = X::LoadTexture("Patrol.png");
		m_txt_check = X::LoadTexture("Check.png");
		m_txt_attack = X::LoadTexture("Attack.png");
		m_screenWidth = X::GetScreenWidth();
		m_screenHeight = X::GetScreenHeight();
		m_spriteWidth = X::GetSpriteWidth(m_txt_patrol);
		m_spriteHeight = X::GetSpriteHeight(m_txt_patrol);
		m_stateMachine->AddState<Patrol>();
		m_stateMachine->AddState<Alert>();
		m_stateMachine->AddState<Attack>();
		m_stateMachine->ChangeState(0);
	}

	void Update(float deltaTime, X::Math::Circle playerCircle, X::Math::Vector2 playerPos)
	{
		m_playerBoundingCircle = playerCircle;
		m_playerPosition = playerPos;
		m_stateMachine->Update(deltaTime);
	}

	void Render() const
	{
		//X::DrawScreenCircle(GetSightCircle(), X::Math::Vector4::Red());
		if(m_stateMachine->GetCurrentState() == 0)
		{
			X::DrawSprite(m_txt_patrol, m_position);
		}
		else if(m_stateMachine->GetCurrentState() == 1)
		{
			X::DrawSprite(m_txt_check, m_position);
		}
		else
		{
			X::DrawSprite(m_txt_attack, m_position);
		}
	}

	X::Math::Vector2& GetPosition() { return m_position; }

	X::Math::Vector2 GetPlayerPosition() const { return m_playerPosition; }

	X::Math::Circle GetPlayerBoundingCircle() const { return m_playerBoundingCircle; }

	float GetScreenWidth() const { return m_screenWidth; }

	float GetScreenHeight() const { return m_screenHeight; }

	float GetSpriteWidth() const { return m_spriteWidth; }

	float GetSpriteHeight() const { return m_spriteHeight; }

	X::Math::Circle GetBoundingCircle() const
	{
		X::Math::Circle c;
		c.center = m_position;
		c.radius = m_spriteWidth * 0.5f;
		return c;
	}

	X::Math::Circle GetSightCircle() const
	{
		X::Math::Circle c;
		c.center = m_position;
		c.radius = SIGHT_RANGE;
		return c;
	}

	void ChangeState(uint32_t index) { m_stateMachine->ChangeState(index); }


	const float SPEED = 150.0f;
private:
	X::Math::Vector2 m_position = { 0, 0 };
	X::Math::Vector2 m_playerPosition;
	X::Math::Circle m_playerBoundingCircle;
	X::TextureId m_txt_patrol;
	X::TextureId m_txt_check;
	X::TextureId m_txt_attack;
	float m_screenWidth;
	float m_screenHeight;
	float m_spriteWidth;
	float m_spriteHeight;
	AI::StateMachine<Enemy>* m_stateMachine;
};


enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Patrol : public AI::State<Enemy>
{
public:
	const float DIRECTION_DURATION = 4.0f;
	float directionTimer = 0.0f;


	void Enter(Enemy& agent) override
	{
		directionTimer = 0.0f;
		if(agent.GetPosition().x > agent.GetScreenWidth() * 0.5f)
		{
			m_direction = Direction::Left;
		}
		else
		{
			m_direction = Direction::Right;
		}
	}

	bool IsInSight(Enemy& agent) const
	{
		const X::Math::Vector2 enemyPos = agent.GetPosition();
		const X::Math::Vector2 playerPos = agent.GetPlayerPosition();
		float distance = X::Math::Magnitude(playerPos - enemyPos);
		return (distance < SIGHT_RANGE);

	}

	Direction GetNewRandomDirection(Direction oldDir) const
	{
		Direction newDir = static_cast<Direction>(X::Random(0, 3));
		while(newDir == oldDir)
		{
			newDir = static_cast<Direction>(X::Random(0, 3));
		}
		return newDir;
	}

	void Update(Enemy& agent, float deltaTime) override
	{
		if (IsInSight(agent))
		{
			agent.ChangeState(1);
		}


		directionTimer += deltaTime;
		if(m_direction == Direction::Left)
		{
			if(directionTimer >= DIRECTION_DURATION)
			{
				m_direction = Direction::Down;
				directionTimer = 0.0f;
			}
			else
			{
				if ((agent.GetPosition().x - (agent.SPEED * deltaTime)) >= (agent.GetSpriteWidth() * 0.5f))
				{
					agent.GetPosition().x -= agent.SPEED * deltaTime;
				}
				else
				{
					agent.GetPosition().x = agent.GetSpriteWidth();
					m_direction = GetNewRandomDirection(m_direction);
				}
			}
		}
		else if(m_direction == Direction::Right)
		{
			if (directionTimer >= DIRECTION_DURATION)
			{
				m_direction = Direction::Up;
				directionTimer = 0.0f;
			}
			else
			{
				if ((agent.GetPosition().x + (agent.GetSpriteWidth() * 0.5f)) + (agent.SPEED * deltaTime) < agent.GetScreenWidth())
				{
					agent.GetPosition().x += agent.SPEED * deltaTime;
				}
				else
				{
					agent.GetPosition().x = agent.GetScreenWidth() - (agent.GetSpriteWidth() * 0.5f);
					m_direction = GetNewRandomDirection(m_direction);
				}
			}
		}
		else if(m_direction == Direction::Up)
		{
			if (directionTimer >= DIRECTION_DURATION)
			{
				m_direction = Direction::Right;
				directionTimer = 0.0f;
			}
			else
			{
				if (agent.GetPosition().y - (agent.SPEED * deltaTime) >= agent.GetSpriteHeight() * 0.5f)
				{
					agent.GetPosition().y -= agent.SPEED * deltaTime;
				}
				else
				{
					agent.GetPosition().y = agent.GetSpriteHeight();
					m_direction = GetNewRandomDirection(m_direction);
				}
			}
		}
		else
		{
			if (directionTimer >= DIRECTION_DURATION)
			{
				m_direction = Direction::Left;
				directionTimer = 0.0f;
			}
			else
			{
				if ((agent.GetPosition().y + (agent.GetSpriteHeight() * 0.5f)) + (agent.SPEED * deltaTime) < agent.GetScreenHeight())
				{
					agent.GetPosition().y += agent.SPEED * deltaTime;
				}
				else
				{
					agent.GetPosition().y = agent.GetScreenHeight() - (agent.GetSpriteHeight() * 0.5f);
					m_direction = GetNewRandomDirection(m_direction);
				}
			}
		}
	}

	void Exit(Enemy& agent) override
	{
		
	}
private:
	Direction m_direction;

};


class Alert : public AI::State<Enemy>
{
public:
	const float CHECK_DURATION = 0.5f;
	float checkTimer = 0.0f;

	bool IsInSight(Enemy& agent) const
	{
		const X::Math::Vector2 enemyPos = agent.GetPosition();
		const X::Math::Vector2 playerPos = agent.GetPlayerPosition();
		const float distance = X::Math::Magnitude(playerPos - enemyPos);

		return (distance < SIGHT_RANGE);

	}


	void Enter(Enemy& agent) override
	{
		checkTimer = 0.0f;
	}
		

	void Update(Enemy& agent, float deltaTime) override
	{
		if(checkTimer >= CHECK_DURATION)
		{
			agent.ChangeState(2);
		}
		else
		{
			if (!IsInSight(agent))
			{
				agent.ChangeState(0);
			}
			else
			{
				checkTimer += deltaTime;
			}
		}
	}

	void Exit(Enemy& agent) override
	{

	}
	
};

class Attack : public AI::State<Enemy>
{
public:

	bool IsInSight(Enemy& agent) const
	{
		const X::Math::Vector2 enemyPos = agent.GetPosition();
		const X::Math::Vector2 playerPos = agent.GetPlayerPosition();
		const float distance = X::Math::Magnitude(playerPos - enemyPos);

		return (distance < SIGHT_ALERT_RANGE);

	}

	void Enter(Enemy& agent) override
	{
		
	}


	void Update(Enemy& agent, float deltaTime) override
	{
		if(IsInSight(agent))
		{
			X::Math::Vector2 velocity;
			agent.GetPosition().x += (agent.GetPlayerPosition().x - agent.GetPosition().x) * deltaTime;
			agent.GetPosition().y += (agent.GetPlayerPosition().y - agent.GetPosition().y) * deltaTime;
		}
		else
		{
			agent.ChangeState(0);
		}
	}

	void Exit(Enemy& agent) override
	{

	}

};