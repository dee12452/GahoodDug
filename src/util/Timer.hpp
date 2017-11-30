#ifndef GAHOOD_TIMER_HPP
#define GAHOOD_TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer(int);
    ~Timer();

    void reset();
    bool check();
    
    void setTargetMs(int);
    int getTargetMs() const;
	int getElapsedMs();
private:
    std::chrono::high_resolution_clock::time_point start, finish;
	int targetMs;
};

#endif
