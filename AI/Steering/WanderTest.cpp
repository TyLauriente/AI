#include "WanderTest.h"



WanderTest::WanderTest()
{

}


WanderTest::~WanderTest()
{
	delete m_wanderBot;
	m_wanderBot = nullptr;
}


void WanderTest::XInitialize()
{
	m_wanderBot = new WanderBot(m_world);
	m_wanderBot->XInitialize();
}

void WanderTest::Update(float deltaTime)
{
	m_wanderBot->Update(deltaTime);
}

void WanderTest::Render()
{
	if (m_wanderBot)
	{
		m_wanderBot->Render();
	}
}