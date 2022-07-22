#include "LineLogic.h"

void LineLogic::Procces()
{
	rollstatus = Rollstatus::Fast;
	Fruit = rng.rngtest(min, max);
	Fruit = TranslateFruitVal(Fruit);
}

bool LineLogic::Timer(float dt, float TimerEnd)
{
	if ((TimerStart += dt) > TimerEnd)
	{
		TimerStart = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

int LineLogic::GetFruit() const
{
	return Fruit;
}

int LineLogic::TranslateFruitVal(int f)
{
	int ret = 0;

	if (f >= 8 && f <= 10)
	{
		ret = 7;
	}
	else if (f >= 11 && f <= 13)
	{
		ret = 6;
	}
	else if (f >= 14 && f <= 15)
	{
		ret = 5;
	}
	else if (f >= 16 && f <= 17)
	{
		ret = 4;
	}
	else if (f == 18)
	{
		ret = 3;
	}
	else if (f == 19)
	{
		ret = 2;
	}
	else
	{
		ret = f;
	}
	return ret;
}
