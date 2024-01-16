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

	//FIXME: �Է¹����� �ʱ�ȭ�� ��� �����ұ�
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
