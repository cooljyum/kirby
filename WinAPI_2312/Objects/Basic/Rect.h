#pragma once

class Rect
{
public:
	Rect() = default;
	Rect(Vector2 pos, Vector2 size);
	Rect(float left, float top, float right, float bottom);

	void Render(HDC hdc);
	void CamRender(HDC hdc);

	bool IsCollision(const Vector2& point) const;
	bool IsCollision(const Rect* rect, OUT Vector2* overlap = nullptr) const;

	void Translate(Vector2 direction) { pos += direction; }

	float Left() const { return pos.x - size.x * 0.5f; }
	float Right() const { return pos.x + size.x * 0.5f; }
	float Top() const { return pos.y - size.y * 0.5f; }
	float Bottom() const { return pos.y + size.y * 0.5f; }

	Vector2 GetSize() { return size; }
	void SetSize(const Vector2& size) { this->size = size; }
	Vector2 Half() { return Vector2(size.x * 0.5f, size.y * 0.5f); }

	bool IsActive() { return isActive; }
	void SetActive(bool isActive) { this->isActive = isActive; }

	Vector2 GetPos() const { return pos; }
	void SetPos(const Vector2& pos) { this->pos = pos; }
	void SetPos(const float& x, const float& y) { pos = { x, y }; }

	string GetTag() const { return tag; }
	void SetTag(const string& tag) { this->tag = tag; }

	void SetColor(COLORREF color) { this->color = color; }

	static void CreatePens();
	static void DeletePens();
	static void OnDraw() { isDraw = !isDraw; }

protected:
	string tag;

	bool isActive = true;

	Vector2 pos;
	Vector2 size;
	COLORREF color = GREEN;

	static map<COLORREF, HPEN> pens;
	static bool isDraw;
};