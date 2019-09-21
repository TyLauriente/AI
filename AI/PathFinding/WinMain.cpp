#include<XEngine.h>
#include"TileMap.h"
#include"CameraManager.h"
#include"Graph.h"
#include<iostream>
#include <minwindef.h>
#include<algorithm>

using coord = AI::Graph::Coordinate;
const float TILE_SIZE = 50.0f;

void XInitialize();
void XTerminate();


TileMap* map;
AI::Graph::Coordinate start{ 0, 0 }, end{ 0, 0 };
AI::Graph graph;
std::vector<AI::Graph::Coordinate> path;
std::vector<AI::Graph::Node> searchedNodes;
bool choose = true;
std::list<coord> blockedNodes;

//Function To Calculate Cost to travel to end node from start to current node
std::function<float(coord)> CalculateCostFromStart =
[](coord c) {
	X::Math::Vector2 v_start = { static_cast<float>(start.x), static_cast<float>(start.y) };
	X::Math::Vector2 v_current = { static_cast<float>(c.x), static_cast<float>(c.y) };
	return X::Math::Magnitude(v_current - v_start);
};

//Function To Calculate Cost to travel to end node from gien end to current node
std::function<float(coord)> CalculateCostFromEnd =
[](coord c) {
	
	X::Math::Vector2 v_end = { static_cast<float>(end.x), static_cast<float>(end.y) };
	X::Math::Vector2 v_current = { static_cast<float>(c.x), static_cast<float>(c.y) };	
	return (X::Math::Magnitude(v_current - v_end));
};

void DrawLineCamera(X::Math::Vector2 v1, X::Math::Vector2 v2, X::Math::Vector4 v3)
{
	v1.x -= CameraManager::Get()->m_position.x;
	v1.y -= CameraManager::Get()->m_position.y;
	v2.x -= CameraManager::Get()->m_position.x;
	v2.y -= CameraManager::Get()->m_position.y;
	X::DrawScreenLine(v1, v2, v3);
}


X::Math::Vector2 ConvertToScreen(AI::Graph::Coordinate coord)
{
	X::Math::Vector2 screen;
	screen.x = (coord.x * TILE_SIZE) + 25;
	screen.y = (coord.y * TILE_SIZE) + 25;
	return screen;
}

void RenderPath()
{
	if (!path.empty())
	{
		AI::Graph::Coordinate current = path.front();
		AI::Graph::Coordinate next = path[1];
		uint32_t index = 2;

		while (!(current == path.back()))
		{
			DrawLineCamera(ConvertToScreen(current), ConvertToScreen(next), X::Math::Vector4::Magenta());
			current = next;
			if (index < path.size())
			{
				next = path[index];
				index++;
			}
		}
	}
}

void RenderSearchedNodes()
{
	if (!searchedNodes.empty())
	{
		for(const auto& node : searchedNodes)
		{
			DrawLineCamera(ConvertToScreen(node.coordinate),
				ConvertToScreen(node.parent), X::Math::Vector4::Green());
		}
	}
}

void CheckMouseInput()
{
	//Check For Start click and End Click
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		map->ChangeMap(static_cast<int>(start.y), static_cast<int>(start.x), 0);
		start.x = static_cast<uint32_t>((X::GetMouseScreenX() + CameraManager::Get()->m_position.x) / TILE_SIZE);
		start.y = static_cast<uint32_t>((X::GetMouseScreenY() + CameraManager::Get()->m_position.y) / TILE_SIZE);
		map->ChangeMap(static_cast<int>(start.y), static_cast<int>(start.x), 1);
	}
	if (X::IsMousePressed(X::Mouse::RBUTTON))
	{
		map->ChangeMap(static_cast<int>(end.y), static_cast<int>(end.x), 0);
		end.x = static_cast<uint32_t>((X::GetMouseScreenX() + CameraManager::Get()->m_position.x) / TILE_SIZE);
		end.y = static_cast<uint32_t>((X::GetMouseScreenY() + CameraManager::Get()->m_position.y) / TILE_SIZE);
		map->ChangeMap(static_cast<int>(end.y), static_cast<int>(end.x), 2);
	}
	if (X::IsMousePressed(X::Mouse::MBUTTON))
	{
		coord blocked;
		blocked.x = static_cast<uint32_t>((X::GetMouseScreenX() + CameraManager::Get()->m_position.x) / TILE_SIZE);
		blocked.y = static_cast<uint32_t>((X::GetMouseScreenY() + CameraManager::Get()->m_position.y) / TILE_SIZE);
		if (std::find(blockedNodes.begin(), blockedNodes.end(), blocked) != blockedNodes.end())
		{
			blockedNodes.remove(blocked);
			map->ChangeMap(static_cast<int>(blocked.y), static_cast<int>(blocked.x), 0);
		}
		else
		{
			coord temp = blocked;
			blockedNodes.push_back(blocked);
			temp.x--;
			blockedNodes.push_back(temp);
			temp = blocked;
			temp.x--;
			temp.y--;
			blockedNodes.push_back(temp);
			temp.x++;
			blockedNodes.push_back(temp);
			temp.x++;
			blockedNodes.push_back(temp);
			temp.y++;
			blockedNodes.push_back(temp);
			temp.y++;
			blockedNodes.push_back(temp);
			temp.x--;
			blockedNodes.push_back(temp);
			temp.x--;
			blockedNodes.push_back(temp);

			map->ChangeMap(static_cast<int>(blocked.y), static_cast<int>(blocked.x), 3);
		}
	}
	if (X::IsKeyPressed(X::Keys::H))
	{
		coord highCostBlock;
		highCostBlock.x = static_cast<uint32_t>((X::GetMouseScreenX() + CameraManager::Get()->m_position.x) / TILE_SIZE);
		highCostBlock.y = static_cast<uint32_t>((X::GetMouseScreenY() + CameraManager::Get()->m_position.y) / TILE_SIZE);
		if (map->GetTile(highCostBlock.y, highCostBlock.x) == 4)
		{
			map->ChangeMap(static_cast<int>(highCostBlock.y), static_cast<int>(highCostBlock.x), 0);
		}
		else
		{
			map->ChangeMap(static_cast<int>(highCostBlock.y), static_cast<int>(highCostBlock.x), 4);
		}
	}
}

