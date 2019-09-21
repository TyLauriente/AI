#include "FleeTest.h"


FleeTest::FleeTest()
{
	m_fleeBot = new FleeBot(m_seekWorld);
}


FleeTest::~FleeTest()
{
	delete m_fleeBot;
	m_fleeBot = nullptr;
}


void FleeTest::XInitialize()
{
	m_fleeBot->XInitialize();
}

void FleeTest::Update(float deltaTime)
{
	m_fleeBot->Update(deltaTime);
}

void FleeTest::Render()
{
	if (m_fleeBot)
	{
		m_fleeBot->Render();
	}
}

void FleeTest::SetTarget(X::Math::Vector2 target)
{
	m_fleeBot->SetTarget(target);
}