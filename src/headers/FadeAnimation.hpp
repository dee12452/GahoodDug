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
    void onCancel(int64_t) override;
    void onAnimate(int64_t) override;
    bool fadeIn;
    Sprite *sprite;
};

#endif
