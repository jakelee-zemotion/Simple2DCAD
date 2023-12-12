#include "scStateMachine.h"

using namespace std;

scStateMachine::scStateMachine()
{
}

scStateMachine::~scStateMachine()
{
}

void scStateMachine::AddState(const string& name, shared_ptr<scState>& state)
{
	mStateMap[name] = state;
}

void scStateMachine::Transition(const string& name)
{
	mCurrState = mStateMap[name];
}

shared_ptr<scState> scStateMachine::GetCurrentState() const
{
	return mCurrState;
}
