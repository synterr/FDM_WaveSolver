#include "stdafx.h"
#include "graphics.h"

Graphics::Graphics() : m_window(nullptr), m_logr(nullptr)
{

}

Graphics::Graphics(sf::RenderWindow* window, Log* logr)
{
	m_window = window;
	m_logr = logr;
}

bool Graphics::createWindow(std::string title, sf::Vector2u window_size, int frame_rate)
{
	bool result = true;
	m_logr->Info("Create window...");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	m_window->create(sf::VideoMode(window_size.x, window_size.y), title, sf::Style::Close, settings);
	sf::WindowHandle h_window = m_window->getSystemHandle();

	if (h_window == nullptr) {
		m_logr->Error("Can't create window :(");
		result = false;
	}
	else
	{
		m_window_size = window_size;
		m_window->clear(sf::Color(0, 0, 0, 255));
		m_window->display();
		m_window->setFramerateLimit(frame_rate);
	}

	return result;
}

bool Graphics::loadResources()
{
	bool result = true;
	m_logr->Info("Preparing image buffer and textures...");

	// window image texture and sprite
	m_image_wnd.create(m_window_size.x, m_window_size.y, sf::Color(10, 10, 10, 255));

	if (m_texture_wnd.create(m_window_size.x, m_window_size.y))
	{
		m_texture_wnd.update(m_image_wnd);
		m_sprite_wnd.setTexture(m_texture_wnd);
	}
	else
	{
		result &= 0; m_logr->Error("Failed to prepare window texture");
	}

	// wave image texture and sprite
	m_image_wav.create(m_window_size.x, m_window_size.y, sf::Color(10, 10, 10, 250));

	if (m_texture_wav.create(m_window_size.x, m_window_size.y))
	{
		m_texture_wav.update(m_image_wav);
		m_sprite_wav.setTexture(m_texture_wav);
	}
	else
	{
		result &= 0; m_logr->Error("Failed to prepare wave texture");
	}

	// medium texture and sprite
	m_image_med.create(m_window_size.x, m_window_size.y, sf::Color(10, 10, 10, 100));

	if (m_texture_med.create(m_window_size.x, m_window_size.y))
	{
		m_texture_med.update(m_image_med);
		m_sprite_med.setTexture(m_texture_med);
	}
	else
	{
		result &= 0; m_logr->Error("Failed to prepare medium texture");
	}

	if (!m_font.loadFromFile("segoeui.ttf"))
	{
		result &= 0; m_logr->Error("Fonts not found");
	}

	if (result)
	{
		m_logr->m_stream << "Total images size: " << m_image_wav.getSize().x * m_image_wnd.getSize().y * 3 * 4 / 1000000 << "MB";
		m_logr->Info(m_logr->m_stream.str().c_str());
		m_logr->m_stream << "Total textures size: " << m_texture_wnd.getSize().x * m_texture_med.getSize().y * 3 * 4 / 1000000 << "MB";
		m_logr->Info(m_logr->m_stream.str().c_str());
		m_logr->m_stream << "Font: '" << m_font.getInfo().family << "' loaded.";
		m_logr->Info(m_logr->m_stream.str().c_str());
	}

	return result;
}

void Graphics::updateTexture(TextureType texture_type)
{
	if (texture_type == TextureWindow)
		m_texture_wnd.update(m_image_wnd);

	if (texture_type == TextureWave)
		m_texture_wav.update(m_image_wav);

	if (texture_type == TextureMedium)
		m_texture_med.update(m_image_med);
}

void Graphics::drawText(std::string text, sf::Vector2u pos)
{
	sf::Text sftext;
	sftext.setFont(m_font); 

	sftext.setPosition((float)pos.x, (float)pos.y);
	sftext.setString(text);
	sftext.setCharacterSize(16); // in pixels, not points!
	sftext.setFillColor(sf::Color(200, 200, 200, 120));
	m_window->draw(sftext);
}
