#include "main.h"
#include <windows.h>
#include <vector>
#include <sstream>


int main(int argc, char* argv[])
{
	logr.Info("WaveSolver by SyntErr 2023");

#ifdef NDEBUG
	logr.Warn("Release mode!");
#else
	logr.Warn("Debug mode!");
#endif
	
	logr.Info("Create window... ", false);
	
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	RenderWindow window(VideoMode((unsigned int)window_size.x, (unsigned int)window_size.y), "FDM Wave Solver", Style::Close, settings);
	window.setFramerateLimit(F_RATE);
	window.display();
	
	logr.Info("done!");


	logr.Warn("Exit!");
	Sleep(1000);
	return 0;
}