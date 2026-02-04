#pragma once
#include "Window.h"
#include "Node.h"
#include "Astar.h"
#include "Player.h"

class Game
{
private:
	Node* nodes = nullptr;

	sf::Vector2i m_mapSize;

	Node* nodeStart = nullptr;
	Node* nodeEnd = nullptr;

	Astar astar;
	Player player;

	bool isDiagAllowed;

	sf::RectangleShape m_nodeShape;
	sf::RectangleShape m_nodeShapePath;
public:
	Game();
	~Game();
	void Initialize();
	void update(Window& _w);
	void displayImGui();
	void display(Window& _window);

};