#include "FrameTimer.h"
#include "FrameTimer.h"


FrameTimer::FrameTimer()
	:
	last(std::chrono::steady_clock::now())
{
}

float FrameTimer::Mark()
{
	const std::chrono::steady_clock::time_point old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> dur = last - old;
	return dur.count();
}

