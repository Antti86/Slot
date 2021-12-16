#pragma once
#include <algorithm>
#include <chrono>
#include <ratio>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <thread>

#include <random>
#include <iostream>

class FrameTimerRng
{
public:
	FrameTimerRng()
	{
		using namespace std::chrono;
		highlast = high_resolution_clock::now();
	}
	uint64_t GetNano()
	{
		using namespace std::chrono;
		nanoseconds n(highlast.time_since_epoch());
		uint64_t r = (uint64_t)n.count();
		return r;
		
	}
	auto GetHighLast() const
	{
		return highlast;
	}
private:
	std::chrono::high_resolution_clock::time_point highlast;
};


class ClockRng
{
public:
	ClockRng()
	{
		UpdateTime();
	}
	time_t GetTime() const
	{
		return aika;
	}
	void UpdateTime()
	{
		aika = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		localtime_s(&timebuffer, &aika);
	}
private:
	time_t aika;
	struct tm timebuffer;
};

class Rng
{
public:
	int rng(int min, int max);
	unsigned int rngtest(unsigned int min, unsigned int max);
private:
	template<typename T>
	T HexaToDecConverion(const std::string& input)
	{
		T pow = (T)input.size() - 1;
		T base = 16;
		T num = 0;
		T result = 0;
		for (auto i : input)
		{
			if (std::isdigit(i))
			{
				num = i - '0';
			}
			else
			{
				num = (i - 'A') + 10;
			}
			result += num * (T)std::pow(base, pow);
			pow--;
		}
		return result;
	}

private:
	ClockRng clock;
	std::mt19937 rg{ (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count() };
};