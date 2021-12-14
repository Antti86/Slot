#include "Surface.h"
#define FULL_WINTARD
#include "ChiliWin.h"
#include <algorithm>
namespace Gdiplus
{
	using std::max;
	using std::min;
}
#include <gdiplus.h>


namespace gdi = Gdiplus;

Surface::Surface(const std::wstring& filename)
{
	gdi::Bitmap bitmap(filename.c_str());
	
	if (bitmap.GetLastStatus() != Gdiplus::Ok)	//string antaa data lose errorin, keksi korjaus
	{
		const std::string n (filename.begin(), filename.end());
		throw std::runtime_error("Surface Unable to load file" + n);
	}
	

	width = bitmap.GetWidth();
	height = bitmap.GetHeight();
	Pixels.resize(width * height);
	const BOOL isAlpha = gdi::IsAlphaPixelFormat(bitmap.GetPixelFormat()) == TRUE;	//alpha blendaus ei toimi tosdistettavasti..

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gdi::Color pixel;

			bitmap.GetPixel(x, y, &pixel);
			
			if (isAlpha == TRUE && filename.find(L"pm_") != std::wstring::npos)
			{
				PutPixel(x, y, { pixel.GetA(), pixel.GetR(), pixel.GetG(), pixel.GetB() });
				
			}
			else
			{
				PutPixel(x, y, { pixel.GetR(), pixel.GetG(), pixel.GetB() });
			}
		}
	}
	
	if (filename.find(L"pm_") != std::wstring::npos)
	{
		SetAlpha();
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	Pixels(width * height)
{
}



Surface::Surface(Surface&& donor) noexcept
{
	*this = std::move(donor);
}

Surface& Surface::operator=(Surface&& rhs) noexcept
{
	Pixels = std::move(rhs.Pixels);
	width = rhs.width;
	height = rhs.height;
	rhs.width = 0;
	rhs.height = 0;
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	Pixels.data()[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return Pixels.data()[y * width + x];
}

const Color* Surface::Data()
{
	return Pixels.data();
}

void Surface::Fill(Color c)
{
	std::fill(Pixels.begin(), Pixels.begin() + width * height, c);
}

void Surface::SetAlpha()
{
	const int nPixels = width * height;

	for (int i = 0; i < nPixels; i++)
	{
		auto pix = Pixels.data()[i];
		const int alpha = pix.GetA();

		pix.SetR((pix.GetR() * alpha) / 256);
		pix.SetG((pix.GetG() * alpha) / 256);
		pix.SetB((pix.GetB() * alpha) / 256);

		Pixels.data()[i] = pix;
	}

}

RectI Surface::GetRect() const
{
	return { 0, GetWidth(), 0, GetHeight() };
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