bool GoodStartAndEnd()
{
	return (start.x >= 0 && start.x < map->GetRows() &&
		start.y >= 0 && start.y < map->GetColumns() &&
		end.x >= 0 && end.x < map->GetRows() &&
		end.y >= 0 && end.y < map->GetColumns());
}

bool Update(float deltaTime)
{
	map->Render();

	std::string frameRate = "FPS: " + std::to_string((1.0f / deltaTime));

	X::DrawScreenText(frameRate.c_str(), 0, 0, 24.0f, X::Math::Vector4::Green());

	if (X::IsKeyDown(X::Keys::RIGHT))
	{
		CameraManager::Get()->m_position.x += deltaTime * 500 * ((X::IsKeyDown(X::Keys::LSHIFT)) ? 10 : 1);
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		CameraManager::Get()->m_position.x -= deltaTime * 500 * ((X::IsKeyDown(X::Keys::LSHIFT)) ? 10 : 1);
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		CameraManager::Get()->m_position.y -= deltaTime * 500 * ((X::IsKeyDown(X::Keys::LSHIFT)) ? 10 : 1);
	}
	if (X::IsKeyDown(X::Keys::DOWN))
	{
		CameraManager::Get()->m_position.y += deltaTime * 500 * ((X::IsKeyDown(X::Keys::LSHIFT)) ? 10 : 1);
	}

	if (choose)
	{
		CheckMouseInput();
	}
	else
	{
		RenderSearchedNodes();
		RenderPath();
	}

	if(X::IsKeyPressed(X::Keys::C))
	{
		choose = true;
	}

	//Run BFS
	if (X::IsKeyPressed(X::Keys::B) || X::IsKeyPressed(X::Keys::D) || X::IsKeyDown(X::Keys::A) && GoodStartAndEnd())
	{
		choose = false;
		graph.Init(map->GetColumns(), map->GetRows(), map->GetTileSize());
		graph.SetBlocked(blockedNodes);

		if (X::IsKeyDown(X::Keys::B))
		{
			std::function<void(coord)> setCostFunction =
				[](coord next) {
				graph.GetNode(next).g = 0;
				graph.GetNode(next).h = 0;
			};
			graph.FindPath(start, end, setCostFunction);
		}
		else if (X::IsKeyDown(X::Keys::D))//Run Dijkstra
		{
			std::function<void(coord)> setCostFunction =
				[](coord next) {
				graph.GetNode(next).g = CalculateCostFromStart(next) + map->GetTile(next.y, next.x);
				graph.GetNode(next).h = 0;
			};
			graph.FindPath(start, end, setCostFunction);
		}
		else if (X::IsKeyDown(X::Keys::A))//Run A*
		{
			std::function<void(coord)> setCostFunction =
				[](coord next) {
				graph.GetNode(next).g = map->GetTile(next.y, next.x);
				graph.GetNode(next).h = CalculateCostFromEnd(next);
			};
			graph.FindPath(start, end, setCostFunction);
		}
		path = graph.GetPath();
		searchedNodes = graph.GetClosedNodes();
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

void XInitialize()
{
	start.x = 9999;
	start.y = 9999;
	end.x = 9999;
	end.y = 9999;
	CameraManager::StaticInitialize();
	CameraManager::Get()->XInitialize();
	map = new TileMap();
	map->XInitialize();
}

void XTerminate()
{
	X::SafeDelete(map);
}
