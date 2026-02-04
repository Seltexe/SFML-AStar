#include "GameManager.h"
#include "imgui-SFML.h"
#include "imgui.h"

GameManager::GameManager()
{
	initTools();
	m_game.Initialize();
}

void GameManager::updateGame()
{
	restartClock();
	m_window.update();
	m_game.update(m_window);

}

void GameManager::displayGame()
{
	m_game.display(m_window);
	m_window.display();
}

void GameManager::loop()
{
	while (m_window.isOpen()) {
		updateGame();
		m_window.clear();
		displayGame();
	}
	ImGui::SFML::Shutdown();
}