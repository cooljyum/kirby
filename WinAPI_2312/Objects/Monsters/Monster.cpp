#include "Framework.h"

Monster::Monster(int x, int y, int hp) : Character()
{
    // HP �� ����
    this->CreateHpBar(Texture::Add(L"Kirby_Resources/UI/MonsterHP.bmp")
        , Texture::Add(L"Kirby_Resources/UI/MonsterHPBottom.bmp")
        , { 600.0f,550.0f });

    // �ʱ� ����
    SetSize(SIZE);
    SetPos(x, y - Half().y);
    SetHp(hp);

    // �ؽ�ó �� �ִϸ��̼� ����
    CreateTexture();
    CreateAnimation();

    // �ִϸ��̼� �ʱ� ����
    animations[IDLE][isRight]->Play();

    // ���� ����
    // ���� ���� �簢��
    traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
    traceRange->SetColor(YELLOW);

    // ���� ���� �簢��
    attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
    attackRange->SetColor(BLUE);

    // ���� �浹ü
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
    // Ȱ�� ���� Ȯ��
    if (!IsActive()) return;

    // �ൿ ���� ���� �� ����
    SetActionState();
    DoAction();

    // �浹 ������ ��Ʈ �浹ü ����
    for (int i = 0; i < hitColliders.size(); i++)
    {
        if (!hitColliders[i]->IsCollision(this))
        {
            hitColliders.erase(hitColliders.begin() + i);
            break;
        }
    }

    // �浹 Ȯ��
    Collision();

    // �ӵ��� ���� �̵�
    Translate(velocity * DELTA);

    // ���� ���� �ִϸ��̼� ������Ʈ
    animations[curState][isRight]->Update();

    // �簢�� ��ġ ������Ʈ
    traceRange->SetPos(pos);
    attackRange->SetPos(pos);

    // �浹ü ��ġ ������Ʈ
    Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
    attackCollider->SetPos(pos + direction * 50.0f - Vector2{ 0.0f, attackCollider->Half().y });

    // �̹��� ��ġ ������Ʈ
    image->SetPos(pos + offset);

    // �߷� ����
    velocity.y += GRAVITY * DELTA;

    float bottom = this->Bottom();
    float pos = landTexture->GetPixelHeight(this->GetPos());
    // �ٴ� ���� �浹 Ȯ�� �� ��ġ ����
    if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
    {
        velocity.y = 0.0f;
        this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
    }

    // ȭ�� ��� �浹 Ȯ�� �� ��ġ ����
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

        // ���� �浹ü ��Ȱ��ȭ
        attackCollider->SetActive(false);
    }

    // ��Ʈ Ÿ�� Ȯ��
    for (Rect* collider : hitColliders)
    {
        if (collider == target)
            return;
    }

    // ��� Ȯ��
    if (IsDie())
        Die();
}

void Monster::CreateTexture()
{
    // �ؽ�ó ����
    leftTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
    rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);

    // �̹��� ����
    image = new Image(rightTexture);
    image->SetTexture(rightTexture);
}

void Monster::CreateAnimation()
{
    // �ִϸ��̼� ��������
    animations.resize(END);

    // ���� �ִϸ��̼�
    animations[IDLE].push_back(new Animation(leftTexture->GetFrame()));
    animations[IDLE].back()->SetPart(2, 2, true);
    animations[IDLE].push_back(new Animation(rightTexture->GetFrame()));
    animations[IDLE].back()->SetPart(2, 2, true);

    // �̵� �ִϸ��̼�
    animations[MOVE].push_back(new Animation(leftTexture->GetFrame()));
    animations[MOVE].back()->SetPart(4, 1, true);
    animations[MOVE].push_back(new Animation(rightTexture->GetFrame()));
    animations[MOVE].back()->SetPart(4, 1, true);

    // ���� �ִϸ��̼�
    animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
    animations[ATTACK].back()->SetPart(5, 9);
    animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
    animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
    animations[ATTACK].back()->SetPart(5, 9);
    animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));

    // ��Ʈ �ִϸ��̼�
    animations[HIT].push_back(new Animation(leftTexture->GetFrame()));
    animations[HIT].back()->SetPart(9, 9);
    animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));
    animations[HIT].push_back(new Animation(rightTexture->GetFrame()));
    animations[HIT].back()->SetPart(9, 9);
    animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));

    // ��� �ִϸ��̼�
    animations[DEAD].push_back(new Animation(leftTexture->GetFrame()));
    animations[DEAD].back()->SetPart(9, 9);
    animations[DEAD].push_back(new Animation(rightTexture->GetFrame()));
    animations[DEAD].back()->SetPart(9, 9);

    // ���� �ִϸ��̼�
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

    // ���� ���� Ȯ��
    if (isStay)
    {
        velocity.x = 0.0f;

        stayTime += DELTA;

        if (stayTime > PATROL_STAY_TIME)
        {
            stayTime = 0.0f;
            isStay = false;
            SetDestPos(); // ������ �ڵ� ����
        }

        SetAnimation(IDLE);

        return;
    }

    // �������� ���� �̵�
    Vector2 direction = destPos - pos;
    velocity.x = direction.Normalized().x * PATROL_SPEED;

    // ���� �Ÿ� �̳��� �����ϸ� ���� ���·� ��ȯ
    constexpr float EPSILON = 2.0f;
    if (direction.Magnitude() < EPSILON)
    {
        isStay = true;
        velocity.x = 0.0f; // �ӵ� �ʱ�ȭ
    }
    else 
    {
        // ���⿡ ���� �ؽ�ó �� �ִϸ��̼� ����
        isRight = velocity.x >= 0;
        isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
        SetAnimation(MOVE);
    }
}

void Monster::Trace()
{
    this->SetActiveHpBar(true);

    // Ÿ���� ���� �̵�
    velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED).x;

    SetDirectionState();

    SetAnimation(MOVE);
}

void Monster::Attack()
{
    if (stayAttackTime <= 0)
    {
        // ����
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
    // ���
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
    // Ÿ���� ��ġ�� ���� ���� ����
    bool isCurRight = target->GetPos().x > pos.x;

    if (isCurRight != isRight)
    {
        isRight = isCurRight;
        SetAnimation(IDLE);
    }
}

void Monster::SetDestPos()
{
    // ��Ʈ�� �Ÿ� ����
    float distance = Random(-PATROL_RANGE, +PATROL_RANGE);

    destPos = pos + Vector2::Right() * distance;

    // ȭ�� ��� ������ ��ġ ����
    if (destPos.x > SCREEN_WIDTH - Half().x)
        destPos.x = SCREEN_WIDTH - Half().x;
    if (destPos.x < Half().x)
        destPos.x = Half().x;

    isRight = distance > 0.0f;
}

void Monster::SetAllActive(bool isActive)
{
    // ��� �簢�� Ȱ��ȭ
    this->SetActive(isActive);
    this->image->SetActive(isActive);
    this->traceRange->SetActive(isActive);
    this->attackRange->SetActive(isActive);
    this->SetActiveHpBar(isActive);
}
