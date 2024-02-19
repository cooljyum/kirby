#pragma once

class KirbtStarBullet : public Image
{
private:
	const float SPEED = 400.0f;
	const float GRAVITY = 3.0f;

	static const int SIZE = 100;

public:
	KirbtStarBullet();
	~KirbtStarBullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 pos, bool isRight);

public:
	static void CreateBullets();
	static void Shot(Vector2 pos, bool isRight);
	static void Delete();

	static void UpdateBullets();
	static void RenderBullets(HDC hdc);

	static bool IsBulletsCollision(Rect* rect);

	static void SetLandTexture(Texture* texture);

private:
	bool isRight;
	Vector2 velocity;

	Animation* animation;

	Texture* starTexture;

	Texture* landTexture;

	HPEN pen;

	static vector<KirbtStarBullet*> bullets;
};