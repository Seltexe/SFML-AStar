#include "Game.h"

Game::Game() : m_mapSize(60, 33), player(nodeStart)
{
	
}

Game::~Game()
{
}

void Game::Initialize()
{
	nodes = new Node[m_mapSize.x * m_mapSize.y];
	isDiagAllowed = true;

	for (int x = 0; x < m_mapSize.x; x++) {
		for (int y = 0; y < m_mapSize.y; y++) {
			nodes[y * m_mapSize.x + x].m_position.x = x;
			nodes[y * m_mapSize.x + x].m_position.y = y;
			nodes[y * m_mapSize.x + x].bObstacle = false;
			nodes[y * m_mapSize.x + x].m_parent = nullptr;
			nodes[y * m_mapSize.x + x].bVisited = false; 
			nodes[y * m_mapSize.x + x].m_gCost = "0";
			
		}
	}

	// Node connections
	astar.resetNeighbour(nodes, m_mapSize, isDiagAllowed);

	nodeStart = &nodes[(m_mapSize.y / 2) * m_mapSize.x + 1];
	nodeEnd = &nodes[(m_mapSize.y / 2) * m_mapSize.x + m_mapSize.x - 2];

	m_nodeShape.setSize(sf::Vector2f(32.f, 32.f));
	m_nodeShape.setFillColor(sf::Color::Blue);
	m_nodeShape.setOutlineThickness(1.f);
	m_nodeShape.setOutlineColor(sf::Color::Black);

	astar.ResetGraph(nodes, m_mapSize);
	astar.solve_Astar(nodeStart, nodeEnd);
	player.setPath(astar.getPath());
}

void Game::update(Window& _w)
{
	sf::Vector2i m_mousePos = sf::Mouse::getPosition(*_w.getRenderWindow());

	sf::Vector2i m_SelectedNode = m_mousePos / 32;

	static float m_timerMouse = 0.f;
	m_timerMouse += getDeltaTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_timerMouse > 0.2f) {

		if (m_SelectedNode.x >= 0 && m_SelectedNode.x < m_mapSize.x) {
			if (m_SelectedNode.y >= 0 && m_SelectedNode.y < m_mapSize.y) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					nodeStart = &nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x];
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					nodeEnd = &nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x];
				}
				else {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].m_Weight += 1.0f;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].m_Weight = std::max(1.0f, nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].m_Weight - 1.0f);  // Diminue le poids (minimum 1)
					}

					nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].bObstacle = nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].m_Weight > 5.0f; // Seuil de poids
				}
					//nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].bObstacle = !nodes[m_SelectedNode.y * m_mapSize.x + m_SelectedNode.x].bObstacle;

				astar.resetNeighbour(nodes, m_mapSize, isDiagAllowed);
				astar.ResetGraph(nodes, m_mapSize);
				astar.solve_Astar(nodeStart, nodeEnd);
				player.setPath(astar.getPath());
			}
		}

		m_timerMouse = 0.f;
	}

	static float m_timerKeyboard = 0.f;
	m_timerKeyboard += getDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_timerKeyboard > 0.2f) {
		isDiagAllowed = !isDiagAllowed;
		astar.resetNeighbour(nodes, m_mapSize, isDiagAllowed);
		astar.ResetGraph(nodes, m_mapSize);
		astar.solve_Astar(nodeStart, nodeEnd);
		player.setPath(astar.getPath());

		m_timerKeyboard = 0.f;
	}

	player.update();
}

void Game::displayImGui()
{
	ImGui::Begin("Controls");

	ImGui::Text("Left Click + Up : Add weight");
	ImGui::Text("Left Click + Down : Remove weight");
	ImGui::Text("Left Click + Left shift : Place start");
	ImGui::Text("Left Click + Left control : Place end");
	ImGui::Text("A: Toggle diagonals");

	ImGui::End();
}

void Game::display(Window& _window)
{
	for (int x = 0; x < m_mapSize.x; x++) {
		for (int y = 0; y < m_mapSize.y; y++) {
			m_nodeShape.setPosition(sf::Vector2f(x * 32, y * 32));
			m_nodeShape.setFillColor(sf::Color::White);

			int intensity = std::min(255, static_cast<int>(nodes[y * m_mapSize.x + x].m_Weight * 20));
			m_nodeShape.setFillColor(sf::Color(intensity, 0, 0));

			if (nodes[y * m_mapSize.x + x].bVisited) {
				m_nodeShape.setFillColor(sf::Color(100, 100, 100));
			}
				
			if (&nodes[y * m_mapSize.x + x] == nodeStart) {
				m_nodeShape.setFillColor(sf::Color::Green);
			}

			if (&nodes[y * m_mapSize.x + x] == nodeEnd) {
				m_nodeShape.setFillColor(sf::Color::Magenta);
			}

			_window.draw(m_nodeShape);
			_window.draw(nodes[y * m_mapSize.x + x].m_gCost, static_cast<sf::Vector2f>(nodes[y * m_mapSize.x + x].m_position * 32));
		}
	}

	astar.drawAllPath(_window, nodes, m_mapSize, 32.f);
	astar.drawPath(_window, nodeEnd, 32.f);
	//player.drawPath(_window);
	player.draw(_window);

	displayImGui();
}
