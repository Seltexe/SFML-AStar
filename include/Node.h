#pragma once
#include "tools.h"

class Node
{
public:
	bool bObstacle = false;			// Is the node an obstruction?
	bool bVisited = false;			// Have we searched this node before?

	sf::Vector2i m_position;
	std::vector<Node*> m_nodeNeighbour;
	std::string m_gCost;
	
	float fGlobalGoal, fLocalGoal;
	float m_Weight = 1.f;

	Node* m_parent;
};

