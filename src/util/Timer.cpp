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
    __int64 startMs = start.count();
    __int64 finishMs = finish.count();
    if(finishMs - startMs >= targetMs) {
        reset();
        return true;
    }
    return false;
}

void Timer::setTargetMs(__int64 ms) {
    targetMs = ms;
}

__int64 Timer::getTargetMs() const {
    return targetMs;
}

std::chrono::milliseconds Timer::getCurrentMs() const {
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
}

__int64 Timer::getElapsedMs() {
    finish = getCurrentMs();
	__int64 finishMs = finish.count();
	__int64 startMs = start.count();
    return finishMs - startMs;
};
