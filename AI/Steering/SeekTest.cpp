#include "SeekTest.h"



SeekTest::SeekTest()
{
	m_seekBot = new SeekBot(m_seekWorld);
}


SeekTest::~SeekTest()
{
	delete m_seekBot;
	m_seekBot = nullptr;
}


void SeekTest::XInitialize()
{
	m_seekBot->XInitialize();
}

void SeekTest::Update(float deltaTime)
{
	m_seekBot->Update(deltaTime);
}

void SeekTest::Render()
{
	if (m_seekBot)
	{
		m_seekBot->Render();
	}
}

void SeekTest::SetTarget(X::Math::Vector2 target)
{
	m_seekBot->SetTarget(target);
}