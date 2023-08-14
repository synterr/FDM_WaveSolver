#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "log.h"
#include "fps.h"
#include "graphics.h"

#define WIDTH		800		// screen width
#define HEIGHT		600		// screen height
#define FRAME_RATE	100		// frame rate limit

#define EXIT() {exit(); return 0;}

using namespace std;
using namespace sf;

//Global variables
constexpr auto TWO_PI = 3.14159265358979f * 2;

const sf::Vector2u	window_size(WIDTH + 1, HEIGHT + 1);

Graphics graph;
Log logr(Log::LevelInfo);
Fps fps;

sf::RenderWindow window;	// main window
sf::WindowHandle h_window;	// main window handle

sf::Image   image_wnd;		// window image
sf::Texture texture_wnd;	// window texture
sf::Sprite  sprite_wnd;		// window sprite

sf::Image   image_wav;		// wave image
sf::Texture texture_wav;	// wave texture
sf::Sprite  sprite_wav;		// wave sprite

sf::Image   image_med;		// media image
sf::Texture texture_med;	// media texture
sf::Sprite  sprite_med;		// media sprite

sf::Font font;				// font used


//Functions
static bool loadResources();
static bool createWindow();
static void exit();
static void mainLoop();