#pragma once

#include <chrono>

struct Timer {

	std::chrono::time_point<std::chrono::high_resolution_clock> time;

	void start_timer();
	double current_time();
	double end_timer();
};

