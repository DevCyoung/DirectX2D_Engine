#include "pch.h"
#include "HeadHunterAI.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "GameObjectBuilder.h"
#include "HeadHunterLazer.h"

#include "HeadHunterBoomShot.h"
#include "HeadHunterIdle.h"
#include "HeadHunterSwordDash.h"
#include "HeadHunterAim.h"
#include "HeadHunterSweep.h"
#include "HeadHunterTeleport.h"
#include "TeleportGround.h"
#include "HeadHunterWallJump.h"
#include "HeadHunterSwordDash.h"
#include "HeadHunterRoll.h"
#include "HeadHunterHurt.h"
#include "HeadHunterPreJump.h"
#include "HeadHunterDie.h"

#include "MonsterAttack.h"

#include "FolowPlayer.h"

#include <Engine/EngineMath.h>
#include <Engine/AfterImage.h>

#include "HeadHunterBullet.h"

#include "BulletMovement.h"

HeadHunterAI::HeadHunterAI()
    : ScriptComponent(eScriptComponentType::HeadHunterAI)
    , mFSM(nullptr)
    , mHand(nullptr)
    , mHP(3)
{    
}

HeadHunterAI::~HeadHunterAI()
{
    DELETE_POINTER_NOT_NULL(mFSM);
}

void HeadHunterAI::CreateAnimation()
{
    Animator2D* const anim = GetOwner()->GetComponent<Animator2D>();
    Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_HeadHunter_headHunet);

    anim->CreateAnimation(L"spr_headhunter_afterhurt", atlas, 2, XMUINT2(5, 34), XMUINT2(70, 53), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_afterhurt_smoke", atlas, 2, XMUINT2(5, 126), XMUINT2(70, 53), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);    
    anim->CreateAnimation(L"spr_headhunter_bomb_run", atlas, 8, XMUINT2(5, 371), XMUINT2(44, 38), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_dead", atlas, 19, XMUINT2(5, 534), XMUINT2(56, 21), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    
    

    

    anim->CreateAnimation(L"spr_headhunter_exit_door", atlas, 3, XMUINT2(5, 852), XMUINT2(21, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_hat_hurtfly", atlas, 7, XMUINT2(5, 934), XMUINT2(13, 12), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_hat_hurtground", atlas, 3, XMUINT2(5, 985), XMUINT2(16, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_head_hurtfly", atlas, 8, XMUINT2(5, 1031), XMUINT2(20, 21), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_head_hurtground", atlas, 8, XMUINT2(5, 1091), XMUINT2(45, 14), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    anim->CreateAnimation(L"spr_headhunter_hurt", atlas, 10, XMUINT2(5, 1144), XMUINT2(70, 53), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_hurtfly", atlas, 4, XMUINT2(5, 1299), XMUINT2(42, 26), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_hurtground", atlas, 6, XMUINT2(5, 1364), XMUINT2(50, 27), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    
    anim->CreateAnimation(L"spr_headhunter_mask1_hurtfly", atlas, 7, XMUINT2(5, 1513), XMUINT2(13, 15), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_mask1_hurtground", atlas, 3, XMUINT2(5, 1567), XMUINT2(22, 10), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_mask2_hurtfly", atlas, 8, XMUINT2(5, 1616), XMUINT2(11, 10), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_mask2_hurtground", atlas, 4, XMUINT2(5, 1665), XMUINT2(27, 5), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_nohead", atlas, 6, XMUINT2(5, 1709), XMUINT2(60, 22), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);    
    anim->CreateAnimation(L"spr_headhunter_prejump", atlas, 3, XMUINT2(5, 1852), XMUINT2(33, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    
    anim->CreateAnimation(L"spr_headhunter_recover", atlas, 4, XMUINT2(5, 2098), XMUINT2(70, 53), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_reveal_bomb", atlas, 8, XMUINT2(5, 2190), XMUINT2(38, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    anim->CreateAnimation(L"DieFly", atlas, 4, XMUINT2(5, 625), XMUINT2(41, 26), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"DieLand", atlas, 8, XMUINT2(5, 690), XMUINT2(58, 41), XMUINT2(10, 10), XMINT2(0, -1), 0.125f);

    anim->CreateAnimation(L"PreJump", atlas, 3, XMUINT2(5, 1852), XMUINT2(33, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"Jump", atlas, 1, XMUINT2(5, 3953), XMUINT2(27, 44), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    anim->CreateAnimation(L"Hurt", atlas, 10, XMUINT2(5, 1144), XMUINT2(70, 53), XMUINT2(10, 10), XMINT2(0, 5), 0.125f);
    anim->CreateAnimation(L"HurtFly", atlas, 4, XMUINT2(5, 1299), XMUINT2(42, 26), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"HurtGround", atlas, 6, XMUINT2(5, 1364), XMUINT2(50, 27), XMUINT2(10, 10), XMINT2(0, 4), 0.125f);

    anim->CreateAnimation(L"Roll", atlas, 7, XMUINT2(5, 770), XMUINT2(60, 43), XMUINT2(10, 10), XMINT2(20, 0), 0.125f);

    anim->CreateAnimation(L"TakeOutRifle", atlas, 8, XMUINT2(5, 2580), XMUINT2(38, 43), XMUINT2(10, 10), XMINT2(3, 0), 0.05f);
    anim->CreateAnimation(L"PutBackRifle", atlas, 8, XMUINT2(5, 2016), XMUINT2(38, 43), XMUINT2(10, 10), XMINT2(3, 0), 0.05f);

    anim->CreateAnimation(L"PreDash", atlas, 8, XMUINT2(5, 1770), XMUINT2(57, 43), XMUINT2(10, 10), XMINT2(9, 0), 0.06f);
    anim->CreateAnimation(L"DashEndGround", atlas, 10, XMUINT2(5, 448), XMUINT2(50, 47), XMUINT2(10, 10), XMINT2(9, 2), 0.08f);
    anim->CreateAnimation(L"Dash", atlas, 1, XMUINT2(5, 3659), XMUINT2(51, 25), XMUINT2(10, 10), XMINT2(0, -9), 0.06f);
    anim->CreateAnimation(L"DashSlownDown", atlas, 1, XMUINT2(5, 3723), XMUINT2(42, 29), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);

    anim->CreateAnimation(L"TakeOutGun", atlas, 7, XMUINT2(5, 2498), XMUINT2(47, 43), XMUINT2(10, 10), XMINT2(6, 0), 0.08f);
    anim->CreateAnimation(L"PutBackGun", atlas, 7, XMUINT2(5, 1934), XMUINT2(47, 43), XMUINT2(10, 10), XMINT2(6, 0), 0.08f);

    anim->CreateAnimation(L"Idle", atlas, 12, XMUINT2(5, 1430), XMUINT2(22, 44), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"Shoot", atlas, 8, XMUINT2(5, 2272), XMUINT2(68, 46), XMUINT2(10, 10), XMINT2(19, 1), 0.06f);
    anim->CreateAnimation(L"Aim", atlas, 19, XMUINT2(5, 218), XMUINT2(39, 52), XMUINT2(10, 10), XMINT2(1, 2), 0.06f);
    anim->CreateAnimation(L"Sweep", atlas, 18, XMUINT2(5, 2357), XMUINT2(59, 46), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"SweepIn", atlas, 4, XMUINT2(5, 2820), XMUINT2(59, 46), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"SweepOut", atlas, 4, XMUINT2(5, 3063), XMUINT2(59, 46), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);

    anim->CreateAnimation(L"TeleportIn", atlas, 4, XMUINT2(5, 2662), XMUINT2(28, 45), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"TeleportOut", atlas, 5, XMUINT2(5, 2905), XMUINT2(28, 45), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);

    anim->CreateAnimation(L"TeleportInGround", atlas, 4, XMUINT2(5, 2746), XMUINT2(41, 35), XMUINT2(10, 10), XMINT2(0, -3), 0.06f);
    anim->CreateAnimation(L"TeleportOutGround", atlas, 5, XMUINT2(5, 2989), XMUINT2(41, 35), XMUINT2(10, 10), XMINT2(0, -3), 0.06f);

    anim->CreateAnimation(L"WallIdle", atlas, 3, XMUINT2(5, 3413), XMUINT2(30, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"WallJump", atlas, 7, XMUINT2(5, 3230), XMUINT2(54, 62), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
    anim->CreateAnimation(L"WallJumpLand", atlas, 4, XMUINT2(5, 3331), XMUINT2(33, 43), XMUINT2(10, 10), XMINT2(4, 0), 0.06f);

    anim->CreateAnimation(L"Invisible", atlas, 1, XMUINT2(5, 3850), XMUINT2(64, 64), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    
    anim->CreateAnimation(L"spr_headhunter_walk", atlas, 8, XMUINT2(5, 3148), XMUINT2(25, 43), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    anim->CreateAnimation(L"spr_player_use_headhunter", atlas, 30, XMUINT2(5, 3495), XMUINT2(47, 35), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_headhunter_head", atlas, 1, XMUINT2(5, 3791), XMUINT2(36, 20), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    
    
    anim->CreateAnimation(L"spr_headhunter_smallhead", atlas, 1, XMUINT2(5, 4036), XMUINT2(14, 9), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    {
        Animation2D* animation = anim->FindAnimationOrNull(L"Shoot");
        std::function<void()> func = [this]() {        
            gSoundManager->Play(eResAudioClip::HeadHunter_headHunterShot, 0.45f);

            GameObject* bullet =  CreateBullet();
            Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
            Vector3 right = GetOwner()->GetComponent<Transform>()->GetRight();

            right.y = 0.7f;
            Vector2 dir = Vector2(right.x, right.y);

            int randBulletX = helper::rand::RandInt(700, 1200);
            int randBulletY = helper::rand::RandInt(-200, 800);

            dir.x = static_cast<float>(randBulletX);
            dir.y = static_cast<float>(randBulletY);


            if (right.x < 0.f)
            {
                dir.x *= -1.f;
            }
				

            bullet->GetComponent<Rigidbody2D>()->SetVelocity(dir );

            position.x += right.x * 50.f;
            position.y += 28.f;
            bullet->GetComponent<Transform>()->SetPosition(position);

            GetOwner()->GetGameSystem()->GetScene()->RegisterEventAddGameObject(bullet, eLayerType::Default);
        };
        animation->SetFrameStartEvent(2, func);
    }
}

GameObject* HeadHunterAI::CreateHand()
{
    //Hand
    GameObject* const hand = new GameObject();

    hand->GetComponent<Transform>()->SetPosition(-4.f, 2.f, 0.f);
    hand->SetName(L"hand");
    hand->SetParent(GetOwner());
    
    return hand;    
}

GameObject* HeadHunterAI::CreateLazer()
{
    //Lazer
    GameObject* const lazerMask = GameObjectBuilder::Default2D(L"LazerMask");
    lazerMask->AddComponent<HeadHunterLazer>();
    lazerMask->AddComponent<RectCollider2D>();
    lazerMask->AddComponent<MonsterAttack>();

    lazerMask->GetComponent<RectCollider2D>()->SetSize(1000.f, 20.f);
    lazerMask->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

    lazerMask->GetComponent<Transform>()->SetPosition(527.f, 3.f, 0.f);    
    return lazerMask;
}

GameObject* HeadHunterAI::CreateBullet()
{
    //Lazer
    GameObject* const bullet = GameObjectBuilder::Default2D(L"HeadHunterBullet");
    
    bullet->AddComponent<HeadHunterLazer>();
    bullet->AddComponent<RectCollider2D>();
    bullet->AddComponent<MonsterAttack>();    
    bullet->AddComponent<HeadHunterBullet>();
    bullet->AddComponent<Rigidbody2D>();
    bullet->AddComponent<Light2D>();        

    bullet->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
    bullet->GetComponent<Light2D>()->SetRadius(80.f);
    bullet->GetComponent<Light2D>()->SetLightDiffuse(Vector3(7.5f, 0.1f, 0.1f));    

    //bullet->GetComponent<Transform>()->SetPosition(-2000, 520, 0);

    GameObject* circleLine = GameObjectBuilder::Default2D(L"HeadHunterBulletCircleLine");    
    circleLine->SetParent(bullet);
    GetOwner()->GetGameSystem()->GetScene()->RegisterEventAddGameObject(circleLine, eLayerType::Default);
    bullet->GetComponent<HeadHunterBullet>()->SetCircle(circleLine);
    
    bullet->GetComponent<RectCollider2D>()->SetSize(10.f, 10.f);    
    return bullet;
}

void HeadHunterAI::onCollisionEnter(Collider2D* other)
{
    if (other->GetOwner()->GetLayer() == eLayerType::PlayerAttack &&
        mFSM->GetCurentStateType() != HeadHunterAI::Hurt &&
        mFSM->GetCurentStateType() != HeadHunterAI::Roll)
    {
        --mHP;

        Camera* const mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
        mainCamera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();

        Vector2 pushOutPower = Vector2(600.f, 500.f);

        if (mHP <= 0)
        {
            mFSM->ChangeState(HeadHunterAI::Die);
            pushOutPower = Vector2(700.f, 800.f);
        }
        else
        {
            mFSM->ChangeState(HeadHunterAI::Hurt);            
            GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f, eTimeEffectType::Damaged);

            gSoundManager->Play(eResAudioClip::enemySlice, 1.f);          
        }        

        Vector3 dir = other->GetOwner()->GetComponent<Transform>()->GetRight();
        eLayerType otherLayerType = other->GetOwner()->GetLayer();
        

        float degreeAngle = helper::math::GetAngle2D(dir);
        gEffectManager->Slash(GetOwner()->GetComponent<Transform>()->GetPosition(), degreeAngle, 0.f);

        if (otherLayerType == eLayerType::PlayerAttack)
        {

            dir.x *= pushOutPower.x;
            dir.y *= pushOutPower.y;
            GetOwner()->GetComponent<Rigidbody2D>()->SetVelocity(Vector2(dir.x, dir.y));


        }
    }

    (void)other;
}

void HeadHunterAI::initialize()
{
    mFSM = new MonsterFSM(GetOwner());

    mFSM->AddState(HeadHunterAI::Idle, new HeadHunterIdle);
    mFSM->AddState(HeadHunterAI::TelportShot, new HeadHunterTeleport);
    mFSM->AddState(HeadHunterAI::Sweep, new HeadHunterSweep);
    mFSM->AddState(HeadHunterAI::Aim, new HeadHunterAim);
    mFSM->AddState(HeadHunterAI::BoomShot, new HeadHunterBoomShot);
    mFSM->AddState(HeadHunterAI::TelportShotGround, new TeleportGround);
    mFSM->AddState(HeadHunterAI::WallJump, new HeadHunterWallJump);
    mFSM->AddState(HeadHunterAI::LandDash, new HeadHunterSwordDash);
    mFSM->AddState(HeadHunterAI::Roll, new HeadHunterRoll);
    mFSM->AddState(HeadHunterAI::Hurt, new HeadHunterHurt);
    mFSM->AddState(HeadHunterAI::PreJump, new HeadHunterPreJump);
    mFSM->AddState(HeadHunterAI::Die, new HeadHunterDie);
        
    mFSM->Initialize(HeadHunterAI::eState::Idle);

    GetOwner()->GetComponent<AfterImage>()->SetColorR(153.f / 255.f);
    GetOwner()->GetComponent<AfterImage>()->SetColorG(50.f / 255.f);
    GetOwner()->GetComponent<AfterImage>()->SetColorB(204.f / 255.f);
}

void HeadHunterAI::update()
{
    if (GameManager::GetInstance()->GetRewindManager()->GetRewindState() != eRewindState::Record)
    {
        return;
    }

    mFSM->GlobalUpdate();
    mFSM->Update();
}

void HeadHunterAI::lateUpdate()
{
}
