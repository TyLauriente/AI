#include "ArriveTest.h"



ArriveTest::ArriveTest()
{
	m_arriveBot = new ArriveBot(m_seekWorld);
}


ArriveTest::~ArriveTest()
{
	delete m_arriveBot;
	m_arriveBot = nullptr;
}


void ArriveTest::XInitialize()
{
	m_arriveBot->XInitialize();
}

void ArriveTest::Update(float deltaTime)
{
	m_arriveBot->Update(deltaTime);
}

void ArriveTest::Render()
{
	if (m_arriveBot)
	{
		m_arriveBot->Render();
	}
}

void ArriveTest::SetTarget(X::Math::Vector2 target)
{
	m_arriveBot->SetTarget(target);
}