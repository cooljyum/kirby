#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	rect = new Rect({}, { SCREEN_WIDTH, SCREEN_HEIGHT });
}

Camera::~Camera()
{
	delete rect;
}

void Camera::Update()
{
	if (target)
		FollowMove();
	else
		FreeMode();

	FixPos();
}

Vector2 Camera::GetPos()
{
	return rect->GetPos();
}

void Camera::SetPos(float x, float y)
{
	rect->SetPos(x, y);
}

void Camera::FreeMode()
{
	if (KEY->Press(VK_RBUTTON))
	{
		if (KEY->Press('A'))
			rect->Translate(Vector2::Left() * moveSpeed * DELTA);
		if (KEY->Press('S'))
			rect->Translate(Vector2::Down() * moveSpeed * DELTA);
		if (KEY->Press('D'))
			rect->Translate(Vector2::Right() * moveSpeed * DELTA);
		if (KEY->Press('W'))
			rect->Translate(Vector2::Up() * moveSpeed * DELTA);
	}
}

void Camera::FollowMove()
{
	destPos = target->GetPos() - offset;

	rect->SetPos(Lerp(rect->GetPos(), destPos, moveSpeed * DELTA));
}

void Camera::FixPos()
{
	if (mapRect == nullptr) return;

	Vector2 pos = rect->GetPos();

	if (pos.x < mapRect->Left())
		pos.x = mapRect->Left();

	if (pos.x > mapRect->Right() - rect->GetSize().x)
		pos.x = mapRect->Right() - rect->GetSize().x;

	if (pos.y < mapRect->Top())
		pos.y = mapRect->Top();

	if (pos.y > mapRect->Bottom() - rect->GetSize().y)
		pos.y = mapRect->Bottom() - rect->GetSize().y;

	rect->SetPos(pos);
}
