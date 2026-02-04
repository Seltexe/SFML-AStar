#pragma once
#include "tools.h"
#include "imgui-SFML.h"
#include "imgui.h"

class Window
{
public:
	Window();
	void update();
	void display();
	void clear();
	void draw(sf::Drawable const& _toDraw);
	void draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size,
		sf::Color const& _color = sf::Color::White, float const& _angle = 0.f, sf::Texture const* _texture = nullptr);
	void draw(std::string _textContent, sf::Vector2f _pos);
	bool isOpen();
	sf::RectangleShape m_rectangleGame;
	sf::RenderWindow* getRenderWindow() { return &m_window; }
private:
	void centerText();
	sf::RenderWindow m_window;
	sf::RenderTexture m_renderTexture;
	sf::RectangleShape m_rectangleShape;
	sf::Text m_text;
	sf::Event m_event;
	bool m_fullScreen;
	float m_timerButton;
	sf::Vector2f m_ratio;
	sf::Font m_font;
};