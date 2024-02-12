#include "Framework.h"
#include "ShootingGameScene.h"

ShootingGameScene::ShootingGameScene()
{
	plane = new Plane();
	EnemyManager::Get()->SetTarget(plane);
}

ShootingGameScene::~ShootingGameScene()
{
	delete plane;

	BulletManager::Delete();
	EnemyManager::Delete();
}

void ShootingGameScene::Update()
{
	plane->Update();
	BulletManager::Get()->Update();
	EnemyManager::Get()->Update();
}

void ShootingGameScene::Render(HDC hdc)
{
	plane->Render(hdc);
	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);
}
