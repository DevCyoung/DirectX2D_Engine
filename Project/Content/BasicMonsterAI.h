#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "Components.h"
#include "PathNode.h"
#include "GameManager.h"
#include "PlayerPath.h"
#include "RewindComponent.h"
#include "GameObjectBuilder.h"

enum class eMonsterState
{
	Idle,
	Partrol,
	Turn,
	Walk,
	Trace,
	Attack,
	Aim,
	Whip,
	Fall,
	HurtFly,
	HurtGround,
	Block,
	Dead,
};

enum class eTraceState
{
	None,
	Idle,	
	Walk,
	Run,
	Turn,
	ElevatorEnter,
	ElevatorExit,
};

enum class eAttackState
{
	None,
	Idle,
	Whip,
	Aim,
	Shot,
	Smog,
};

enum class eEmotionState
{
	None,
	Follow,
	Exclaim,
	Question,
};

class BasicMonsterAI : public ScriptComponent
{
public:
	BasicMonsterAI(const eScriptComponentType scriptComponentType);
	virtual ~BasicMonsterAI();
	BasicMonsterAI(const BasicMonsterAI&) = delete;
	BasicMonsterAI& operator=(const BasicMonsterAI&) = delete;

	void SetHandObject(GameObject* const handObject) { Assert(handObject, ASSERT_MSG_NULL); mHandObject = handObject; }
	void SetGunObject(GameObject* const gunObject) { Assert(gunObject, ASSERT_MSG_NULL); mGunObject = gunObject; }
	void SetMonsterType(const eMonsterType monsterType) { mMonsterType = monsterType; }
	void SetEmotion(GameObject* const emotion) { Assert(emotion, ASSERT_MSG_NULL); mEmotion = emotion; }
	void ChangeState(eMonsterState state);
	bool IsDead() { return mbDead; }

	virtual void CreateAnimation(Scene* scene) = 0;
	virtual void CreateGun(Scene* scene) = 0;	

private:
	virtual void initialize() override final;
	virtual void update() override final;
	//virtual void lateUpdate() override final;			
	virtual void onCollisionEnter(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;
	

	void stateUpdate();

	

protected:
	bool isAttackable(const float attackDistacne);
	virtual void trace();
	virtual void idle();
	virtual void walk();
	virtual void turn();
	virtual void aim();
	virtual void whip();
	virtual void partrol();
	virtual void search();
	virtual void block();
	virtual void damaged(Collider2D* other, Vector2 pushOutPower);
	virtual GameObject* createBullet(Vector3 direction, Vector3 position);
	virtual void bleed();

	void dieEnter();
	void liveEnter();

protected:
	PathNode* mPrePlayerPathNode;
	PathNode* mNextElevatorNode;
	GameObject* mHandObject;
	GameObject* mGunObject;
	GameObject* mEmotion;
	Transform* mTransform;
	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;

	float mRunSpeed;
	float mPatrolDitance;

	float mCurIdleTime;
	float mCurWalkTime;

	float mElevatorTime;

	float mShotDelayTime;

	float mEffectTime;

	float mAimAttackableDistance;

	float mBlockTime;

	std::vector<PathNode*> mPath;

	bool mbDead;
	bool mbShield;

	eMonsterState mState;
	eTraceState mTraceState;
	eAttackState mAttackState;
	eMonsterType mMonsterType;
	eEmotionState mEmotionState;
	
};
