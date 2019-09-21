#include"Precompiled.h"
#include"Graph.h"

using namespace AI;

Graph::Graph()
	: m_nodes{ nullptr }
	, m_columns { 0 }
	, m_rows{ 0 }
{

}

Graph::~Graph()
= default;

void Graph::Init(uint32_t columns, uint32_t rows, float unitSize)
{
	m_unitSize = unitSize;
	if (!m_nodes)
	{
		m_nodes = std::make_unique<Node[]>(columns * rows);
		m_columns = columns;
		m_rows = rows;
		for (uint32_t y = 0; y < m_rows; ++y)
		{
			for (uint32_t x = 0; x < m_columns; ++x)
			{
				GetNode({ x, y }).coordinate = { x, y };
			}
		}
	}
}

void Graph::Clear()
{
	m_nodes.reset();
	m_columns = 0;
	m_rows = 0;
}

Graph::Node& Graph::GetNode(Coordinate coord)
{
	if(coord.x < 0 && coord.x >= m_rows && coord.y < 0 && coord.y >= m_columns)
	{
		throw;
	}
	return m_nodes[coord.x + (coord.y * m_columns)];
}

bool Graph::FindPath(const Graph::Coordinate& start, const Graph::Coordinate& end,
	const std::function<void(Graph::Coordinate, Graph::Coordinate)> SetCostFunction)
{
	m_start = start;
	m_end = end;
	Reset();
	m_openList.push_back(start);//Add Start Node to open List
	GetNode(start).opened = true;
	GetNode(start).parent = start;
	bool found = false;


	while (!found && !m_openList.empty())//Continue Looping While the path has not 
	{                                   //been found and the open list isn't empty

		const Coordinate current = GetBestNode();//Set current node to the front of the open list
		m_openList.remove(current);
		if (current == end)
		{
			found = true;
		}
		else
		{
			auto surroundingNodes = GetSurroundingNodes(current);
			for (const auto node : surroundingNodes)//Check each node arround the Current
			{
				if (NodeIsReal(node))
				{
					if (!(GetNode(node).opened) && !(GetNode(node).blocked))// If the node is not open and it is not blocked
					{                                                     //  then add node to open list, set node opened to
						m_openList.push_back(node);                      //   true and set the nodes parent to current
						GetNode(node).opened = true;
						GetNode(node).parent = current;
						SetCostFunction(node, end);
					}
				}
			}
		}
		m_closedList.push_back(current);//Add the current to the closed list
		GetNode(current).closed = true;
	}

	return found;
}



std::vector<Graph::Coordinate> Graph::GetPath()
{
	auto tempNode = m_closedList.back();//set temp to the end position 
	const auto startNode = m_closedList.front();//set start to start
	std::vector<Graph::Coordinate> path;
	path.push_back(tempNode);//add end node

	while(!(tempNode == startNode))//while temp does not equal start
	{
		tempNode = GetNode(tempNode).parent;//take node from parent and place it in the path
		path.push_back(tempNode);
	}

	std::reverse(path.begin(), path.end());//reverse order so it can be followed
	return path;
}

std::vector<Graph::Node> Graph::GetClosedNodes()
{
	std::vector<Graph::Node> nodes;
	for(const auto& node : m_closedList)
	{
		auto addMe = GetNode(node);
		nodes.push_back(addMe);
	}
	return nodes;
}

void Graph::Reset()
{
	for (uint32_t index = 0; index < m_columns * m_rows; ++index)
	{
		m_nodes[index].opened = false;
		m_nodes[index].closed = false;
		m_nodes[index].parent.x = 0;
		m_nodes[index].parent.y = 0;
	}
	m_openList.clear();
	m_closedList.clear();
}

void Graph::SetBlocked(std::list<Coordinate> blockedNodes)
{
	for (auto node : blockedNodes)
	{
		GetNode(node).blocked = true;
	}
}


std::vector<Graph::Coordinate> Graph::GetSurroundingNodes(Coordinate current) const//returns all surrounding nodes
{
	std::vector<Coordinate> surroundingNodes;
	Coordinate tempNode;
	if (current.x > 0)
	{
		tempNode = current;
		tempNode.x--;
		surroundingNodes.push_back(tempNode);
	}
	if (current.x + 1 < m_rows)
	{
		tempNode = current;
		tempNode.x++;
		surroundingNodes.push_back(tempNode);
	}
	if (current.y > 0)
	{
		tempNode = current;
		tempNode.y--;
		surroundingNodes.push_back(tempNode);
	}
	if (current.y + 1 < m_rows)
	{
		tempNode = current;
		tempNode.y++;
		surroundingNodes.push_back(tempNode);
	}
	if (current.x + 1 < m_rows && current.y + 1 < m_columns)
	{
		tempNode = current;
		tempNode.y++;
		tempNode.x++;
		surroundingNodes.push_back(tempNode);
	}
	if (current.x + 1 < m_rows && current.y - 1 >= 0)
	{
		tempNode = current;
		tempNode.x++;
		tempNode.y--;
		surroundingNodes.push_back(tempNode);
	}
	if (current.x - 1 >= 0 && current.y + 1 < m_columns)
	{
		tempNode = current;
		tempNode.x--;
		tempNode.y++;
		surroundingNodes.push_back(tempNode);
	}
	if (current.x - 1 >= 0 && current.y - 1 >= 0)
	{
		tempNode = current;
		tempNode.x--;
		tempNode.y--;
		surroundingNodes.push_back(tempNode);
	}
	return surroundingNodes;
}

bool Graph::NodeIsReal(Graph::Coordinate coordinate)
{
	return (coordinate.x >= 0 && coordinate.x < m_rows &&
		coordinate.y >= 0 && coordinate.y < m_columns);
}

Graph::Coordinate Graph::GetBestNode()
{
	Graph::Coordinate bestNode = m_openList.front();
	float bestCost = GetNode(bestNode).GetCost();
	for(auto node : m_openList)
	{
		if(GetNode(node).GetCost() < bestCost && !GetNode(node).blocked)
		{
			bestNode = node;
			bestCost = GetNode(node).GetCost();
		}
	}
	return bestNode;
}

float Graph::CalculateRealCost(Graph::Coordinate node)
{
	float cost = 0;
	float h = GetNode(node).h;

	while(!(node == m_start))
	{
		cost += GetNode(node).g;
		node = GetNode(node).parent;
	}
	return cost + h;
}