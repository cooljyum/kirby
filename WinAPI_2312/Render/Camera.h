#pragma once

class Rect;

class Camera : public Singleton<Camera>
{
private:
	friend class Singleton;

	Camera();
	~Camera();

public:
	void Update();

	Vector2 GetPos();

	void SetTarget(Rect* target) { this->target = target; }
	void SetMapRect(Rect* rect) { mapRect = rect; }
	void SetOffset(float x, float y) { offset = { x, y }; }
	void SetPos(float x, float y);

private:
	void FreeMode();
	void FollowMove();

	void FixPos();

private:
	Rect* rect;
	Rect* mapRect = nullptr;
	Rect* target = nullptr;

	float moveSpeed = 1000.0f;
	Vector2 offset = CENTER;
	Vector2 destPos;
};