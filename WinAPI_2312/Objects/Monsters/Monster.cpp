#include "Framework.h"

Monster::Monster(int x, int y, int hp) : Character()
{
    // HP 바 설정
    this->CreateHpBar(Texture::Add(L"Kirby_Resources/UI/MonsterHP.bmp")
        , Texture::Add(L"Kirby_Resources/UI/MonsterHPBottom.bmp")
        , { 600.0f,550.0f });

    // 초기 설정
    SetSize(SIZE);
    SetPos(x, y - Half().y);
    SetHp(hp);

    // 텍스처 및 애니메이션 설정
    CreateTexture();
    CreateAnimation();

    // 애니메이션 초기 설정
    animations[IDLE][isRight]->Play();

    // 범위 설정
    // 추적 범위 사각형
    traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
    traceRange->SetColor(YELLOW);

    // 공격 범위 사각형
    attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
    attackRange->SetColor(BLUE);

    // 공격 충돌체
    attackCollider = new Rect(Vector2(), Vector2(50, 50));
    attackCollider->SetColor(RED);
    attackCollider->SetActive(false);
}

Monster::~Monster()
{
    delete hpBar;

    for (vector<Animation*> animationArray : animations)
    {
        delete animationArray[0];
        delete animationArray[1];
    }
}

void Monster::Update()
{
    // 활성 상태 확인
    if (!IsActive()) return;

    // 행동 상태 설정 및 실행
    SetActionState();
    DoAction();

    // 충돌 해제된 히트 충돌체 제거
    for (int i = 0; i < hitColliders.size(); i++)
    {
        if (!hitColliders[i]->IsCollision(this))
        {
            hitColliders.erase(hitColliders.begin() + i);
            break;
        }
    }

    // 충돌 확인
    Collision();

    // 속도에 따라 이동
    Translate(velocity * DELTA);

    // 현재 상태 애니메이션 업데이트
    animations[curState][isRight]->Update();

    // 사각형 위치 업데이트
    traceRange->SetPos(pos);
    attackRange->SetPos(pos);

    // 충돌체 위치 업데이트
    Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
    attackCollider->SetPos(pos + direction * 50.0f - Vector2{ 0.0f, attackCollider->Half().y });

    // 이미지 위치 업데이트
    image->SetPos(pos + offset);

    // 중력 설정
    velocity.y += GRAVITY * DELTA;

    float bottom = this->Bottom();
    float pos = landTexture->GetPixelHeight(this->GetPos());
    // 바닥 지형 충돌 확인 및 위치 조정
    if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
    {
        velocity.y = 0.0f;
        this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
    }

    // 화면 경계 충돌 확인 및 위치 조정
    if (this->Left() < 0.0f)
    {
        this->SetPos({ this->Half().x ,this->GetPos().y });
        return;
    }
}

void Monster::Render(HDC hdc)
{
    CamRender(hdc);
    traceRange->CamRender(hdc);
    attackRange->CamRender(hdc);
    attackCollider->CamRender(hdc);

    image->CamRender(hdc, animations[curState][isRight]->GetFrame());

    hpBar->Render(hdc);
}

void Monster::InHaled()
{
    SetAnimation(INHALED);
}

void Monster::Hit()
{
    SetAnimation(HIT);
    actionState = ActionState::HIT;
}

void Monster::SetActionState()
{
    if (actionState == ActionState::HIT) return;

    if (attackRange->IsCollision(target))
    {
        actionState = ActionState::ATTACK;
    }
    else if (traceRange->IsCollision(target))
    {
        actionState = ActionState::TRACE;
    }
    else
    {
        actionState = ActionState::PATROL;
    }
}

void Monster::SetIdle()
{
    SetAnimation(IDLE);
    actionState = ActionState::PATROL;
}

void Monster::Collision()
{
    if (curState == HIT)
        return;

    if (KirbyStarBullet::IsBulletsCollision(this))
    {
        this->DamageHp(8);

        MonsterManager::Get()->SetOffAllHpBar();
        this->SetActiveHpBar(true);

        SetAnimation(HIT);
        actionState = ActionState::HIT;
    }

    if (attackCollider->IsCollision(target))
    {
        target->DamageHp(1);

        Kirby* kirby = (Kirby*)target;
        kirby->Hit();

        // 공격 충돌체 비활성화
        attackCollider->SetActive(false);
    }

    // 히트 타겟 확인
    for (Rect* collider : hitColliders)
    {
        if (collider == target)
            return;
    }

    // 사망 확인
    if (IsDie())
        Die();
}

void Monster::CreateTexture()
{
    // 텍스처 설정
    leftTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
    rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);

    // 이미지 설정
    image = new Image(rightTexture);
    image->SetTexture(rightTexture);
}

