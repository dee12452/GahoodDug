#include "../headers/Timer.hpp"

Timer::Timer(unsigned int ms) {
    setTargetMs(ms);
    reset();
}

Timer::~Timer() {}

void Timer::reset() {
    start = getCurrentMs();
    finish = getCurrentMs();
}

bool Timer::check() {
    finish = getCurrentMs();
    int64_t startMs = start.count();
    int64_t finishMs = finish.count();
    if(finishMs - startMs >= targetMs) {
        reset();
        return true;
    }
    return false;
}

void Timer::setTargetMs(int64_t ms) {
    targetMs = ms;
}

int64_t Timer::getTargetMs() const {
    return targetMs;
}

std::chrono::milliseconds Timer::getCurrentMs() const {
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
}

int64_t Timer::getElapsedMs() {
    finish = getCurrentMs();
	int64_t finishMs = finish.count();
	int64_t startMs = start.count();
    return finishMs - startMs;
};
