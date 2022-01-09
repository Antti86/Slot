#include "Fruits.h"
#include "Board.h"

Fruits::Fruits(Vec2 pos)
	:
	pos(pos)
{
}

void Fruits::Draw(Graphics& gfx, class Board& brd) const
{
	gfx.DrawSprite((Vei2)pos, picslice, brd.GetClippingRect(), fruitsheet, SpriteEffect::Chroma{ Colors::White });
}

void Fruits::Procces()
{
	rolling = true;
	Fruit = rng.rngtest(min, max);

	CalculateFruitPos();
}

int Fruits::GetFruit() const
{
	return Fruit;
}

void Fruits::MoveFruit(float dt)
{
	pos.y += speed * dt;
}

void Fruits::Timer(float dt, float TimerEnd)
{
	if ((TimerStart += dt) > TimerEnd)
	{
		TimerStart = 0.0f;
		rolling = false;
	}
	else
	{
		MoveFruit(dt);
		rolling = true;
	}
}

bool Fruits::IsRolling() const
{
	return rolling;
}

void Fruits::CalculateFruitPos()
{
	Fruit = TranslateFruitVal();
	currentXfruit = Fruit % width;
	currentYfruit = Fruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}

int Fruits::TranslateFruitVal()
{
	int ret = 0;

	if (Fruit >= 8 && Fruit <= 10)
	{
		ret = 7;
	}
	else if (Fruit >= 11 && Fruit <= 13)
	{
		ret = 6;
	}
	else if (Fruit >= 14 && Fruit <= 15)
	{
		ret = 5;
	}
	else if (Fruit >= 16 && Fruit <= 17)
	{
		ret = 4;
	}
	else if (Fruit == 18 )
	{
		ret = 3;
	}
	else if (Fruit == 19)
	{
		ret = 2;
	}
	else
	{
		ret = Fruit;
	}
	return ret;
}
