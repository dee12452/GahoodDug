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
    virtual void onCancel(__int64) = 0;
    virtual void onAnimate(__int64) = 0;
    int duration;
    Timer *elapsedTimer;
};

#endif
