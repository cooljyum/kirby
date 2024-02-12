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
	//	hdc, //����� ����
	//	100, 100, //����� ��ġ
	//	300, 300,//����� ũ��
	//	memDC,//������ ����
	//	100, 200,//������ ��ġ
	//	SRCCOPY
	//);

	SelectObject(memDC, testBitmap);

	StretchBlt(
		hdc, //����� ����
		0, 0, //����� ��ġ
		SCREEN_WIDTH, SCREEN_HEIGHT,//����� ũ��
		memDC,//������ ����
		0, 0,//������ ��ġ
		testSize.x, testSize.y,//������ ũ��
		SRCCOPY
	);

	SelectObject(memDC, sivaBitmap);

	POINT cutSize = { sivaSize.x / 8, sivaSize.y / 2 };

	GdiTransparentBlt(
		hdc, //����� ����
		CENTER_X, CENTER_Y, //����� ��ġ
		sivaSize.x / 8, sivaSize.y / 2,//����� ũ��
		memDC,//������ ����
		cutSize.x * curFrame.x, cutSize.y * curFrame.y,//������ ��ġ
		cutSize.x, cutSize.y,//������ ũ��
		MAGENTA
	);
}
