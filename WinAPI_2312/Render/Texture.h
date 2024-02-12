#pragma once

class Rect;

class Texture
{
private:
	Texture(wstring file, int frameX = 1, int frameY = 1,
		bool isTrans = false, COLORREF transColor = MAGENTA);
	~Texture();

public:
	void Render(HDC hdc, Rect* rect, POINT curFrame = { 0, 0 });
	void Render(HDC hdc, Rect* rect, int alpha, POINT curFrame = { 0, 0 });

	float GetPixelHeight(const Vector2& pos);

	Vector2 GetSize() { return cutSize; }
	POINT GetFrame() { return imageFrame; }
	HDC GetMemDC() { return memDC; }
	COLORREF GetTransColor() { return transColor; }

public:
	static Texture* Add(wstring file, int frameX = 1, int frameY = 1,
		bool isTrans = true, COLORREF transColor = MAGENTA);
	static void Delete();

private:
	HDC memDC;
	HDC alphaMemDC;
	HBITMAP bitmap;
	HBITMAP alphaBitmap;

	BLENDFUNCTION blendFunc;

	COLORREF transColor;

	POINT imageSize, imageFrame, cutSize;

	bool isTrans;

	static unordered_map<wstring, Texture*> textures;
};