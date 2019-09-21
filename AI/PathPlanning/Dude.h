#pragma once

#include<AI.h>


class Dude
{
public:
	Dude(AI::AIWorld& world);
	~Dude();

	void Init(std::function<void(AI::Graph::Coordinate)> setCostFunction, uint32_t rows, uint32_t collumns, float unitSize);

	void Update(float deltaTime, X::Math::Vector2 targetPos);

	void Render() { X::DrawSprite(m_textureId, m_agent.Position(), m_rotation); }

	X::Math::Vector2 GetPosition() { return m_agent.Position(); }

	void SetRotation();

private:
	const float DISTANCE_TO_STOP = 30.0f;
	const float MASS = 10.0f;
	const float SPEED = 400.0f;

	AI::Agent m_agent;
	AI::AIWorld& m_world;
	AI::PathPlanner m_pathPlanner;
	AI::SteeringModule m_steering;
	X::TextureId m_textureId;
	float m_spriteWidth;
	float m_spriteHeight;
	std::vector<X::Math::Vector2> m_path;
	X::Math::Vector2 m_previousTarget;
	int m_currentTarget;
	float m_screenWidth;
	float m_screenHeight;
	float m_rotation;
	std::list<X::Math::Vector2> m_previousVelocities;
	int m_velocities = 0;
};

