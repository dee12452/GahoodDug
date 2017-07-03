#include "../headers/BaseAnimation.hpp"
#include "../headers/Timer.hpp"


BaseAnimation::BaseAnimation(unsigned int duration) { 
    this->duration = duration;
    this->elapsedTimer = new Timer(duration);
}

BaseAnimation::~BaseAnimation() {
    if(elapsedTimer != NULL) {
        delete elapsedTimer;
        elapsedTimer = NULL;
    }
}

bool BaseAnimation::isFinished() {
    if(elapsedTimer->check()) {
        onFinish();
        return true;
    }
    return false;
}

void BaseAnimation::animate() {
    onAnimate(elapsedTimer->getElapsedMs());
}

void BaseAnimation::cancel() {
    onCancel(elapsedTimer->getElapsedMs());
}
