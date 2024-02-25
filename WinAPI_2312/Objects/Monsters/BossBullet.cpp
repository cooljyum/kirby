#include "Framework.h"
#include "BossBullet.h"

vector<BossBullet*> BossBullet::bullets;

BossBullet::BossBullet() : Image(nullptr)
{ 
	//Boss Bullet Set
	starTexture = Texture::Add(L"Kirby_Resources/Effect/ShotEffect.bmp", 8, 1, true);

	SetTexture(starTexture);

	animation = new Animation(maxFrame);
	animation->SetDefault(true);

	isActive = false;

	pen = CreatePen(PS_SOLID, 1, MAGENTA);
	animation->SetSpeed(1.0f);
}

BossBullet::~BossBullet()
{
	delete animation;
	DeleteObject(pen);
}

void BossBullet::Update()
{
	if (!isActive) return;

	Translate({ velocity.x * SPEED * DELTA, 0.0f });

	animation->Update();

}

void BossBullet::Render(HDC hdc)
{
	Image::CamRender(hdc, animation->GetFrame());
}

void BossBullet::Fire(Vector2 pos, bool isRight)
{
	isActive = true;
	this->isRight = isRight;
	SetTexture(starTexture);

	velocity = {};

	animation->Play();

	SetPos(pos);

	EffectManager::Get()->Play("StarEffect",this->GetPos());
}

void BossBullet::init()
{
	for (BossBullet*& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->SetActive(false);
		}
	}
}

void BossBullet::CreateBullets()
{
	bullets.resize(SIZE);

	for (BossBullet*& bullet : bullets)
		bullet = new BossBullet();
}

void BossBullet::Shot(Vector2 pos, bool isRight)
{
	for (BossBullet*& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(pos, isRight);
			return;
		}
	}
}

void BossBullet::Delete()
{
	for (BossBullet*& bullet : bullets)
		delete bullet;
}

void BossBullet::UpdateBullets()
{
	for (BossBullet*& bullet : bullets)
		bullet->Update();
}

void BossBullet::RenderBullets(HDC hdc)
{
	for (BossBullet*& bullet : bullets)
		bullet->Render(hdc);
}

bool BossBullet::IsBulletsCollision(Rect* rect)
{
	for (BossBullet* bullet : bullets)
	{
		if (bullet->IsCollision(rect))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

BossBullet* BossBullet::Collision(Rect* rect)
{
	for (BossBullet*& bullet : bullets)
	{
		if (bullet->IsCollision(rect))
			return bullet;
	}

	return nullptr;
}

void BossBullet::SetLandTexture(Texture* texture)
{
	for (BossBullet* bullet : bullets)
	{
		bullet->landTexture = texture;
	}
}
