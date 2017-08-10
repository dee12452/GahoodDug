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
    void onCancel(__int64) override;
    void onAnimate(__int64) override;
    bool fadeIn;
    Sprite *sprite;
};

#endif
