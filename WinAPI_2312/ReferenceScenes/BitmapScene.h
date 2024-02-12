#pragma once

class BitmapScene : public Scene
{
public:
	BitmapScene();
	~BitmapScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	HDC memDC;
	HBITMAP testBitmap;
	HBITMAP sivaBitmap;

	POINT testSize;
	POINT sivaSize;

	POINT curFrame = {7, 1};
};