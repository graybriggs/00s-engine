#include "timer.h"

void Timer::start_timer() {
    time = std::chrono::high_resolution_clock::now();
}

double Timer::current_time() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - time);
    return elapsed.count();
}

double Timer::end_timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - time);
    return elapsed.count();
}