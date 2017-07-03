#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <vector>
class BaseAnimation;

class Animator {
public:
    static Animator * getInstance();
    static void deleteInstance();
    
    void animateAnimations();
    void startAnimation(BaseAnimation *);
    void stopAnimation(BaseAnimation *);
    void stopAllAnimations();

private:
    Animator();
    ~Animator();
    static Animator *instance;

    std::vector<BaseAnimation *> animations;
};

#endif
