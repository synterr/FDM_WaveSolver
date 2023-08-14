#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "log.h"

class Graphics
{
public:

	enum TextureType
	{
		TextureNone = 0, TextureWindow, TextureWave, TextureMedium
	};

	sf::Image   m_image_wnd;		// window image
	sf::Sprite  m_sprite_wnd;		// window sprite

	sf::Image   m_image_wav;		// wave image
	sf::Sprite  m_sprite_wav;		// wave sprite

	sf::Image   m_image_med;		// media image
	sf::Sprite  m_sprite_med;		// media sprite

	//sf::Font font;				// font used
private:
	sf::Texture m_texture_wnd;	// window texture
	sf::Texture m_texture_wav;	// wave texture
	sf::Texture m_texture_med;	// media texture

	sf::RenderWindow* m_window;
	sf::Vector2u m_window_size;
	sf::Font m_font;
	Log* m_logr;

public:
	Graphics();
	Graphics(sf::RenderWindow* window, Log* logr);
	bool createWindow(std::string title, sf::Vector2u window_size, int frame_rate);
	bool loadResources();
	void updateTexture(TextureType texture_type);
	void drawText(std::string text, sf::Vector2u pos);
};

