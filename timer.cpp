#include "timer.h"

Timer::Timer(std::string say)
{
	start = std::chrono::high_resolution_clock::now();
	Say = say;
}

Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;

	std::cout << Say << " " << duration.count() << "sek. " << std::endl;
}