#include "MenuScreens.h"

MenuScreen::MenuScreen(const std::string& text, const Vei2& in_textpos, Color textcolor, Color Pointercolor, int LineCap,
	Surface* BackGround)
	:
	menutext(text),
	textpos(in_textpos),
	BackGround(BackGround),
	menucount(0),
	textcolor(textcolor),
	Pointercolor(Pointercolor),
	LineCap(LineCap)
{
	nlines = Menu.GetNumberOfLines(text);
	SetSelectionPos();
	menuRects = GetMenuRects();
}

void MenuScreen::Draw(Graphics& gfx) const
{
	if (BackGround != nullptr)
	{
		SpriteEffect::NoChroma E;
		gfx.DrawSprite(Vei2(0, 0), *BackGround, E);
	}
	Menu.DrawTexts(menutext, textpos, gfx, textcolor, LineCap);
	DrawSelectionPointer(gfx, SelPointPos);
}


void MenuScreen::DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const
{
	gfx.DrawCircle(StartMenuP.x, StartMenuP.y, cRadius, Pointercolor);
}

void MenuScreen::MenuMovement(const Keyboard::Event& e, const Mouse::Event& me) 
{
	if (e.GetCode() == VK_UP && menucount > 0)
	{
		menucount -= 1;
	}
	if (e.GetCode() == VK_DOWN && menucount < nlines)
	{
		menucount += 1;
	}
	for (int i = 0; i < menuRects.size(); i++)
	{
		if (me.LeftIsPressed())
		{
			if (menuRects[i].IsInside(me.GetPos()))
			{
				menucount = i;
			}
		}

	}
}

void MenuScreen::SetSelectionPos()
{
	SelPointPos.x = textpos.x - 30;
	SelPointPos.y = (textpos.y + (Menu.GetcharHeight() / 2)) + ((menucount * Menu.GetcharHeight()) * LineCap);
}

std::vector<RectI> MenuScreen::GetMenuRects()
{
	std::vector<RectI> ret;
	int x = 0;
	int y = 0;
	for (int i = 0; i < menutext.size(); i++)
	{
		if (menutext[i] != '\n' && i != menutext.size() - 1)
		{
			x++;
		}
		else
		{
			if (i == menutext.size() - 1)
			{
				x++;
			}
			int width = Menu.GetcharWidth() * x;
			int ypos = textpos.y + ((y * Menu.GetcharHeight()) * LineCap);
			ret.emplace_back(textpos.x, textpos.x + width, ypos, ypos + Menu.GetcharHeight());
			x = 0;
			y++;
		}
	}
	return ret;
}

int MenuScreen::ProcessMenu(Keyboard& kbd, Mouse& mous)
{
	SetSelectionPos();
	const Keyboard::Event e = kbd.ReadKey();
	const Mouse::Event me = mous.Read();
	MenuMovement(e, me);
	if ((e.IsPress() && e.GetCode() == VK_RETURN) || me.LeftIsPressed() )
	{
		return menucount;
	}
	return -1;
}






