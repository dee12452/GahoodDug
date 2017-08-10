#ifndef GAHOOD_TIMER_HPP
#define GAHOOD_TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer(unsigned int);
    ~Timer();

    void reset();
    bool check();
    
    void setTargetMs(unsigned int);
	__int64 getTargetMs() const;
	__int64 getElapsedMs();
private:
    std::chrono::milliseconds getCurrentMs() const;
    std::chrono::milliseconds start;
    std::chrono::milliseconds finish;
	__int64 targetMs;
};

#endif
