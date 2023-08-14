#include "main.h"
#include <windows.h>


int main(int argc, char* argv[])
{
	bool result = true;

	logr.SetLevel(Log::LevelInfo);
	logr.Info("WaveSolver by SyntErr 2023");

#ifdef NDEBUG
	logr.Warn("Release mode!");
#else
	logr.Warn("Debug mode!");
#endif
	
	if (!createWindow())
		EXIT();

	if (!loadResources())
		EXIT();

	graph = Graphics(&window, &font);

	logr.Info("Simulation started!");
	if(window.isOpen())
		mainLoop();
	logr.Info("Simulation stopped!");

	window.display();

	EXIT();
}

void mainLoop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		
		texture_wnd.update(image_wnd);
		texture_wav.update(image_wav);
		texture_med.update(image_med);

		window.draw(sprite_wnd);
		window.draw(sprite_wav);
		window.draw(sprite_med);

		fps.update();
		std::stringstream fpss;
		fpss << "FPS:" << fps.getFPS();
		graph.drawText(fpss.str(), Vector2u(10, 10));

		window.display();
	}
}

static bool createWindow()
{
	bool result = true;
	logr.Info("Create window...");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(window_size.x, window_size.y), "FDM Wave Solver", sf::Style::Close, settings);
	h_window = window.getSystemHandle();

	if (h_window == nullptr) {
		logr.Error("Can't create window :(");
		result = false;
	}
	else
	{
		window.clear(sf::Color(0, 0, 0, 255));
		window.display();
		window.setFramerateLimit(FRAME_RATE);
	}

	return result;
}

static bool loadResources()
{
	bool result = true;
	logr.Info("Preparing image buffer and textures...");
	
	// window image texture and sprite
	image_wnd.create(WIDTH + 1, HEIGHT + 1, sf::Color(10, 10, 10, 255));

	if (texture_wnd.create(WIDTH + 1, HEIGHT + 1))
	{
		texture_wnd.update(image_wnd);
		sprite_wnd.setTexture(texture_wnd);
	}
	else
	{
		result &= 0; logr.Error("Failed to prepare window texture");
	}

	// wave image texture and sprite
	image_wav.create(WIDTH + 1, HEIGHT + 1, sf::Color(10, 10, 10, 100));

	if (texture_wav.create(WIDTH + 1, HEIGHT + 1))
	{
		texture_wav.update(image_wav);
		sprite_wav.setTexture(texture_wav);
	}
	else
	{
		result &= 0; logr.Error("Failed to prepare wave texture");
	}

	// medium texture and sprite
	image_med.create(WIDTH + 1, HEIGHT + 1, sf::Color(10, 10, 10, 100));

	if (texture_med.create(WIDTH + 1, HEIGHT + 1))
	{
		texture_med.update(image_med);
		sprite_med.setTexture(texture_med);
	}
	else
	{
		result &= 0; logr.Error("Failed to prepare medium texture");
	}

	if (!font.loadFromFile("segoeui.ttf"))
	{
		result &= 0; logr.Error("Fonts not found");
	}

	if (result)
	{
		logr_stream << "Total images size: " << image_wav.getSize().x * image_wnd.getSize().y * 3 * 4 / 1000000 << "MB";
		logr.Info(logr_stream.str().c_str()); logr_stream = std::stringstream();
		logr_stream << "Total textures size: " << texture_wnd.getSize().x * texture_med.getSize().y * 3 * 4 / 1000000 << "MB";
		logr.Info(logr_stream.str().c_str()); logr_stream = std::stringstream();
		logr_stream << "Font: '" << font.getInfo().family << "' loaded.";
		logr.Info(logr_stream.str().c_str()); logr_stream = std::stringstream();
	}

	return result;
}

static void exit()
{
	logr.Warn("Exiting...");
	
	Sleep(1000);
}
