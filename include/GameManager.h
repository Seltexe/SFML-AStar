#pragma once
#include "Window.h"
#include "Game.h"

class GameManager
{
public:
	GameManager();
	void loop();

private:
	void updateGame();
	void displayGame();
	Game m_game;
	Window m_window;
};