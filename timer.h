#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

struct Timer {

	std::chrono::time_point<std::chrono::high_resolution_clock> time;

	void start_timer() {
		time = std::chrono::high_resolution_clock::now();
	}

	double current_time() {
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - time);
		return elapsed.count();
	}

	double end_timer() {
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - time);
		return elapsed.count();
	}
};



#endif // TIMER_H