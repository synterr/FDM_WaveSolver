#include "main.h"
#include <windows.h>
#include <vector>
#include <sstream>


int main(int argc, char* argv[])
{
	bool result = true;

	logr.Info("WaveSolver by SyntErr 2023");

#ifdef NDEBUG
	logr.Warn("Release mode!");
#else
	logr.Warn("Debug mode!");
#endif
	
	logr.Info("Create window... ", false);

	ContextSettings settings;
	settings.antialiasingLevel = 4;

	RenderWindow window(VideoMode(window_size.x, window_size.y), "FDM Wave Solver", Style::Close, settings);
	h_window = window.getSystemHandle();

	if (h_window == nullptr) {
		logr.Error("Can't create window :(");
		EXIT();
	}

	window.clear(Color(0, 0, 0, 255));
	window.display();
	window.setFramerateLimit(F_RATE);
	
	logr.Info("done!");

	if (!PrepareTextures())
		EXIT();
	
	texture_wnd.update(image_buf);
	texture_wav.update(image_buf);
	texture_med.update(image_buf);
	
	window.draw(sprite_wnd);
	window.draw(sprite_wav);
	window.draw(sprite_med);

	window.display();

	EXIT();
}

static bool PrepareTextures()
{
	bool result = true;
	logr.Info("Preparing image buffer and textures...", false);
	
	// main window image buffer
	image_buf.create(W_WIDTH + 1, W_HEIGHT + 1, Color(0, 0, 0));

	// window texture and sprite
	if (result &= texture_wnd.create(W_WIDTH + 1, W_HEIGHT + 1))
	{
		texture_wnd.update(image_buf);
		sprite_wnd.setTexture(texture_wnd);
	}
	else
		logr.Error("Failed to prepare window texture");

	// wave texture and sprite
	if (result &= texture_wav.create(W_WIDTH + 1, W_HEIGHT + 1))
	{
		texture_wav.update(image_buf);
		sprite_wav.setTexture(texture_wav);
	}
	else
		logr.Error("Failed to prepare wave texture");

	// medium texture and sprite
	if (result &= texture_med.create(W_WIDTH + 1, W_HEIGHT + 1))
	{
		texture_med.update(image_buf);
		sprite_med.setTexture(texture_med);
	}
	else
		logr.Error("Failed to prepare medium texture");


	if (result)
		logr.Info("done!");

	return result;
}

static void Exit()
{
	logr.Warn("Exiting...", false);
	
	Sleep(1000);
}
