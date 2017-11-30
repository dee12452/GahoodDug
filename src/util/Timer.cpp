#include "Timer.hpp"

Timer::Timer(int ms) {
    setTargetMs(ms);
    reset();
}

Timer::~Timer() {}

void Timer::reset() {
	start = std::chrono::high_resolution_clock::now();
    finish = std::chrono::high_resolution_clock::now();
}

bool Timer::check() {
    finish = std::chrono::high_resolution_clock::now();
	//elapsedTime is in seconds
	double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
    if(static_cast<int> (elapsedTime * 1000) >= targetMs) {
        reset();
        return true;
    }
    return false;
}

void Timer::setTargetMs(int ms) {
    targetMs = ms;
}

int Timer::getTargetMs() const {
    return targetMs;
}

int Timer::getElapsedMs() {
    finish = std::chrono::high_resolution_clock::now();
	double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
	return static_cast<int> (elapsedTime * 1000);
};
