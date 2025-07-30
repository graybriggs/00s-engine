#include "timer.h"

#include <GLFW/glfw3.h>

#include <iostream>

Timer::Timer() {
    last_time = glfwGetTime();
}

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

void Timer::start_frame_time() {
    frame_current_time = glfwGetTime();
}

void Timer::check_frame_time() {
    	++frame_count;
		if (frame_current_time - last_time >= 1.0) {
			std::cout << 1000.0 / frame_count << " ms/frame\n";
			frame_count = 0;
			last_time += 1.0;
		}	
}