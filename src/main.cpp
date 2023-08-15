#include "stdafx.h"
#include "main.h"

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
	if (!mem->Allocate(window_size))
		EXIT();
	printf("\n");

	//Prepare graphics
	graph = Graphics(&window, &logr);
	if (!graph.createWindow("FDM Wave Solver", window_size, FRAME_RATE))
		EXIT();
	if (!graph.loadResources())
		EXIT();
	printf("\n");

	//Initialize solver
	solver.Init(window_size.x-1, window_size.y-1, 0.03, 0.08, mem);
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
			}
		}

		graph.updateTexture(Graphics::TextureWindow);
		graph.updateTexture(Graphics::TextureWave);
		graph.updateTexture(Graphics::TextureMedium);

		window.draw(graph.m_sprite_wnd);
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
