#pragma once

class Image : public Rect
{
public:
	Image(wstring file, int frameX = 1, int frameY = 1, bool isTrans = true, COLORREF transColor = MAGENTA);
	Image(Texture* texture = nullptr);
	~Image();

	void Render(HDC hdc, POINT curFrame = { 0, 0 });
	void Render(HDC hdc, int alpha, POINT curFrame = { 0, 0 });

	void SetTexture(Texture* texture);

	Texture* GetTexture() { return texture; }
protected:
	Texture* texture;
	POINT maxFrame;
};