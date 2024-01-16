#include "pch.h"
#include "FSMState.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
	: mCurState(nullptr)
	, mPrevState(nullptr)
{
}

FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::ChangeState(FSMState* const state)
{
	Assert(state, ASSERT_MSG_NULL);

	//FIXME: 입력받을때 초기화를 어떻게 설정할까
	//if (state == mCurState)
	//{
	//	return;
	//}
	
	if (nullptr != mCurState)
	{
		mCurState->Exit();
	}
	

	mPrevState = mCurState;	
	mCurState = state;
	mCurState->Enter();
}
