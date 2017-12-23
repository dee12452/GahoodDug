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
    int getTargetMs() const;
	int getElapsedMs();
private:
    std::chrono::high_resolution_clock::time_point start, finish;
	unsigned int targetMs;
};

#endif
