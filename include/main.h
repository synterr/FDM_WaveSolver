#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "log.h"

#define W_WIDTH		800		// screen width
#define W_HEIGHT	600		// screen height
#define F_RATE		100		// framerate limit

#define EXIT() {Exit(); return 0;}

using namespace sf;
using namespace std;

//Global variables
constexpr auto TWO_PI = 3.14159265358979f * 2;

const Vector2u	window_size(W_WIDTH + 1, W_HEIGHT + 1);

char logr_buff[80] = "Loger buffer Init";

Log logr(Log::LevelInfo);

WindowHandle h_window;	// main window handle
Image image_buf;		// main window image buffer

Texture texture_wnd;	// window texture
Sprite  sprite_wnd;		// window sprite

Texture texture_wav;	// wave texture
Sprite  sprite_wav;		// wave sprite

Texture texture_med;	// media texture
Sprite  sprite_med;		// media sprite

//Functions
static bool PrepareTextures();
static void Exit();