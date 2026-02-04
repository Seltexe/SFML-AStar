//
// Got the algorithm on github for A*
// https://github.com/OneLoneCoder/Javidx9/blob/master/ConsoleGameEngine/SmallerProjects/OneLoneCoder_PathFinding_AStar.cpp
//
#pragma once
#include "tools.h"
#include "Node.h"
#include "Window.h"

class Astar
{
private:
	std::vector<Node*> path;
public:
	std::vector<Node*> getPath() {
		return path;
	}

	void ResetGraph(Node*& nodes, sf::Vector2i _mapSize) {
		for (int x = 0; x < _mapSize.x; x++) {
			for (int y = 0; y < _mapSize.y; y++) {
				nodes[y * _mapSize.x + x].bVisited = false;
				nodes[y * _mapSize.x + x].fGlobalGoal = INFINITY;
				nodes[y * _mapSize.x + x].fLocalGoal = INFINITY;
				nodes[y * _mapSize.x + x].m_parent = nullptr;
			}
		}
	}

	auto distance(Node* a, Node* b) {
		return sqrtf((a->m_position.x - b->m_position.x) * (a->m_position.x - b->m_position.x) + (a->m_position.y - b->m_position.y) * (a->m_position.y - b->m_position.y));
	}


	auto heuristic(Node* a, Node* b) { return distance(a, b); }

	void resetNeighbour(Node*& nodes, sf::Vector2i _mapSize, bool isDiagAllowed) {
		for (int x = 0; x < _mapSize.x; x++) {
			for (int y = 0; y < _mapSize.y; y++) {
				nodes[y * _mapSize.x + x].m_nodeNeighbour.clear();

				if (y > 0)
					nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y - 1) * _mapSize.x + (x + 0)]);
				if (y < _mapSize.y - 1)
					nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y + 1) * _mapSize.x + (x + 0)]);
				if (x > 0)
					nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y + 0) * _mapSize.x + (x - 1)]);
				if (x < _mapSize.x - 1)
					nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y + 0) * _mapSize.x + (x + 1)]);

				if (isDiagAllowed) {
					if (y > 0 && x > 0)
						nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y - 1) * _mapSize.x + (x - 1)]);
					if (y < _mapSize.y - 1 && x > 0)
						nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y + 1) * _mapSize.x + (x - 1)]);
					if (y > 0 && x < _mapSize.x - 1)
						nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y - 1) * _mapSize.x + (x + 1)]);
					if (y < _mapSize.y - 1 && x < _mapSize.x - 1)
						nodes[y * _mapSize.x + x].m_nodeNeighbour.push_back(&nodes[(y + 1) * _mapSize.x + (x + 1)]);
				}
			}
		}
	}

	bool solve_Astar(Node*& _nodeStart, Node*& _nodeEnd)
	{
		// Setup starting conditions
		Node* currentNode = _nodeStart;
		_nodeStart->fLocalGoal = 0.0f;
		_nodeStart->fGlobalGoal = heuristic(_nodeStart, _nodeEnd);

		// Add start node to not tested list, this will ensure it get tested
		// As the algorithm progresses, newly discovered nodes get added to this
		// list, and will themselves be tested later.
		std::list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(_nodeStart);


		while (!listNotTestedNodes.empty() && currentNode != _nodeEnd)
		{
			// Sort untested nodes by global goal, so lowest is first
			listNotTestedNodes.sort([](const Node* lhs, const Node* rhs) {return lhs->fGlobalGoal < rhs->fGlobalGoal; });

			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

			if (listNotTestedNodes.empty())
				break;

			currentNode = listNotTestedNodes.front();
			currentNode->bVisited = true;

			// Check each of this node's neighbour
			for (auto nodeNeighbour : currentNode->m_nodeNeighbour)
			{
				if (!nodeNeighbour->bVisited /*&& nodeNeighbour->bObstacle == 0*/)
					listNotTestedNodes.push_back(nodeNeighbour);

				// Calculate the neighbours potential lowest parent distance
				float fPossiblyLowerGoal = currentNode->fLocalGoal + distance(currentNode, nodeNeighbour) * nodeNeighbour->m_Weight;
				currentNode->m_gCost = std::to_string(static_cast<int>(fPossiblyLowerGoal));

				// If choosing to path through this node is a lower distance than what 
				// the neighbour currently has set, update the neighbour to use this node
				// as the path source, and set its distance scores as necessary
				if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
				{
					nodeNeighbour->m_parent = currentNode;
					nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

					// The best path length to the neighbour being tested has changed, so
					// update the neighbour's score. The heuristic is used to globally bias
					// the path algorithm, so it knows if its getting better or worse. At some
					// point the algo will realise this path is worse and abandon it, and then go
					// and search along the next best path.
					nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, _nodeEnd);
				}
			}
		}


		path.clear();
		if (_nodeEnd->m_parent != nullptr) {
			Node* p = _nodeEnd;
			while (p != nullptr) {
				path.push_back(p);
				p = p->m_parent;
			}
			std::reverse(path.begin(), path.end());
		}
		return true;
	}

	void drawAllPath(Window& _window, Node* nodes, sf::Vector2i mapSize, float nodeSize)
	{
		sf::VertexArray path(sf::Lines);

		for (int x = 0; x < mapSize.x; x++) {
			for (int y = 0; y < mapSize.y; y++) {
				Node& currentNode = nodes[y * mapSize.x + x];

				for (auto n : currentNode.m_nodeNeighbour) {
					if (n != nullptr) {
						path.append(sf::Vertex(sf::Vector2f(currentNode.m_position.x * nodeSize + nodeSize / 2,
							currentNode.m_position.y * nodeSize + nodeSize / 2),
							sf::Color(92, 0, 255, 100)));

						path.append(sf::Vertex(sf::Vector2f(n->m_position.x * nodeSize + nodeSize / 2,
							n->m_position.y * nodeSize + nodeSize / 2),
							sf::Color(92, 0, 255, 100)));
					}
				}
			}
		}

		_window.draw(path);
	}


	void drawPath(Window& _window, Node* nodeEnd, float nodeSize)
	{
		if (nodeEnd == nullptr)
			return;

		sf::VertexArray path(sf::LinesStrip);

		Node* current = nodeEnd;

		while (current != nullptr)
		{
			path.append(sf::Vertex(sf::Vector2f(current->m_position.x * nodeSize + nodeSize / 2,
				current->m_position.y * nodeSize + nodeSize / 2),
				sf::Color::Yellow));

			current = current->m_parent;
		}

		_window.draw(path);
	}
};

