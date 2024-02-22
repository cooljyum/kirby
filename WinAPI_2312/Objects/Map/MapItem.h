#pragma once

class MapItem : public Image
{
public:
	MapItem(Texture* texture, float speed = 1.0f, bool loop = false);
	~MapItem();

	void Update();
	void Render(HDC hdc);

	void Play(const Vector2& pos);

private:
	Animation* animation;
};