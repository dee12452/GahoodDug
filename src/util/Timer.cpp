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
    unsigned int startMs = start.count();
    unsigned int finishMs = finish.count();
    if(finishMs - startMs >= targetMs) {
        reset();
        return true;
    }
    return false;
}

void Timer::setTargetMs(unsigned int ms) {
    targetMs = ms;
}

unsigned int Timer::getTargetMs() const {
    return targetMs;
}

std::chrono::milliseconds Timer::getCurrentMs() const {
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
}

unsigned int Timer::getElapsedMs() {
    finish = getCurrentMs();
    unsigned int finishMs = finish.count();
    unsigned int startMs = start.count();
    return finishMs - startMs;
};
