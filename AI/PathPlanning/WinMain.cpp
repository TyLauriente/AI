#include<XEngine.h>
#include"TileMap.h"
#include"AI.h"
#include<iostream>
#include<algorithm>
#include"Dude.h"

using coord = AI::Graph::Coordinate;
const float TILE_SIZE = 50.0f;

void XInitialize();
void XTerminate();

AI::AIWorld world;
Dude* dude = nullptr;

coord start, end;


TileMap* map;
std::vector<AI::Graph::Node> searchedNodes;
std::list<coord> blockedNodes;

X::Math::Vector2 ConvertToPosition(AI::Graph::Coordinate coord)
{
	return { static_cast<float>(coord.x * map->GetTileSize()),
		static_cast<float>(coord.y * map->GetTileSize()) };
}


void CheckMouseInput()
{
	//Check For Start click and End Click
	
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		coord blocked;
		blocked.x = static_cast<uint32_t>((X::GetMouseScreenX()) / TILE_SIZE);
		blocked.y = static_cast<uint32_t>((X::GetMouseScreenY()) / TILE_SIZE);
		if (std::find(blockedNodes.begin(), blockedNodes.end(), blocked) != blockedNodes.end())
		{
			blockedNodes.remove(blocked);
			X::Math::Vector2 pos = ConvertToPosition(blocked);
			X::Math::Vector2 pos1 = pos;
			pos1.x += TILE_SIZE;
			world.RemoveWall({ pos, pos1 });
			pos1.x -= TILE_SIZE;
			pos1.y += TILE_SIZE;
			world.RemoveWall({ pos, pos1 });
			pos1.x += TILE_SIZE;
			pos.y += TILE_SIZE;
			world.RemoveWall({ pos, pos1 });
			pos1.y -= TILE_SIZE;
			pos.x += TILE_SIZE;
			world.RemoveWall({ pos, pos1 });
			map->ChangeMap(static_cast<int>(blocked.y), static_cast<int>(blocked.x), 0);
		}
		else
		{
			blockedNodes.push_back(blocked);
			X::Math::Vector2 pos = ConvertToPosition(blocked);
			X::Math::Vector2 pos1 = pos;
			pos1.x += TILE_SIZE;
			world.AddWall({ pos, pos1 });
			pos1.x -= TILE_SIZE;
			pos1.y += TILE_SIZE;
			world.AddWall({ pos, pos1 });
			pos1.x += TILE_SIZE;
			pos.y += TILE_SIZE;
			world.AddWall({ pos, pos1 });
			pos1.y -= TILE_SIZE;
			pos.x += TILE_SIZE;
			world.AddWall({ pos, pos1 });
			map->ChangeMap(static_cast<int>(blocked.y), static_cast<int>(blocked.x), 3);
		}
	}
	if (X::IsKeyPressed(X::Keys::H))
	{
		coord highCostBlock;
		highCostBlock.x = static_cast<uint32_t>((X::GetMouseScreenX()) / TILE_SIZE);
		highCostBlock.y = static_cast<uint32_t>((X::GetMouseScreenY()) / TILE_SIZE);
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


bool Update(float deltaTime)
{
	static float timer = 0.0f;
	static X::Math::Vector2 target;
	CheckMouseInput();
	start = { static_cast<uint32_t>(dude->GetPosition().x / TILE_SIZE), static_cast<uint32_t>(dude->GetPosition().y / TILE_SIZE) };
	end = { static_cast<uint32_t>(X::GetMouseScreenX() / TILE_SIZE), static_cast<uint32_t>(X::GetMouseScreenY() / TILE_SIZE) };
	world.GetNavGraph().Init(map->GetColumns(), map->GetRows(), map->GetTileSize());
	world.GetNavGraph().SetBlocked(blockedNodes);
	if (timer >= 0.2f)
	{
		target = { static_cast<float>(X::GetMouseScreenX()), static_cast<float>(X::GetMouseScreenY()) };
		timer = 0.0f;
	}
	else
	{
		timer += deltaTime;
	}

	dude->Update(deltaTime, target);
	

	map->Render();
	dude->Render();
	std::string fps = std::to_string(1.0f / deltaTime);
	X::DrawScreenText(fps.c_str(), 0.0f, 0.0f, 24.0f, X::Math::Vector4::Green());

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	dude = new Dude(world);
	X::Start();
	XInitialize();


	X::Run(Update);

	XTerminate();
	X::Stop();
}




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


void XInitialize()
{
	map = new TileMap();
	map->XInitialize();
	dude->Init(
		[](coord next) {
		world.GetNavGraph().GetNode(next).g = map->GetTile(next.y, next.x);
		world.GetNavGraph().GetNode(next).h = CalculateCostFromEnd(next);
	}, map->GetRows(), map->GetColumns(), map->GetTileSize());
}

void XTerminate()
{
	X::SafeDelete(dude);
	X::SafeDelete(map);
}
