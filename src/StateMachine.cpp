#include "StateMachine.h"
#include "DrawLineState.h"
#include "IdleState.h"

using namespace std;

StateMachine::StateMachine()
{
	mCurrState = make_shared<IdleState>();
	mStateMap["Idle"] = mCurrState;
}

StateMachine::~StateMachine()
{
}

void StateMachine::AddState(string name, shared_ptr<State> state)
{
	mStateMap[name] = state;
}

void StateMachine::Transition(string name)
{
	mCurrState = mStateMap[name];
}

shared_ptr<State> StateMachine::GetCurrentState() const
{
	return mCurrState;
}
