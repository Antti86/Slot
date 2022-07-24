#pragma once
#include "Rng.h"

class LineLogic  //Only for Board!
{
	friend class Board;
private:
	enum class Rollstatus
	{
		Stop,
		Slow,
		Fast
	};
private:
	void Procces(); //This will get the "ball rolling"
	bool Timer(float dt, float TimerEnd); //This is for the fast to slow rolling checkup..
	int GetFruit() const;
private:
	int TranslateFruitVal(int f); //Odds calculating, translates wider range to short range
private:
	Rollstatus rollstatus = Rollstatus::Stop;
	int testcounter = 0;
	int Fruit = 0;
	Rng rng;
	float TimerStart = 0;
	static constexpr int min = 0;
	static constexpr int max = 19;
};