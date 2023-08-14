#pragma once
#include <SFML/Graphics.hpp>
#include "log.h"

class Fps
{
public:
	Fps();
	const unsigned int getFPS();

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update();
};