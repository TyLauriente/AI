#include<XEngine.h>
#include<ImGui/Inc/imgui.h>
#include<AI.h>
#include"Player.h"
#include"Enemy.h"


void XInitialize();
void XTerminate();

Player player;

Enemy enemy1({ 50, 50 });
Enemy enemy2({ 50, 800 });
Enemy enemy3({ 1500, 50 });
Enemy enemy4({ 1500, 800 });

//void OnGui()
//{
//	ImGui::Begin("Dada");
//	ImGui::SliderFloat2("Position", &position.x, 300.0f, 500.0f);
//	ImGui::End();
//}

bool Update(float deltaTime)
{
	player.Update(deltaTime);
	enemy1.Update(deltaTime, player.GetBoundingCircle(), player.GetPosition());
	enemy2.Update(deltaTime, player.GetBoundingCircle(), player.GetPosition());
	enemy3.Update(deltaTime, player.GetBoundingCircle(), player.GetPosition());
	enemy4.Update(deltaTime, player.GetBoundingCircle(), player.GetPosition());
	
	player.Render();
	enemy1.Render();
	enemy2.Render();
	enemy3.Render();
	enemy4.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("xconfig.json");
	XInitialize();


	X::Run(Update);

	XTerminate();
	X::Stop();
}

void XInitialize()
{
	player.XInitiaize();
	enemy1.XInitialize();
	enemy2.XInitialize();
	enemy3.XInitialize();
	enemy4.XInitialize();
}

void XTerminate()
{

}