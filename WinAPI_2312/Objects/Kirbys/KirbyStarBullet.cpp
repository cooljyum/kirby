#include "Framework.h"
#include "KirbyStarBullet.h"

vector<KirbyStarBullet*> KirbyStarBullet::bullets;

KirbyStarBullet::KirbyStarBullet() : Image(nullptr)
{
	starTexture = Texture::Add(L"Kirby_Resources/Effect/ShotEffect.bmp", 8, 1, true);

	SetTexture(starTexture);

	animation = new Animation(maxFrame);
	animation->SetDefault(true);

	isActive = false;

	pen = CreatePen(PS_SOLID, 1, MAGENTA);
	animation->SetSpeed(7.0f);
}

KirbyStarBullet::~KirbyStarBullet()
{
	delete animation;
	DeleteObject(pen);
}

void KirbyStarBullet::Update()
{
	if (!isActive) return;

	Translate({ velocity.x * SPEED * DELTA, 0.0f });

	animation->Update();

}

void KirbyStarBullet::Render(HDC hdc)
{
	Image::CamRender(hdc, animation->GetFrame());
}

void KirbyStarBullet::Fire(Vector2 pos, bool isRight)
{
	isActive = true;
	this->isRight = isRight;
	SetTexture(starTexture);

	if (isRight)
	{
		this->velocity = { +1.0f, 0 };
	}
	else 
	{
		this->velocity = { -1.0f, 0 };
	}

	animation->Play();

	SetPos(pos);
}

void KirbyStarBullet::CreateBullets()
{
	bullets.resize(SIZE);

	for (KirbyStarBullet*& bullet : bullets)
		bullet = new KirbyStarBullet();
}

void KirbyStarBullet::Shot(Vector2 pos, bool isRight)
{
	for (KirbyStarBullet*& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(pos, isRight);
			return;
		}
	}
}

void KirbyStarBullet::Delete()
{
	for (KirbyStarBullet*& bullet : bullets)
		delete bullet;
}

void KirbyStarBullet::UpdateBullets()
{
	for (KirbyStarBullet*& bullet : bullets)
		bullet->Update();
}

void KirbyStarBullet::RenderBullets(HDC hdc)
{
	for (KirbyStarBullet*& bullet : bullets)
		bullet->Render(hdc);
}

bool KirbyStarBullet::IsBulletsCollision(Rect* rect)
{
	for (KirbyStarBullet* bullet : bullets)
	{
		if (bullet->IsCollision(rect))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

void KirbyStarBullet::SetLandTexture(Texture* texture)
{
	for (KirbyStarBullet* bullet : bullets)
	{
		bullet->landTexture = texture;
	}
}
