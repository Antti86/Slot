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
	Fruits(Vec2 pos);
	Fruits(Vec2 pos, int GfxFruit);
	void Draw(Graphics& gfx, class Board& brd) const;
	void Procces();
	int GetFruit() const;
	int GetGFXFruit() const;
	void MoveFruit(float dt);
	void Timer(float dt, float TimerEnd);
	Vec2 GetPos() const;
	const Rollstatus& GetRollStatus() const;
	int GetFruitDim() const;
	void CalculateFruitPos();

	void MoveLine(std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float dt);
	void SetSpeed(float s);
	bool TimerTest(float dt, float TimerEnd);
	Rollstatus rollstatus = Rollstatus::Stop;
private:
	
	int TranslateFruitVal(int f);
private:
	Vec2 pos;	//gfx
	int Fruit;  //log
	int GfxFruit;	//gfx
	float fastspeed = 700.0f; //gfx
	float slowspeed = 100.0f; //gfx
	float speed = fastspeed;  //gfx
	Surface fruitsheet = { L"Kuvat//MeatSmall.png" }; //gfx

	Rng rng;	//log
	
	int currentXfruit = 0;			//max 3 gfx
	int currentYfruit = 0;			//max 4 gfx
	static constexpr int width = 4; //gfx
	static constexpr int height = 2; //gfx
	static constexpr int dim = 70;   //gfx
	Vei2 rectpos = { currentXfruit * dim, currentYfruit * dim }; //gfx
	RectI picslice = RectI(rectpos, dim, dim); //gfx

	//log
	float TimerStart = 0;
	float TimerStart1 = 0;
	static constexpr int min = 0;
	static constexpr int max = 20;
};