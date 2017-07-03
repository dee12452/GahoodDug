#ifndef BASE_ANIMATION_HPP
#define BASE_ANIMATION_HPP

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
    virtual void onCancel(unsigned int) = 0;
    virtual void onAnimate(unsigned int) = 0;
    int duration;
    Timer *elapsedTimer;
};

#endif
