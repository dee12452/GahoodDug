#include "../headers/FadeAnimation.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Sprite.hpp"

#ifndef NULL
#define NULL 0
#endif

FadeAnimation::FadeAnimation(Sprite *sprite, 
        bool isFadeIn, 
        unsigned int duration) : BaseAnimation(duration) {
    this->fadeIn = isFadeIn;
    this->sprite = sprite;
    if(fadeIn) {
        sprite->setAlpha(Constants::SPRITE_ALPHA_NONE);
    }
    else {
        sprite->setAlpha(Constants::SPRITE_ALPHA_FULL);
    }
}

FadeAnimation::~FadeAnimation() {
    /**
     * Animations should not be cleaning up sprites
     */
    sprite = NULL;
}

void FadeAnimation::onAnimate(unsigned int elapsedMs) {
    if(fadeIn) {
        sprite->setAlpha(Constants::SPRITE_ALPHA_FULL * elapsedMs / duration);
    }
    else {
        sprite->setAlpha(Constants::SPRITE_ALPHA_FULL - (Constants::SPRITE_ALPHA_FULL * elapsedMs / duration));
    }
}

void FadeAnimation::onCancel(unsigned int) {
    onFinish();
}

void FadeAnimation::onFinish() {
    if(fadeIn) {
        sprite->setAlpha(Constants::SPRITE_ALPHA_FULL);
    }
    else {
        sprite->setAlpha(Constants::SPRITE_ALPHA_NONE);
    }
}
