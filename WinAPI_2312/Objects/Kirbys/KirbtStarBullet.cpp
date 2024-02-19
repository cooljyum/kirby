#include "Framework.h"
#include "KirbtStarBullet.h"

vector<KirbtStarBullet*> KirbtStarBullet::bullets;

KirbtStarBullet::KirbtStarBullet() : Image(nullptr)
{
	starTexture = Texture::Add(L"Kirby_Resources/Effect/ShotEffect.bmp", 8, 1, true);

	SetTexture(starTexture);

	animation = new Animation(maxFrame);
	animation->SetDefault(true);

	isActive = false;

	pen = CreatePen(PS_SOLID, 1, MAGENTA);
	animation->SetSpeed(7.0f);
}

KirbtStarBullet::~KirbtStarBullet()
{
	delete animation;
	DeleteObject(pen);
}

void KirbtStarBullet::Update()
{
	if (!isActive) return;

	velocity.x +=  DELTA;

	Translate(velocity * SPEED * DELTA);

	animation->Update();


}

void KirbtStarBullet::Render(HDC hdc)
{
	Image::CamRender(hdc, animation->GetFrame());
}

void KirbtStarBullet::Fire(Vector2 pos, bool isRight)
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

void KirbtStarBullet::CreateBullets()
{
	bullets.resize(SIZE);

	for (KirbtStarBullet*& bullet : bullets)
		bullet = new KirbtStarBullet();
}

void KirbtStarBullet::Shot(Vector2 pos, bool isRight)
{
	for (KirbtStarBullet*& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(pos, isRight);
			return;
		}
	}
}

void KirbtStarBullet::Delete()
{
	for (KirbtStarBullet*& bullet : bullets)
		delete bullet;
}

void KirbtStarBullet::UpdateBullets()
{
	for (KirbtStarBullet*& bullet : bullets)
		bullet->Update();
}

void KirbtStarBullet::RenderBullets(HDC hdc)
{
	for (KirbtStarBullet*& bullet : bullets)
		bullet->Render(hdc);
}

bool KirbtStarBullet::IsBulletsCollision(Rect* rect)
{
	for (KirbtStarBullet* bullet : bullets)
	{
		if (bullet->IsCollision(rect))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

void KirbtStarBullet::SetLandTexture(Texture* texture)
{
	for (KirbtStarBullet* bullet : bullets)
	{
		bullet->landTexture = texture;
	}
}
