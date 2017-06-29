#include "../headers/GahoodTimer.hpp"

GahoodTimer::GahoodTimer(unsigned int ms) {
    setTargetMs(ms);
    reset();
}

GahoodTimer::~GahoodTimer() {}

void GahoodTimer::reset() {
    start = getCurrentMs();
    finish = getCurrentMs();
}

bool GahoodTimer::check() {
    finish = getCurrentMs();
    unsigned int startMs = start.count();
    unsigned int finishMs = finish.count();
    if(finishMs - startMs >= targetMs) {
        reset();
        return true;
    }
    return false;
}

void GahoodTimer::setTargetMs(unsigned int ms) {
    targetMs = ms;
}

unsigned int GahoodTimer::getTargetMs() const {
    return targetMs;
}

std::chrono::milliseconds GahoodTimer::getCurrentMs() const {
    return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
}
