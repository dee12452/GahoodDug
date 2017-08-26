#ifndef BASE_ANIMATION_HPP
#define BASE_ANIMATION_HPP

#include <cstdint>

class Timer;

class BaseAnimation {
public:
    BaseAnimation(unsigned int);
    virtual ~BaseAnimation();

    void animate();
    void cancel();
    virtual bool isFinished();

protected:
    virtual void onFinish() = 0;
    virtual void onCancel(int64_t) = 0;
    virtual void onAnimate(int64_t) = 0;
    int duration;
    Timer *elapsedTimer;
};

#endif
