#include <XEngine.h>

// http://cgm.cs.mcgill.ca/~godfried/teaching/cg-projects/97/Ian/cutting_ears.html

const float cursorRadius = 8.0f;
const float gridSize = 20.0f;

enum class Mode
{
	None,
	AddVertex,
	RemoveVertex
};

struct Polygon
{
	std::vector<X::Math::Vector2> vertices;
	std::vector<int> indices;
};

Mode mode = Mode::None;
Polygon polygon;
bool snapToGrid = true;

void Triangulate()
{
	const int vertexCount = (int)polygon.vertices.size();
	if (vertexCount < 3)
		return;

	polygon.indices.clear();

	std::vector<int> checklist;
	checklist.reserve(vertexCount);
	for (int i = 0; i < vertexCount; ++i)
	{
		checklist.push_back(i);
	}

	int current = 0;
	while (checklist.size() >= 3)
	{
		const int checkListCount = (int)checklist.size();
		int a = checklist[current];
		int b = checklist[(current + 1) % checkListCount];
		int c = checklist[(current + 2) % checkListCount];
		X::Math::Vector2 ab = polygon.vertices[b] - polygon.vertices[a];
		X::Math::Vector2 bc = polygon.vertices[c] - polygon.vertices[b];

		// Skip if concave
		X::Math::Vector2 perp = X::Math::PerpendicularLH(ab);
		if (X::Math::Dot(perp, bc) < 0.0f)
		{
			++current;
			continue;
		}

		// Skip if triangle is not empty
		bool skip = false;
		for (int i = 0; i < checkListCount - 3; ++i)
		{
			int testIndex = checklist[(i + current + 3) % checkListCount];
			if (X::Math::PointInTriangle(polygon.vertices[testIndex], polygon.vertices[a], polygon.vertices[b], polygon.vertices[c]))
			{
				skip = true;
				break;
			}
		}
		if (skip)
		{
			++current;
			continue;
		}

		// Found ear, add triangle, remove middle vertex and restart
		polygon.indices.push_back(a);
		polygon.indices.push_back(b);
		polygon.indices.push_back(c);
		checklist.erase(checklist.begin() + current + 1);
		current = 0;
	}
}

X::Math::Vector2 SnapVertex(const X::Math::Vector2& pos)
{
	for (const auto& v : polygon.vertices)
	{
		if (X::Math::DistanceSqr(v, pos) <= X::Math::Sqr(cursorRadius))
			return v;
	}
	return pos;
}

void UpdateAddVertex()
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		polygon.indices.clear();

		float mouseX = (float)X::GetMouseScreenX();
		float mouseY = (float)X::GetMouseScreenY();
		if (snapToGrid)
		{
			mouseX = std::floorf((mouseX + gridSize * 0.5f) / gridSize) * gridSize;
			mouseY = std::floorf((mouseY + gridSize * 0.5f) / gridSize) * gridSize;
		}
		X::Math::Vector2 pos(mouseX, mouseY);
		polygon.vertices.push_back(SnapVertex(pos));
	}
}

void UpdateRemoveVertex()
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		polygon.indices.clear();

		float mouseX = (float)X::GetMouseScreenX();
		float mouseY = (float)X::GetMouseScreenY();
		X::Math::Vector2 pos(mouseX, mouseY);
		for (auto iter = polygon.vertices.begin(); iter != polygon.vertices.end(); ++iter)
		{
			if (X::Math::DistanceSqr(*iter, pos) <= X::Math::Sqr(cursorRadius))
			{
				polygon.vertices.erase(iter);
				break;
			}
		}
	}
}

void Save()
{
	if (!polygon.vertices.empty())
	{
		Triangulate();

		FILE* file = nullptr;
		fopen_s(&file, "polygon.txt", "w");
		fprintf_s(file, "Vertices: %d\n", (int)polygon.vertices.size());
		fprintf_s(file, "Indices: %d\n", (int)polygon.indices.size());
		for (const auto& v : polygon.vertices)
		{
			fprintf_s(file, "%f %f\n", v.x, v.y);
		}
		for (const auto& i : polygon.indices)
		{
			fprintf_s(file, "%d\n", i);
		}
		fclose(file);
	}
}

void Load()
{
	polygon.vertices.clear();
	polygon.indices.clear();

	FILE* file = nullptr;
	fopen_s(&file, "polygon.txt", "r");
	if (file == nullptr)
	{
		return;
	}

	int vertices = 0;
	int indices = 0;
	fscanf_s(file, "Vertices: %d\n", &vertices);
	fscanf_s(file, "Indices: %d\n", &indices);
	polygon.vertices.resize(vertices);
	polygon.indices.resize(indices);
	for (int i = 0; i < vertices; ++i)
	{
		X::Math::Vector2& v = polygon.vertices[i];
		fscanf_s(file, "%f %f\n", &v.x, &v.y);
	}
	for (int i = 0; i < indices; ++i)
	{
		fscanf_s(file, "%d\n", &polygon.indices[i]);
	}
	fclose(file);

	Triangulate();
}

