#ifndef INCLUDED_AI_GRAPH_H
#define INCLUDED_AI_GRAPH_H

#include<functional>

namespace AI
{

class Graph
{
public:
	struct Coordinate
	{
		Coordinate(uint32_t iX, uint32_t iY) { x = iX; y = iY; }
		Coordinate() = default;
		uint32_t x{ 0 }, y{ 0 };
		//Coordinate(const Coordinate &c2) { x = c2.x; y = c2.y; }
		bool operator==(const Coordinate& other) const
		{
			return x == other.x && y == other.y;
		}
	};
	struct Node
	{
		Coordinate coordinate;
		Coordinate parent;
		float g{ 0.0f }, h{ 0.0f };
		bool opened{ false };
		bool closed{ false };
		bool blocked{ false };
		float GetCost() { return g + h; }
	};

	Graph();
	~Graph();

	void Init(uint32_t columns, uint32_t rows, float unitSize);
	void Clear();

	Node& GetNode(Coordinate coord);

	bool FindPath(const Coordinate& start, const Coordinate& end,
		const std::function<void(Graph::Coordinate, Graph::Coordinate)> GetBestNode);

	std::vector<Coordinate> GetPath();

	std::vector<Node> GetClosedNodes();

	uint32_t GetColumns() const { return m_columns; }
	uint32_t GetRows() const { return m_rows; }

	void SetBlocked(std::list<Coordinate> blockedNodes);

	const float& UnitSize() const { return m_unitSize; }

private:
	void Reset();
	std::vector<Coordinate> GetSurroundingNodes(Coordinate current) const;
	bool NodeIsReal(Coordinate coordinate);
	Coordinate GetBestNode();
	float CalculateRealCost(Coordinate node);

	std::unique_ptr<Node[]> m_nodes;
	uint32_t m_columns;
	uint32_t m_rows;
	std::list<Coordinate> m_closedList;
	std::list<Coordinate> m_openList;
	Coordinate m_start;
	Coordinate m_end;
	float m_unitSize;
};

} // namespace AI

#endif