#include "AvoidTest.h"



AvoidTest::AvoidTest()
{
	
}


AvoidTest::~AvoidTest()
{
	delete m_avoidBot;
	m_avoidBot = nullptr;
}


void AvoidTest::XInitialize()
{
	float height = static_cast<float>(X::GetScreenHeight());
	float width = static_cast<float>(X::GetScreenWidth());

	X::Math::Circle obstacle;

	for (int x = 75; x < width - 75; x += X::Random(200, 500))
	{
		for (int y = 75; y < height - 75; y += X::Random(200, 500))
		{
			obstacle.center = { x * 1.0f, y * 1.0f };
			obstacle.radius = static_cast<float>(X::Random(10, 100));
			m_world.AddObstacles(obstacle);
		}
	}
	
	m_avoidBot = new AvoidBot(m_world);
	m_avoidBot->XInitialize();
}

void AvoidTest::Update(float deltaTime)
{
	m_avoidBot->Update(deltaTime);
}

void AvoidTest::Render()
{
	if (m_avoidBot)
	{
		m_avoidBot->Render();
	}

	std::vector<X::Math::Circle> obstacles = m_avoidBot->GetObstacles();
	for (const auto& circle : obstacles)
	{
		X::DrawScreenCircle(circle, X::Math::Vector4::Green());
	}
}

void AvoidTest::SetTarget(X::Math::Vector2 target)
{
	m_avoidBot->SetTarget(target);
}