void CheckKey()
{
	if (X::IsKeyPressed(X::Keys::ESCAPE))
	{
		mode = Mode::None;
	}
	else if (X::IsKeyPressed(X::Keys::F1))
	{
		mode = Mode::AddVertex;
	}
	else if (X::IsKeyPressed(X::Keys::F2))
	{
		mode = Mode::RemoveVertex;
	}
	else if (X::IsKeyPressed(X::Keys::T))
	{
		Triangulate();
	}
	else if (X::IsKeyPressed(X::Keys::G))
	{
		snapToGrid = !snapToGrid;
	}
	else if (X::IsKeyPressed(X::Keys::S))
	{
		Save();
	}
	else if (X::IsKeyPressed(X::Keys::L))
	{
		Load();
	}
	else if (X::IsKeyPressed(X::Keys::C))
	{
		polygon.vertices.clear();
		polygon.indices.clear();
	}
}

void DrawGrid()
{
	if (snapToGrid)
	{
		float screenWidth = (float)X::GetScreenWidth();
		float screenHeight = (float)X::GetScreenHeight();
		for (float y = 0; y <= screenHeight; y += gridSize)
		{
			for (float x = 0; x <= screenWidth; x += gridSize)
			{
				X::DrawScreenDiamond(x, y, 2.0f, X::Math::Vector4::DarkGray());
			}
		}
	}
}

void DrawPolygon()
{
	const int vertexCount = (int)polygon.vertices.size();
	const int indexCount = (int)polygon.indices.size();
	for (int i = 0; i < indexCount; i += 3)
	{
		const auto& a = polygon.vertices[polygon.indices[i]];
		const auto& b = polygon.vertices[polygon.indices[i + 1]];
		const auto& c = polygon.vertices[polygon.indices[i + 2]];
		X::DrawScreenLine(a, b, X::Math::Vector4::Gray());
		X::DrawScreenLine(b, c, X::Math::Vector4::Gray());
		X::DrawScreenLine(c, a, X::Math::Vector4::Gray());
	}
	for (int i = 0; i < vertexCount - 1; ++i)
	{
		X::DrawScreenLine(polygon.vertices[i], polygon.vertices[i + 1], X::Math::Vector4::Blue());
	}
	if (vertexCount >= 3)
	{
		X::DrawScreenLine(polygon.vertices[0], polygon.vertices[vertexCount - 1], X::Math::Vector4::DarkBlue());
	}
	for (int i = 0; i < vertexCount; ++i)
	{
		const auto& v = polygon.vertices[i];
		X::DrawScreenLine(v.x - 2, v.y - 2, v.x + 2, v.y + 2, X::Math::Vector4::LightBlue());
		X::DrawScreenLine(v.x - 2, v.y + 2, v.x + 2, v.y - 2, X::Math::Vector4::LightBlue());
	}
}

void DrawCursor()
{
	float mouseX = (float)X::GetMouseScreenX();
	float mouseY = (float)X::GetMouseScreenY();

	switch (mode)
	{
	case Mode::None:
		X::DrawScreenCircle(X::Math::Circle(mouseX, mouseY, cursorRadius * 0.5f), X::Math::Vector4::Blue());
		break;
	case Mode::AddVertex:
		X::DrawScreenCircle(X::Math::Circle(mouseX, mouseY, cursorRadius), X::Math::Vector4::Green());
		break;
	case Mode::RemoveVertex:
		X::DrawScreenCircle(X::Math::Circle(mouseX, mouseY, cursorRadius), X::Math::Vector4::Red());
		break;
	}
}

void DrawLegend()
{
	const char* const instruction =
		"Add Polygon Vertices in Clockwise Order!\n"
		"F1  - Add Vertex\n"
		"F2  - Remove Vertex\n"
		"T   - Triangulate\n"
		"G   - Snap to Grid\n"
		"S   - Save\n"
		"L   - Load\n"
		"C   - Clear\n"
		"ESC - Back\n"
		"Q   - Quit";
	X::DrawScreenText(instruction, 10.0f, 10.0f, 16.0f, X::Math::Vector4::White());
}

bool GameLoop(float deltaTime)
{
	CheckKey();

	switch (mode)
	{
	case Mode::AddVertex:
		UpdateAddVertex();
		break;
	case Mode::RemoveVertex:
		UpdateRemoveVertex();
		break;
	}

	DrawGrid();
	DrawPolygon();
	DrawCursor();
	DrawLegend();

	return X::IsKeyPressed(X::Keys::Q);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("Hello Polygon");
	X::Run(GameLoop);
	X::Stop();
	return 0;
}