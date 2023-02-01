#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Rect.h"
#include "SpriteEffect.h"
#include "Keyboard.h"
#include "Font.h"
#include "Mouse.h"

class MenuScreen
{
public:
	MenuScreen(const std::string& text, const Vei2& in_textpos, Color textcolor, Color Pointercolor, int LineCap = 1,
		Surface* BackGround = nullptr);
	void Draw(Graphics& gfx) const;
	int ProcessMenu(Keyboard& kbd, Mouse& mous); //Palauttaa menucount, sen mukaan toisessa päässä switch tai if...
private:
	void DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const;
	void MenuMovement(const Keyboard::Event& e, const Mouse::Event& me);
	void SetSelectionPos(); //Laskee select merkin oikean kohdan
	std::vector<RectI> GetMenuRects(); //Hiiri komentoja varten olevat neliöt
private:
	Surface* BackGround;
	Font Menu = Font(L"kuvat//Consolas13x24.bmp");
	Color textcolor;
	Color Pointercolor;
	Vei2 textpos;
	int menucount;
	Vei2 SelPointPos;
	int cRadius = 6;
	int nlines;
	std::string menutext;
	Vei2 textcap;
	int LineCap;
	std::vector<RectI> menuRects;
};


































