#ifndef FADE_ANIMATION_HPP
#define FADE_ANIMATION_HPP

#include "BaseAnimation.hpp"

class Sprite;

class FadeAnimation : public BaseAnimation {
public:
    FadeAnimation(Sprite *, bool, unsigned int);
    ~FadeAnimation() override;

protected:
    void onFinish() override;
    void onCancel(unsigned int) override;
    void onAnimate(unsigned int) override;
    bool fadeIn;
    Sprite *sprite;
};

#endif
