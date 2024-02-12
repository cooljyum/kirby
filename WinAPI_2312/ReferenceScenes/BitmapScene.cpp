#include "Framework.h"
#include "BitmapScene.h"

BitmapScene::BitmapScene()
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);

	testBitmap = (HBITMAP)LoadImage(hInst, L"Textures/Background.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);	

	BITMAP bitmap;
	GetObject(testBitmap, sizeof(BITMAP), &bitmap);

	testSize.x = bitmap.bmWidth;
	testSize.y = bitmap.bmHeight;

	sivaBitmap = (HBITMAP)LoadImage(hInst, L"Textures/siva_run.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);

	bitmap;
	GetObject(sivaBitmap, sizeof(BITMAP), &bitmap);

	sivaSize.x = bitmap.bmWidth;
	sivaSize.y = bitmap.bmHeight;
}

BitmapScene::~BitmapScene()
{
	DeleteDC(memDC);
	DeleteObject(testBitmap);
	DeleteObject(sivaBitmap);
}

void BitmapScene::Update()
{
}

void BitmapScene::Render(HDC hdc)
{
	//BitBlt(
	//	hdc, //출력할 영역
	//	100, 100, //출력할 위치
	//	300, 300,//출력할 크기
	//	memDC,//복사할 영역
	//	100, 200,//복사할 위치
	//	SRCCOPY
	//);

	SelectObject(memDC, testBitmap);

	StretchBlt(
		hdc, //출력할 영역
		0, 0, //출력할 위치
		SCREEN_WIDTH, SCREEN_HEIGHT,//출력할 크기
		memDC,//복사할 영역
		0, 0,//복사할 위치
		testSize.x, testSize.y,//복사할 크기
		SRCCOPY
	);

	SelectObject(memDC, sivaBitmap);

	POINT cutSize = { sivaSize.x / 8, sivaSize.y / 2 };

	GdiTransparentBlt(
		hdc, //출력할 영역
		CENTER_X, CENTER_Y, //출력할 위치
		sivaSize.x / 8, sivaSize.y / 2,//출력할 크기
		memDC,//복사할 영역
		cutSize.x * curFrame.x, cutSize.y * curFrame.y,//복사할 위치
		cutSize.x, cutSize.y,//복사할 크기
		MAGENTA
	);
}
