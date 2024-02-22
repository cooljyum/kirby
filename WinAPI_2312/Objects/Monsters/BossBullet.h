#pragma once

class BossBullet : public Image
{
private:
	const float SPEED = 400.0f;
	const float GRAVITY = 3.0f;

	static const int SIZE = 2;

public:
	BossBullet();
	~BossBullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 pos, bool isRight);
	void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	

public:
	static void init();
	static void CreateBullets();
	static void Shot(Vector2 pos, bool isRight);
	static void Delete();

	static void UpdateBullets();
	static void RenderBullets(HDC hdc);

	static bool IsBulletsCollision(Rect* rect);
	static BossBullet* Collision(Rect* rect);

	static void SetLandTexture(Texture* texture);

private:
	bool isRight;
	Vector2 velocity;

	Animation* animation;

	Texture* starTexture;

	Texture* landTexture;

	HPEN pen;

	static vector<BossBullet*> bullets;
};