#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "log.h"
#include "fps.h"
#include "graphics.h"
#include "memory.h"
#include "solver.h"
#include "state_modifier.h"
#include "colors.h"

#define WIDTH		900		// screen width
#define HEIGHT		600		// screen height
#define FRAME_RATE	200		// frame rate limit

#define EXIT() {exit(); return 0;}

using namespace std;
using namespace sf;

//Global variables
constexpr auto TWO_PI = 3.14159265358979f * 2;

const sf::Vector2u	window_size(WIDTH + 1, HEIGHT + 1);

Graphics graph;
Memory*  mem;

Fps fps;
Log logr(Log::LevelInfo);

sf::RenderWindow window;	// main window

//Functions
static void exit();
static void mainLoop();
