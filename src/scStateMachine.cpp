#include "scStateMachine.h"
#include "scDrawLineState.h"

using namespace std;

scStateMachine::scStateMachine()
{
}

scStateMachine::~scStateMachine()
{
}

void scStateMachine::AddState(const string name, shared_ptr<scStateInterface> state)
{
	mStateMap[name] = state;
}

void scStateMachine::Transition(const string name)
{
	mCurrState = mStateMap[name];
}

shared_ptr<scStateInterface> scStateMachine::GetCurrentState() const
{
	return mCurrState;
}
