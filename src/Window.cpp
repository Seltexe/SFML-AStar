#include "Window.h"

Window::Window()
{
	sf::VideoMode tmpVidMode = sf::VideoMode::getDesktopMode();
	m_window.create(tmpVidMode, "Astar algorithm", sf::Style::Default);
	m_renderTexture.create((float)tmpVidMode.width, (float)tmpVidMode.height);
	m_rectangleShape.setSize(sf::Vector2f((float)tmpVidMode.width, (float)tmpVidMode.height));
	m_rectangleShape.setPosition(sf::Vector2f(0.f, 0.f));
	m_rectangleShape.setFillColor(sf::Color::White);
	m_fullScreen = false;
	m_timerButton = 0.f;
	m_ratio = sf::Vector2f(1920.f / (float)tmpVidMode.width, 1080.f / (float)tmpVidMode.height);
	m_font.loadFromFile("..\\Ressources\\Font\\Nexa-Heavy.ttf");
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(10);
	//m_text.setOutlineColor(sf::Color::Black);
	//m_text.setOutlineThickness(1.f);
	m_text.setFont(m_font);

	ImGui::SFML::Init(m_window);
}

void Window::update()
{
	m_timerButton += getDeltaTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11) && m_timerButton >= 0.2f) {
		if (m_fullScreen)
			m_window.create(sf::VideoMode(1920, 1080), "Astar algorithm", sf::Style::Default);
		else
			m_window.create(sf::VideoMode(1920, 1080), "Astar algorithm", sf::Style::Fullscreen);
		m_fullScreen = !m_fullScreen;
		m_timerButton = 0.f;
	}
	ImGui::SFML::Update(m_window, getRestartClock());

	while (m_window.pollEvent(m_event))
	{
		ImGui::SFML::ProcessEvent(m_window, m_event);
		if (m_event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Window::display()
{
	m_renderTexture.display();

	m_rectangleShape.setTexture(&(m_renderTexture.getTexture()));

	m_window.draw(m_rectangleShape);
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void Window::clear()
{
	m_renderTexture.clear();
	m_window.clear();
}

void Window::draw(sf::Drawable const& _toDraw)
{
	m_renderTexture.draw(_toDraw);
}

void Window::draw(sf::Vector2f const& _pos, sf::Vector2f const& _origin, sf::Vector2f const& _size,
	sf::Color const& _color, float const& _angle, sf::Texture const* _texture)
{
	m_rectangleGame.setFillColor(_color);
	m_rectangleGame.setPosition(_pos);
	m_rectangleGame.setOrigin(_origin);
	m_rectangleGame.setSize(_size);
	m_rectangleGame.setRotation(_angle);
	m_rectangleGame.setTexture(_texture);
	m_renderTexture.draw(m_rectangleGame);
}

void Window::draw(std::string _textContent, sf::Vector2f _pos)
{
	m_text.setString(_textContent);
	m_text.setPosition(_pos);
	m_renderTexture.draw(m_text);
}

bool Window::isOpen()
{
	return m_window.isOpen();
}

void Window::centerText()
{
	sf::FloatRect bounds = m_text.getGlobalBounds();
	m_text.setOrigin(sf::Vector2f(bounds.getSize().x / 2.f, bounds.getSize().y / 2.f));
}


