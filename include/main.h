#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "log.h"

#define W_WIDTH		800		// screen width
#define W_HEIGHT	600		// screen height
#define F_RATE		100		// framerate limit

using namespace sf;
using namespace std;

constexpr auto TWO_PI = 3.14159265358979f * 2;

const Vector2f	window_size(W_WIDTH + 1, W_HEIGHT + 1);

char logr_buff[80] = "Loger buffer Init";

Log logr(Log::LevelInfo);