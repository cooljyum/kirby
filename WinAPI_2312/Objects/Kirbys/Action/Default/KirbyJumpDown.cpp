#include "Framework.h"

KirbyJumpDown::KirbyJumpDown(Rect* owner) : KirbyJump(owner)
{
	//Tex, ANi Set
	//Tex
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);
	
	//Ani
	AddAnimation(LEFT)->SetPart(77, 67);
	AddAnimation(RIGHT)->SetPart(77, 67);

	//Ani Speed Setting
	GetAnimation(LEFT)->SetSpeed(2.3f);
	GetAnimation(RIGHT)->SetSpeed(2.3f);
}

KirbyJumpDown::~KirbyJumpDown()
{
}

void KirbyJumpDown::Jump()
{
	//Extend Jump
	KirbyJump::Jump();

	//Bottom Check
	landHeight = landTexture->GetPixelHeight(owner->GetPos());

	//When bottom and land touch
	if (owner->Bottom() > landHeight)
	{
		//velocity init
		velocity.y = 0.0f; 

		//Owner Pos Setting (Above landHeight)
		owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });

		//Downcasting
		Kirby* kirby = (Kirby*)owner;

		//Kirby Idle
		kirby->SetIdle();

		//여기서 질문이 다운 캐스팅 하는데 이왕할거면 이게 낫나
		//Downcasting
		/*
		Kirby* kirby = (Kirby*)owner;

		kirby->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
		kirby->SetIdle();
		*/

		//쓸모 x
		// Hit 기능 넣다가 ..
		//if (!kirby->GetIsHit())
		//	kirby->SetIdle();
		//else
		//	kirby->Hit();
	}
}
