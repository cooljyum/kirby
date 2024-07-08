#include "Framework.h"
#include <Scenes/MainScene.h>

vector<Rect*> Kirby::colliders;

bool Kirby::isEatBullet = false; 

Kirby::Kirby() : Character()
{
	//HpBar Set
	CreateHpBar(Texture::Add(L"Kirby_Resources/UI/PlayerHP.bmp") 
								,Texture::Add(L"Kirby_Resources/UI/PlayerHPBottom.bmp")
								, {200.0f,550.0f}, true);
	UpdateHp();

	SetSize(SIZE);
	CreateActions();
	KirbyStarBullet::CreateBullets();
}

Kirby::~Kirby()
{
	delete hpBar;

	KirbyStarBullet::Delete();
}

void Kirby::Update()
{
	actions[curModeState][curActionState]->Update();
	
	Collision();
	Move();
	Control();
	Attack();

	KirbyStarBullet::UpdateBullets();

	//Check Die
	if (IsDie() && curActionState != DIE)
	{
		if (dieStayTime <= 0.0f)
			SetAction(Kirby::DIE, isRight);

		dieStayTime += DELTA;
		return;
	}
}

void Kirby::Render(HDC hdc)
{
	Rect::CamRender(hdc);
	actions[curModeState][curActionState]->Render(hdc);

	KirbyStarBullet::RenderBullets(hdc);

	hpBar->Render(hdc);
}

void Kirby::SetLandTexture(Texture* texture)
{
	float landHeight = texture->GetPixelHeight(GetPos());
	SetPos({ GetPos().x, landHeight - Half().y });

	for (const pair<ModeState, vector<Action*>>& actionList : actions) 
		for (Action* action : actionList.second) 
			action->SetLandTexture(texture);
		
	KirbyStarBullet::SetLandTexture(texture);
}

void Kirby::Move()
{
	
	bool isMove = false;
	bool isRun = false;

	if (KEY->Press('D'))
	{
		isMove = true;
		isRight = true;
	}
	if (KEY->Press('A'))
	{
		isMove = true;
		isRight = false;
	}

	if (curActionState == JUMPUP || curActionState == JUMPDOWN || curActionState == SIT 
		|| curActionState == ATTACK || curActionState == HIT || curActionState == DIE || curActionState == DANCE) return;
	isMove ?  SetAction(WALK, isRight) : SetIdle();
}

void Kirby::Control()
{
	if (curActionState == DIE || curActionState == DANCE) return;

	if (KEY->Down('W') && curActionState != JUMPUP && curActionState != JUMPDOWN)
	{
		SOUND->Play("Jump", 0.2f);
		EffectManager::Get()->Play("kirbyEffect", pos);
		SetAction(JUMPUP, isRight);
	}

	if (KEY->Down('S') && curActionState != JUMPUP && curActionState != JUMPDOWN) 
	{
		SetAction(SIT, isRight);
	}
	
	if (KEY->Down('S') && curActionState != JUMPUP && curActionState != JUMPDOWN)
	{
		SetAction(SIT, isRight);
	}

	if (KEY->Up('S') && curActionState == SIT && curModeState == DEFAULT) {
		SetIdle();
	}
}

void Kirby::Attack()
{
	if (curActionState == JUMPUP || curActionState == JUMPDOWN || curActionState == SIT || curActionState == ATTACK || curActionState == DIE) return;

	if (KEY->Down('F'))
	{
		SetAction(ATTACK, isRight);
	}
	
}

void Kirby::Hit()
{
	SetAction(Kirby::HIT, isRight);
	isHit = false;
}

void Kirby::Die()
{
	SetAction(Kirby::DIE, isRight);
}

void Kirby::CreateActions()
{
	CreateModeAction(DEFAULT);
	CreateModeAction(EAT);
}

