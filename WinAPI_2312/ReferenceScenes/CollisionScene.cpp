#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	rect = new Rect(CENTER, { 100, 200 });
	rect2 = new Rect(CENTER, { 200, 100 });

	redBrush = CreateSolidBrush(RED);
	blueBrush = CreateSolidBrush(BLUE);
}

CollisionScene::~CollisionScene()
{
	delete rect;
	delete rect2;

	DeleteObject(redBrush);
	DeleteObject(blueBrush);
}

void CollisionScene::Update()
{
	rect2->SetPos(mousePos);

	isCollision = rect->IsCollision(rect2);
}

void CollisionScene::Render(HDC hdc)
{
	isCollision ? SelectObject(hdc, redBrush) : SelectObject(hdc, blueBrush);

	rect->Render(hdc);
	rect2->Render(hdc);
}
