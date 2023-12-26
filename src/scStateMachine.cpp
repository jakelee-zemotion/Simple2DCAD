#include "scStateMachine.h"

#include "scDrawLineState.h"
#include "scSelectState.h"
#include "scSelectVertexState.h"
#include "scSelectLineState.h"
#include "scSelectFaceState.h"
#include "scScene.h"

#include <QPainter>

using namespace std;

scStateMachine::scStateMachine()
{
}

scStateMachine::~scStateMachine()
{
}

void scStateMachine::AddState(const string& name, const std::shared_ptr<scScene>& scene)
{
    shared_ptr<scState> state;

    if (name == "Draw")
        state = make_shared<scDrawLineState>(scene);
    else if (name == "SelectAll")
        state = make_shared<scSelectState>(scene, SHAPE_TYPE::VERTEX | SHAPE_TYPE::LINE | SHAPE_TYPE::FACE);
    else if (name == "SelectVertex")
        state = make_shared<scSelectState>(scene, SHAPE_TYPE::VERTEX);
    else if (name == "SelectLine")
        state = make_shared<scSelectState>(scene, SHAPE_TYPE::LINE);
    else if (name == "SelectFace")
        state = make_shared<scSelectState>(scene, SHAPE_TYPE::FACE);

	mStateMap[name] = state;
}

void scStateMachine::Transition(const string& name)
{
	assert(mStateMap.find(name) != mStateMap.end());

	if (mCurrState != nullptr)
		mCurrState->EndState();

	mCurrState = mStateMap[name];
}

shared_ptr<scState> scStateMachine::GetCurrentState() const
{
	assert(mCurrState != nullptr);

	return mCurrState;
}
