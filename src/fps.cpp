#include "fps.h"
#include <sstream>

Fps::Fps() : mFrame(0), mFps(0)
{

}

const unsigned int Fps::getFPS()
{
	return mFps;
}

void Fps::update()
{
	if (mClock.getElapsedTime().asSeconds() >= 1.f)
	{
		mFps = mFrame;
		mFrame = 0;
		mClock.restart();
	}

	++mFrame;
}
