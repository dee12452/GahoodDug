#ifndef GAHOOD_TIMER_HPP
#define GAHOOD_TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer(int64_t);
    ~Timer();

    void reset();
    bool check();
    
    void setTargetMs(int64_t);
    int64_t getTargetMs() const;
	int64_t getElapsedMs();
private:
    std::chrono::milliseconds getCurrentMs() const;
    std::chrono::milliseconds start;
    std::chrono::milliseconds finish;
	int64_t targetMs;
};

#endif
