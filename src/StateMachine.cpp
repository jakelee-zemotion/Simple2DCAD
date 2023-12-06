#include "StateMachine.h"
#include "DrawLineState.h"
#include "IdleState.h"

using namespace std;

StateMachine::StateMachine()
{
	AddState("Idle", make_shared <IdleState>());
	mCurrState = mStateMap["Idle"];
}

StateMachine::~StateMachine()
{
}

void StateMachine::AddState(const string name, shared_ptr<State> state)
{
	mStateMap[name] = state;
}

void StateMachine::Transition(const string name)
{
	mCurrState = mStateMap[name];
}

shared_ptr<State> StateMachine::GetCurrentState() const
{
	return mCurrState;
}
