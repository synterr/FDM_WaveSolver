#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Graphics
{
private:
	sf::RenderWindow* m_window;
	sf::Font* m_font;

public:
	Graphics();
	Graphics(sf::RenderWindow* window, sf::Font* font);
	void drawText(std::string text, sf::Vector2u pos);
};

