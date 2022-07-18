#pragma once
#include "Vec2.h"
#include "Surface.h"
#include "Rng.h"
#include "Graphics.h"
#include "Rect.h"

class Fruits
{
public:
	enum class Rollstatus
	{
		Stop,
		Slow,
		Fast
	};
public:
	Fruits() = default;
	Fruits(Vec2 pos, int GfxFruit);
	void Draw(Graphics& gfx, class Board& brd) const;
	void Procces(); //This will get the "ball rolling"
	void CalculateFruitPos(); //Getting right fruit pic from the sprite sheet
	void MoveFruit(float dt); //Moving single fruit
	void MoveLine(Fruits& line, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float dt); 
	//Moving multiple fruits, Encap reasons this is here and not in board class

	bool Timer(float dt, float TimerEnd); //This is for the fast to slow rolling checkup..

	Vec2 GetPos() const;
	const Rollstatus& GetRollStatus() const;
	int GetFruitDim() const;
	int GetFruit() const;
	int GetGFXFruit() const;
	
	void SetSpeed(float s);
	Rollstatus rollstatus = Rollstatus::Stop;
private:
	int TranslateFruitVal(int f); //Odds calculating, translates wider range to short range
private:
	Vec2 pos;	//gfx
	int Fruit = 0;  //log
	int GfxFruit = 0;	//gfx
	float speed = 700.0f;  //gfx
	Surface fruitsheet = { L"Kuvat//MeatSmall.png" }; //gfx
	Rng rng;	//log
	int currentXfruit = 0;			//max 3 gfx
	int currentYfruit = 0;			//max 4 gfx
	static constexpr int width = 4; //gfx
	static constexpr int height = 2; //gfx
	static constexpr int dim = 70;   //gfx
	Vei2 rectpos = { currentXfruit * dim, currentYfruit * dim }; //gfx
	RectI picslice = RectI(rectpos, dim, dim); //gfx
	int testcounter = 0;
	//log
	float TimerStart = 0;
	static constexpr int min = 0;
	static constexpr int max = 20;
};