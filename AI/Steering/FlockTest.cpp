#include "FlockTest.h"



FlockTest::FlockTest()
{
	
}


FlockTest::~FlockTest()
{
	for (int index = 0; index < AMOUNT_OF_FLOCKBOTS; ++index)
	{
		delete m_flockBot[index];
		m_flockBot[index] = nullptr;
	}
}


void FlockTest::XInitialize()
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
	for (int index = 0; index < AMOUNT_OF_FLOCKBOTS; ++index)
	{
		m_flockBot[index] = new FlockBot(m_world);
		m_flockBot[index]->XInitialize();
	}
}

void FlockTest::Update(float deltaTime)
{
	for (int index = 0; index < AMOUNT_OF_FLOCKBOTS; ++index)
	{
		m_flockBot[index]->Update(deltaTime);
	}
}

void FlockTest::Render()
{
	for (int index = 0; index < AMOUNT_OF_FLOCKBOTS; ++index)
	{
		if (m_flockBot[index])
		{
			m_flockBot[index]->Render();
		}
	}

	std::vector<X::Math::Circle> obstacles = m_flockBot[0]->GetObstacles();
	for (const auto& circle : obstacles)
	{
		X::DrawScreenCircle(circle, X::Math::Vector4::Green());
	}
}

void FlockTest::SetTarget(X::Math::Vector2 target)
{
	for (int index = 0; index < AMOUNT_OF_FLOCKBOTS; ++index)
	{
		m_flockBot[index]->SetTarget(target);
	}
}