void Kirby::CreateModeAction(ModeState mode)
{
	if (mode == DEFAULT) 
	{ 
		actions[mode].push_back(new KirbyIdle(this));
		actions[mode].push_back(new KirbyWalk(this));
		actions[mode].push_back(new KirbySit(this));
		actions[mode].push_back(new KirbyInhole(this));
		actions[mode].push_back(new KirbyJumpUp(this));
		actions[mode].push_back(new KirbyJumpDown(this));
		actions[mode].push_back(new KirbyHit(this));
		actions[mode].push_back(new KirbyDie(this));
		actions[mode].push_back(new KirbyDance(this));
	}
	
	if (mode == EAT) 
	{ 
		actions[mode].push_back(new KirbyIdleEat(this)); 
		actions[mode].push_back(new KirbyWalkEat(this));
		actions[mode].push_back(new KirbySitEat(this));
		actions[mode].push_back(new KirbyAttackEat(this));
		actions[mode].push_back(new KirbyJumpUpEat(this));
		actions[mode].push_back(new KirbyJumpDownEat(this));
		actions[mode].push_back(new KirbyHit(this));
		actions[mode].push_back(new KirbyDie(this));
		actions[mode].push_back(new KirbyDance(this));
	}

	actions[mode][HIT]->GetAnimation(0)->SetEndEvent([this]() {
			SetMode(DEFAULT); SetIdle();
		});

	actions[mode][HIT]->GetAnimation(1)->SetEndEvent([this]() {
			SetMode(DEFAULT); SetIdle();
		});
	
	actions[mode][ATTACK]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT ) {
			SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][ATTACK]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT ) {
			SetMode(DEFAULT); SetIdle();
		}});

	
	actions[mode][SIT]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT ) { 
			SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][SIT]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT ) {  
			SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][DANCE]->GetAnimation(0)->SetEndEvent([this]() {SetMode(DEFAULT); SetIdle();});
	actions[mode][DANCE]->GetAnimation(1)->SetEndEvent([this]() {SetMode(DEFAULT); SetIdle();});

}

void Kirby::SetIdle()
{
	if (curModeState == DEFAULT) SetAction(IDLE, isRight);
	if (curActionState == IDLE) return;
	SetAction(IDLE, isRight,true);
}

void Kirby::SetAction(ActionState state, bool isRight, bool isForce)
{
	if (!isForce && curActionState == state)
		return;

	actions[curModeState][curActionState]->End();
	curActionState = state;
	actions[curModeState][state]->Start(isRight);
}

void Kirby::Collision()
{
	//Door
	MapItem* door = MapItemManager::Get()->Collision("Door", this);

	//When Door Touch
	if (door != nullptr)
		if (KEY->Down('W')) 
		{
			SOUND->Play("Door");
			MainScene::kirbyHpSave = GetHp();
			SCENE->ChangeScene("Boss");
		}

	//Treasure
	MapItem* treasure = MapItemManager::Get()->Collision("Treasure", this);

	//When Treasure Touch
	if (treasure != nullptr) 
	{
		SOUND->Play("Door");
		treasure->SetActive(false);
		MapItemManager::Get()->Play("TreasureOpen", treasure->GetPos());
	}

	MapItem* treasureOpen = MapItemManager::Get()->Collision("TreasureOpen", this);
	//When Treasure Touch
	if (treasureOpen != nullptr)
	{
		if (KEY->Down('W')) 
			SCENE->ChangeScene("End");
	}
	
	Monster* monster = MonsterManager::Get()->Collision(this);
	if (monster != nullptr)
	{
		if (curActionState == ATTACK) return;
		if (monster->GetState() == Monster::HIT) return;

		monster->DamageHp(DEMAGE_MONSTER);

		Vector2 direction = isRight ? Vector2::Right() : Vector2::Left(); 
		Vector2 velocity = { direction.x * PUSH_FORCE , 0.0f };

		monster->Hit();
		monster->SetVelocity(velocity);
			
		DamageHp(ATTACK_MONSTER);
		Hit();
	}

}

void Kirby::AddCollider(Rect* collider)
{
	colliders.push_back(collider);
}

Rect* Kirby::AttackCollision(Rect* rect)
{
	for (Rect* collider : colliders)
	{
		if (collider->IsCollision(rect))
			return collider;
	}

	return nullptr;
}

void Kirby::Dance()
{
	SetAction(Kirby::DANCE, isRight);
}
