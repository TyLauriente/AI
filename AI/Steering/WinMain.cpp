#include<XEngine.h>
#include<ImGui/Inc/imgui.h>
#include<AI.h>
#include"SeekTest.h"
#include"FleeTest.h"
#include"ArriveTest.h"
#include"AvoidTest.h"
#include"WanderTest.h"
#include"FlockTest.h"


void XInitialize();
void XTerminate();

const int AMOUNT_OF_TESTS = 6;

enum class DemoType
{
	Seek,
	Flee,
	Arrive,
	Wander,
	AvoidAndWander,
	Flock
};

std::string StringTypes[AMOUNT_OF_TESTS]
{
	"Seek",
	"Flee",
	"Arrive",
	"Wander",
	"Avoid + Wander",
	"Flock"
};

SeekTest* seekTest = nullptr;
FleeTest* fleeTest = nullptr;
ArriveTest* arriveTest = nullptr;
AvoidTest* avoidTest = nullptr;
WanderTest* wanderTest = nullptr;
FlockTest* flockTest = nullptr;

int demoType;

void OnGui()
{
	ImGui::Begin("Behaviour");
	ImGui::SetWindowPos({ 0,0 });
	ImGui::SetWindowSize({ 300, 50 });
	ImGui::SliderInt(StringTypes[static_cast<int>(demoType)].c_str(), &demoType, 0, AMOUNT_OF_TESTS - 1);
	ImGui::End();
}

bool Update(float deltaTime)
{
	OnGui();

	if(static_cast<DemoType>(demoType) == DemoType::Seek)
	{
		seekTest->Update(deltaTime);
		seekTest->Render();
	}
	else if(static_cast<DemoType>(demoType) == DemoType::Flee)
	{
		fleeTest->Update(deltaTime);
		fleeTest->Render();
	}
	else if (static_cast<DemoType>(demoType) == DemoType::Arrive)
	{
		arriveTest->Update(deltaTime);
		arriveTest->Render();
	}
	else if (static_cast<DemoType>(demoType) == DemoType::Wander)
	{
		wanderTest->Update(deltaTime);
		wanderTest->Render();
	}
	else if (static_cast<DemoType>(demoType) == DemoType::AvoidAndWander)
	{
		avoidTest->Update(deltaTime);
		avoidTest->Render();
	}
	else if (static_cast<DemoType>(demoType) == DemoType::Flock)
	{
		flockTest->Update(deltaTime);
		flockTest->Render();
	}

	

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	seekTest = new SeekTest();
	fleeTest = new FleeTest();
	arriveTest = new ArriveTest();
	avoidTest = new AvoidTest();
	wanderTest = new WanderTest();
	flockTest = new FlockTest();

	X::Start("xconfig.json");
	XInitialize();


	X::Run(Update);

	XTerminate();
	X::Stop();
}

void XInitialize()
{
	seekTest->XInitialize();
	fleeTest->XInitialize();
	arriveTest->XInitialize();
	avoidTest->XInitialize();
	wanderTest->XInitialize();
	flockTest->XInitialize();
}

void XTerminate()
{
	delete seekTest;
	seekTest = nullptr;
	delete fleeTest;
	fleeTest = nullptr;
	delete arriveTest;
	arriveTest = nullptr;
	delete avoidTest;
	avoidTest = nullptr;
	delete wanderTest;
	wanderTest = nullptr;
	delete flockTest;
	flockTest = nullptr;
}