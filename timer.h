#pragma once

#include <chrono>


struct Timer {
public:
	
	Timer();
	void start_timer();
	double current_time();
	double end_timer();

	void start_frame_time();
	void check_frame_time();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> time;
	double frame_current_time;
	double last_time;
	int frame_count;
};

