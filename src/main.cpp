#include "stdafx.h"
#include "main.h"
#include "globals.h"

double scale = 1;


int main(int argc, char* argv[])
{
	bool result = true;

	logr.SetLevel(Log::LevelInfo);
	logr.Info("WaveSolver by SyntErr 2023");
	printf("\n");
#ifdef NDEBUG
	logr.Warn("Release mode!");
#else
	logr.Warn("Debug mode!");
#endif
	printf("\n");

	//Prepare memory
	mem = mem->getInstance(&logr);
	if (!mem->allocate(window_size))
		EXIT();
	printf("\n");

	//Prepare graphics
	graph = Graphics(&window, &logr);
	if (!graph.createWindow("FDM Wave Solver", window_size, FRAME_RATE))
		EXIT();
	if (!graph.loadResources())
		EXIT();
	printf("\n");
	
	graph.updateTexture(Graphics::TextureWindow);
	window.draw(graph.m_sprite_wnd);

	//Initialize solver
	Solver::init(window_size.x-1, window_size.y-1, 0.01, 0.08, mem);
	//Set initial conditions
	Solver::initialConditions(mem);
	//Compute color tables
	Colors::computeColorTables();
	//generate medium texture
	graph.genMediumTexture(mem);

	logr.Info("Simulation started!");
	printf("\n");

	if (window.isOpen())
		mainLoop();

	logr.Info("Simulation stopped!");
	printf("\n");
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
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Comma)
				{
					g_hueshift -= 2;
					if (g_hueshift < 0) g_hueshift += 360;
				}
				if (event.key.code == sf::Keyboard::Period)
				{
					g_hueshift += 2;
					if (g_hueshift >= 360) g_hueshift -= 360;
				}
				break;
			}
			
				
		}
		scale = 1;
		Solver::simStep(mem, &graph, scale);


		//graph.updateTexture(Graphics::TextureWindow);
		graph.updateTexture(Graphics::TextureWave);
		graph.updateTexture(Graphics::TextureMedium);

		//window.draw(graph.m_sprite_wnd);
		window.draw(graph.m_sprite_wav);
		window.draw(graph.m_sprite_med);

		fps.update();
		std::stringstream fpss;
		fpss << "FPS:" << fps.getFPS();
		graph.drawText(fpss.str(), Vector2u(10, 10));

		window.display();
	}

	mem->destroyInstance();
}


static void exit()
{
	logr.Warn("Exiting...");

	Sleep(1000);
}
