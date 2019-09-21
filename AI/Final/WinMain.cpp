#include<XEngine.h>
#include<AI.h>
#include"TileMap.h"
#include"FreeForAllAgent.h"

void XInitialize();
void XTerminate();

const int AMOUNT_OF_AGENTS = 4;


AI::AIWorld world;
TileMap map;
std::vector<FreeForAllAgent*> agents;

void CheckCollisions()
{

}


bool Update(float deltaTime)
{
	for (auto& agent : agents)
	{
		agent->Update(deltaTime);
	}

	map.Render();
	for (auto& agent : agents)
	{
		agent->Render();
	}
	
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start();
	XInitialize();

	X::Run(Update);

	XTerminate();
	X::Stop();
}

//Function To Calculate Cost to travel to end node from gien end to current node
std::function<float(AI::Graph::Coordinate, AI::Graph::Coordinate)> CalculateCostFromEnd =
[](AI::Graph::Coordinate c, AI::Graph::Coordinate end) {

	X::Math::Vector2 v_end = { static_cast<float>(end.x), static_cast<float>(end.y) };
	X::Math::Vector2 v_current = { static_cast<float>(c.x), static_cast<float>(c.y) };
	return (X::Math::Magnitude(v_current - v_end));
};


void XInitialize()
{
	map.XInitialize();
	agents.push_back(new FreeForAllAgent(world, { X::GetScreenWidth() * 0.5f, 50.0f }));
	agents.push_back(new FreeForAllAgent(world, { static_cast<float>(X::GetScreenWidth() - 50), X::GetScreenHeight() * 0.5f }));
	agents.push_back(new FreeForAllAgent(world, { X::GetScreenWidth() * 0.5f, static_cast<float>(X::GetScreenHeight() - 50) }));
	agents.push_back(new FreeForAllAgent(world, { 50.0f, X::GetScreenHeight() * 0.5f }));
	for (auto& agent : agents)
	{
		agent->XInitialize(map);
		agent->SetCostFunction([](AI::Graph::Coordinate next, AI::Graph::Coordinate end) {
			world.GetNavGraph().GetNode(next).g = map.GetTile(next.y, next.x);
			world.GetNavGraph().GetNode(next).h = CalculateCostFromEnd(next, end);
		});
	}

	std::list<AI::Graph::Coordinate> blocked;

	for (int x = 0; x < map.GetRows(); ++x)
	{
		for (int y = 0; y < map.GetColumns(); ++y)
		{
			if (map.GetTile(x, y) != 0)
			{
				blocked.push_back(AI::Graph::Coordinate((uint32_t)x, (uint32_t)y));
				X::Math::Vector2 start = { x * map.GetTileSize(), y * map.GetTileSize() };
				X::Math::Vector2 end = start;
				end.x += map.GetTileSize();
				world.AddWall({ start, end });
				end.x -= map.GetTileSize();
				end.y += map.GetTileSize();
				world.AddWall({ start, end });
				end.x += map.GetTileSize();
				start.y += map.GetTileSize();
				world.AddWall({ start, end });
				end.y -= map.GetTileSize();
				start.x += map.GetTileSize();
				world.AddWall({ start, end });
			}
		}
	}

	world.GetNavGraph().Init(map.GetRows(), map.GetColumns(), map.GetTileSize());
	world.GetNavGraph().SetBlocked(blocked);
	
}

void XTerminate()
{
	
}