void Monster::CreateAnimation()
{
    // 애니메이션 리사이즈
    animations.resize(END);

    // 정지 애니메이션
    animations[IDLE].push_back(new Animation(leftTexture->GetFrame()));
    animations[IDLE].back()->SetPart(2, 2, true);
    animations[IDLE].push_back(new Animation(rightTexture->GetFrame()));
    animations[IDLE].back()->SetPart(2, 2, true);

    // 이동 애니메이션
    animations[MOVE].push_back(new Animation(leftTexture->GetFrame()));
    animations[MOVE].back()->SetPart(4, 1, true);
    animations[MOVE].push_back(new Animation(rightTexture->GetFrame()));
    animations[MOVE].back()->SetPart(4, 1, true);

    // 공격 애니메이션
    animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
    animations[ATTACK].back()->SetPart(5, 9);
    animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
    animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
    animations[ATTACK].back()->SetPart(5, 9);
    animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));

    // 히트 애니메이션
    animations[HIT].push_back(new Animation(leftTexture->GetFrame()));
    animations[HIT].back()->SetPart(9, 9);
    animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));
    animations[HIT].push_back(new Animation(rightTexture->GetFrame()));
    animations[HIT].back()->SetPart(9, 9);
    animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));

    // 사망 애니메이션
    animations[DEAD].push_back(new Animation(leftTexture->GetFrame()));
    animations[DEAD].back()->SetPart(9, 9);
    animations[DEAD].push_back(new Animation(rightTexture->GetFrame()));
    animations[DEAD].back()->SetPart(9, 9);

    // 흡입 애니메이션
    animations[INHALED].push_back(new Animation(leftTexture->GetFrame()));
    animations[INHALED].back()->SetPart(9, 9);
    animations[INHALED].push_back(new Animation(rightTexture->GetFrame()));
    animations[INHALED].back()->SetPart(9, 9);
}

void Monster::SetAnimation(AnimationState state)
{
    if (curState == state) return;

    curState = state;
    isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
    animations[state][isRight]->Play();
}

void Monster::DoAction()
{
    if (curState == INHALED) return;

    switch (actionState)
    {
    case Monster::ActionState::PATROL:
        Patrol();
        break;
    case Monster::ActionState::TRACE:
        Trace();
        break;
    case Monster::ActionState::ATTACK:
        Attack();
        break;
    }
}

void Monster::Patrol()
{
    this->SetActiveHpBar(false);

    // 정지 상태 확인
    if (isStay)
    {
        velocity.x = 0.0f;

        stayTime += DELTA;

        if (stayTime > PATROL_STAY_TIME)
        {
            stayTime = 0.0f;
            isStay = false;
            SetDestPos(); // 목적지 자동 설정
        }

        SetAnimation(IDLE);

        return;
    }

    // 목적지를 향해 이동
    Vector2 direction = destPos - pos;
    velocity.x = direction.Normalized().x * PATROL_SPEED;

    // 일정 거리 이내에 도달하면 정지 상태로 전환
    constexpr float EPSILON = 2.0f;
    if (direction.Magnitude() < EPSILON)
    {
        isStay = true;
        velocity.x = 0.0f; // 속도 초기화
    }
    else 
    {
        // 방향에 따라 텍스처 및 애니메이션 설정
        isRight = velocity.x >= 0;
        isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
        SetAnimation(MOVE);
    }
}

void Monster::Trace()
{
    this->SetActiveHpBar(true);

    // 타겟을 향해 이동
    velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED).x;

    SetDirectionState();

    SetAnimation(MOVE);
}

void Monster::Attack()
{
    if (stayAttackTime <= 0)
    {
        // 공격
        stayAttackTime = ATTACK_STAY_TIME;

        attackCollider->SetActive(true);

        velocity = {};

        SetDirectionState();

        SetAnimation(ATTACK);
    }
    stayAttackTime -= DELTA;
}

void Monster::Die()
{
    // 사망
    SetAnimation(DEAD);

    stayDieTime += DELTA;
    if (stayDieTime > DIE_STAY_TIME)
    {
        SOUND->Play("MonsterDie");
        stayDieTime = 0.0f;
        SetAllActive(false);
    }
}

void Monster::SetDirectionState()
{
    // 타겟의 위치에 따라 방향 설정
    bool isCurRight = target->GetPos().x > pos.x;

    if (isCurRight != isRight)
    {
        isRight = isCurRight;
        SetAnimation(IDLE);
    }
}

void Monster::SetDestPos()
{
    // 패트롤 거리 설정
    float distance = Random(-PATROL_RANGE, +PATROL_RANGE);

    destPos = pos + Vector2::Right() * distance;

    // 화면 경계 내에서 위치 조정
    if (destPos.x > SCREEN_WIDTH - Half().x)
        destPos.x = SCREEN_WIDTH - Half().x;
    if (destPos.x < Half().x)
        destPos.x = Half().x;

    isRight = distance > 0.0f;
}

void Monster::SetAllActive(bool isActive)
{
    // 모든 사각형 활성화
    this->SetActive(isActive);
    this->image->SetActive(isActive);
    this->traceRange->SetActive(isActive);
    this->attackRange->SetActive(isActive);
    this->SetActiveHpBar(isActive);
}
