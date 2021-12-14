#define FULL_WINTARD

#include "ChiliWin.h"
#include "GDIPlusManager.h"
#include <algorithm>

namespace Gdiplus
{
	using std::min;
	using std::max;
}

#include <gdiplus.h>
#pragma comment( lib,"gdiplus.lib" )

ULONG_PTR GDIPlusManager::token = 0;
int GDIPlusManager::RefCount = 0;

namespace gdi = Gdiplus;

GDIPlusManager::GDIPlusManager()
{
	if (RefCount++ == 0)
	{
		gdi::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		gdi::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--RefCount == 0)
	{
		gdi::GdiplusShutdown(token);
	}
	
}
