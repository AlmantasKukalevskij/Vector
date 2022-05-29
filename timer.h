#pragma once

#include <chrono>
#include <iostream>
#include <string>

struct Timer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<double> duration;

	std::string Say;

	Timer(std::string say);
	~Timer();
};