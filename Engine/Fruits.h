#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Rng.h"
#include "Graphics.h"
#include "Rect.h"

class Fruits
{
	friend class Board;
public:
	Fruits(Vei2 pos);
	void Draw(Graphics& gfx) const;
	void Procces(int counter, int min, int max);
	int GetFruit() const;
private:

	Surface fruitsheet = { L"Kuvat//MeatSmall.png" };
	Vei2 pos;
	Rng rng;
	int Fruit = 0;
	int currentXfruit = 0;			//max 3
	int currentYfruit = 0;			//max 4
	static constexpr int width = 4;
	static constexpr int height = 2;
	static constexpr int dim = 70;
	Vei2 rectpos = { currentXfruit * dim, currentYfruit * dim };
	RectI picslice = RectI(rectpos, dim, dim);
};