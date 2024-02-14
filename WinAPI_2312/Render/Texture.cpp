#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
	: imageFrame({ frameX, frameY }), transColor(transColor), isTrans(isTrans)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	bitmap = (HBITMAP)LoadImage(hInst, file.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);	

	BITMAP map;
	GetObject(bitmap, sizeof(BITMAP), &map);

	imageSize.x = map.bmWidth;
	imageSize.y = map.bmHeight;

	cutSize = { imageSize.x / imageFrame.x, imageSize.y / imageFrame.y };
	SelectObject(memDC, bitmap);

	alphaBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(alphaMemDC, alphaBitmap);

	ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
	DeleteDC(memDC);
	DeleteDC(alphaMemDC);
	DeleteObject(bitmap);
	DeleteObject(alphaBitmap);
}

void Texture::Render(HDC hdc, Rect* rect, POINT curFrame)
{
	if (!isTrans)
	{
		BitBlt(
			hdc,
			(int)rect->Left(), (int)rect->Top(),
			(int)rect->GetSize().x, (int)rect->GetSize().y,
			memDC,
			cutSize.x * curFrame.x,
			cutSize.y * curFrame.y,
			SRCCOPY
		);
		return;
	}	

	GdiTransparentBlt(
		hdc,
		(int)rect->Left(), (int)rect->Top(),
		(int)rect->GetSize().x, (int)rect->GetSize().y,
		memDC,
		cutSize.x * curFrame.x,
		cutSize.y * curFrame.y,
		cutSize.x, cutSize.y,
		transColor
	);
}

void Texture::Render(HDC hdc, Rect* rect, int alpha, POINT curFrame)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (!isTrans)
	{
		GdiAlphaBlend(
			hdc,
			(int)rect->Left(), (int)rect->Top(),
			(int)rect->GetSize().x, (int)rect->GetSize().y,
			memDC,
			cutSize.x * curFrame.x,
			cutSize.y * curFrame.y,
			cutSize.x, cutSize.y,
			blendFunc
		);
		return;
	}

	BitBlt(
		alphaMemDC,
		0, 0,
		(int)rect->GetSize().x, (int)rect->GetSize().y,
		hdc,
		(int)rect->Left(), (int)rect->Top(),
		SRCCOPY
	);

	GdiTransparentBlt(
		alphaMemDC,
		0, 0,
		(int)rect->GetSize().x, (int)rect->GetSize().y,
		memDC,
		cutSize.x * curFrame.x,
		cutSize.y * curFrame.y,
		cutSize.x, cutSize.y,
		transColor
	);

	GdiAlphaBlend(
		hdc,
		(int)rect->Left(), (int)rect->Top(),
		(int)rect->GetSize().x, (int)rect->GetSize().y,
		alphaMemDC,
		0, 0,
		(int)rect->GetSize().x, (int)rect->GetSize().y,
		blendFunc
	);
}

float Texture::GetPixelHeight(const Vector2& pos)
{
	int startY = pos.y < 0.0f ? 0 : (int)pos.y;

	for (int y = startY; y < imageSize.y; y++)
	{
		COLORREF color = GetPixel(memDC, (int)pos.x, y);

		if (color != transColor)
			return (float)y;
	}

	return (float)imageSize.y;
}

float Texture::GetPixelRight(Rect* rect)
{
	int start = rect->GetPos().x < 0.0f ? 0 : (int)rect->GetPos().x;
	int end = start + rect->Half().x;
	int what = (int)rect->GetPos().y - (int)rect->Half().y / 10;

	for (int x = start; x < end; x++)
	{
		COLORREF color = GetPixel(memDC, x, (int)rect->GetPos().y + (int)rect->Half().y/2);

		if (color != transColor)
			return (float)x;
	}

	return -1.0f;
}

float Texture::GetPixelLeft(Rect* rect)
{
	int start = rect->GetPos().x < 0.0f ? 0 : (int)rect->GetPos().x;
	int end = start - rect->Half().x;

	for (int x = start; x > end; x--)
	{
		COLORREF color = GetPixel(memDC, x, (int)rect->GetPos().y + (int)rect->Half().y / 2);

		if (color != transColor)
			return (float)x;
	}

	return -1.0f;
}

Texture* Texture::Add(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (textures.count(file) > 0)
		return textures[file];

	Texture* texture = new Texture(file, frameX, frameY, isTrans, transColor);
	textures[file] = texture;

	return texture;
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> texture : textures)
		delete texture.second;		
}
