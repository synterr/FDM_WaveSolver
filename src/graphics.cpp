#include "graphics.h"

Graphics::Graphics() : m_window(nullptr), m_font(nullptr)
{

}

Graphics::Graphics(sf::RenderWindow* window, sf::Font* font)
{
	m_window = window;
	m_font = font;
}

void Graphics::drawText(std::string text, sf::Vector2u pos)
{
	sf::Text sftext;
	sftext.setFont(*m_font); 

	sftext.setPosition(pos.x, pos.y);
	sftext.setString(text);
	sftext.setCharacterSize(16); // in pixels, not points!
	sftext.setFillColor(sf::Color(200, 200, 200, 120));
	m_window->draw(sftext);
}
