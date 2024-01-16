#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(KissyfaceAI);

class Animator2D;
class Rigidbody2D;

enum class eKissyfaceAIState
{
	None,
	Ready,
	ToBattle,
	

	Idle,
	
	Hurt,	

	Block,

	Slash, // 1

	PreJump, //2
	Jump, 
	JumpSwing,
	LandAttack,

	PreLunge, // 3
	Lunge,
	LungeAttack,

	Throw,
	Tug,
	ReturnAxe,

	

	Recover,

	Struggle,
	
	Slice,

	Dead,

	NoHead,
};

class KissyfaceAI : public ScriptComponent
{
public:
	KissyfaceAI();
	virtual ~KissyfaceAI();
	KissyfaceAI(const KissyfaceAI&) = delete;
	KissyfaceAI& operator=(const KissyfaceAI&) = delete;


	void SetAxe(GameObject* const axe) { Assert(axe, ASSERT_MSG_NULL); mAxe = axe; }
	void SetBrokenAxe(GameObject* const brokenAxe) { Assert(brokenAxe, ASSERT_MSG_NULL); mBrokenAxe = brokenAxe; }
	void SetHead(GameObject* const head) { Assert(head, ASSERT_MSG_NULL); mHead = head; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	void hurt();
	void recover();

	void block();

	void preJump();
	void jump();
	void jumpSwing();
	void landAttack();

	void slash();
	void Idle();

	void preLunge();
	void lunge();
	void lungeAttack();

	void _throw();
	void tug();
	void returnAxe();

	void slice();
	void struggle();

	void throwAxe();

	void turnOnVisibleAxe();
	void turnOffVisibleAxe();	

	void turnOnMonsterAttack();
	void turnOffMonsterAttack();

	virtual void onCollisionEnter(Collider2D* other) override;

	bool isAxeInHand();
	bool isAttackable();

	GameObject* mMonsterAttack;
	GameObject* mBrokenAxe;
	GameObject* mHead;

	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;
	Vector2 mDirection;
	eKissyfaceAIState mState;
	GameObject* mAxe;

	int mLife;

	float mHurtTime;
	float mStruggleTime;
};
