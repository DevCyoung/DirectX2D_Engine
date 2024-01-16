#include "pch.h"
#include "MonsterFSM.h"

MonsterFSM::MonsterFSM(GameObject* owner)
	: mMonsterStates{}
	, mRegisterEnterState(nullptr)
	, mCurrentState(nullptr)
	, mOwner(owner)
{
}

MonsterFSM::~MonsterFSM()
{
	for (MonsterState* state : mMonsterStates)
	{
		DELETE_POINTER(state);
	}
}

void MonsterFSM::Initialize(int idx)
{
	Assert(idx < MAX_MONSTER_STATES, ASSERT_MSG_INVALID);
	Assert(mMonsterStates[idx], ASSERT_MSG_NULL);

	for (MonsterState* state : mMonsterStates)
	{
		if (state)
		{
			state->Initialize();
		}
	}

	mCurrentState = mMonsterStates[idx];
	mCurrentState->Enter();
}

void MonsterFSM::GlobalUpdate()
{
	if (mRegisterEnterState)
	{
		mCurrentState->Exit();
		mCurrentState = mRegisterEnterState;
		mCurrentState->Enter();
		mRegisterEnterState = nullptr;
	}
}

void MonsterFSM::Update()
{
	Assert(mCurrentState, ASSERT_MSG_NULL);

	mCurrentState->Update();
}

void MonsterFSM::AddState(int idx, MonsterState* state)
{
	Assert(state, ASSERT_MSG_NULL);
	Assert(idx < MAX_MONSTER_STATES, ASSERT_MSG_INVALID);
	Assert(!mMonsterStates[idx], ASSERT_MSG_NOT_NULL);

	state->mMonsterFSM = this;
	state->mGameObject = mOwner;
	state->mType = idx;

	mMonsterStates[idx] = state;
}

void MonsterFSM::ChangeState(int idx)
{
	Assert(mCurrentState, ASSERT_MSG_NULL);
	Assert(idx < MAX_MONSTER_STATES, ASSERT_MSG_INVALID);
	Assert(mMonsterStates[idx], ASSERT_MSG_NULL);
	//Assert(!mRegisterEnterState, WCHAR_IS_NOT_NULLPTR);

	mRegisterEnterState = mMonsterStates[idx];

	/*mCurrentState->Exit();
	mCurrentState = mMonsterStates[idx];
	mCurrentState->Enter();*/
}
