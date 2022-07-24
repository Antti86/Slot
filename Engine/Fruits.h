#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Graphics.h"
#include "Rect.h"

class Fruits //Only for Board!
{
	friend class Board;
private:
	Fruits(Vec2 pos, int GfxFruit);
	void Draw(Graphics& gfx, class Board& brd) const;
	void CalculateFruitPos(); //Getting right fruit pic from the sprite sheet
	void MoveFruit(float dt); //Moving single fruit
	Vec2 GetPos() const;
	void SetSpeed(float s);
private:
	int GfxFruit;
	Vec2 pos;
	float speed = 700.0f;
	Surface fruitsheet = { L"Kuvat//MeatSmall.png" };
	int currentXfruit = 0;			//max 3 gfx
	int currentYfruit = 0;			//max 4 gfx
	static constexpr int width = 4; 
	static constexpr int height = 2; 
	static constexpr int dim = 70;   
	Vei2 rectpos = { currentXfruit * dim, currentYfruit * dim }; 
	RectI picslice = RectI(rectpos, dim, dim); 
};