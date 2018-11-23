/*



*/
#pragma once
#include <chrono>


class Timer
{
public:
	Timer();
	~Timer() = default;

	void setTimer(const float _timer);
	void setWaitTime(const float _w_time);

	void startTimer();
	void stopTimer();
	void updateDeltaTime();
	const float getTime() const;
	const bool isTimeUp();

private:
	bool is_started;

	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point fin_time;

	float dt = 0.f;
	float timer = 0.f;
	float wait_time = 0.f;
};