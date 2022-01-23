#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Rng.h"
#include "Graphics.h"
#include "Rect.h"

class Fruits
{

public:
	Fruits(Vec2 pos);
	Fruits(Vec2 pos, int Fruit);
	void Draw(Graphics& gfx, class Board& brd) const;
	void Procces();
	int GetFruit() const;
	void MoveFruit(float dt);
	void Timer(float dt, float TimerEnd);
	bool IsRolling() const;
	int GetFruitDim() const;
	void CalculateFruitPos();
	Vec2& GetPos();
	Vec2 pos;
	int Fruit;
private:

	int TranslateFruitVal();
private:

	Surface fruitsheet = { L"Kuvat//MeatSmall.png" };
	
	Rng rng;
	
	int currentXfruit = 0;			//max 3
	int currentYfruit = 0;			//max 4
	static constexpr int width = 4;
	static constexpr int height = 2;
	static constexpr int dim = 70;
	Vei2 rectpos = { currentXfruit * dim, currentYfruit * dim };
	RectI picslice = RectI(rectpos, dim, dim);
	float speed = 700.0f;
	float TimerStart = 0;
	bool rolling = false;
	static constexpr int min = 0;
	static constexpr int max = 20;
};