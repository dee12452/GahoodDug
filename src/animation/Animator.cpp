#include "../headers/Animator.hpp"
#include "../headers/BaseAnimation.hpp"

#ifndef NULL
#define NULL 0
#endif

Animator * Animator::instance = NULL;

Animator::Animator() {}

Animator::~Animator() {}

Animator * Animator::getInstance() {
    if(instance == NULL) {
        instance = new Animator();
    }
    return instance;
}

void Animator::deleteInstance() {
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void Animator::animateAnimations() {
    for(unsigned int i = 0; i < animations.size(); i++) {
        if(!animations[i]->isFinished()) {
            animations[i]->animate();
        }
        else {
            std::swap(animations[i], animations[animations.size() - 1]);
            delete animations[animations.size() - 1];
            animations[animations.size() - 1] = NULL;
            animations.pop_back();
        }
    }
}

void Animator::startAnimation(BaseAnimation *animation) {
    if(animation != NULL) {
        animations.push_back(animation);
    }
}

void Animator::stopAnimation(BaseAnimation *animation) {
    for(unsigned int i = 0; i < animations.size(); i++) {
        if(animation == animations[i]) {
            animations[i]->cancel();
            std::swap(animations[i], animations[animations.size() - 1]);
            delete animations[animations.size() - 1];
            animations[animations.size() - 1] = NULL;
            animations.pop_back();
        }
    }
}

void Animator::stopAllAnimations() {
    for(unsigned int i = 0; i < animations.size(); i++) {
        animations[i]->cancel();
        std::swap(animations[i], animations[animations.size() - 1]);
        delete animations[animations.size() - 1];
        animations[animations.size() - 1] = NULL;
        animations.pop_back();
    }

}
