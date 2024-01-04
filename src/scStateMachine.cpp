#include "scStateMachine.h"

#include "scDrawLineState.h"
#include "scSelectState.h"
#include "scScene.h"
#include "scCoordinateHelper.h"
#include "scCommon.h"

#include <QPainter>

using namespace std;

scStateMachine::scStateMachine()
{
}

scStateMachine::~scStateMachine()
{
}

void scStateMachine::AddState(
    const string& name, 
    const std::shared_ptr<scScene>& scene,
    const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
{
    shared_ptr<scState> state;
        
    if (name == SC_DRAW_LINE)
        state = make_shared<scDrawLineState>(scene, coordinateHelper);
    else if (name == SC_SELECT_ALL)
        state = make_shared<scSelectState>(scene, coordinateHelper, SHAPE_TYPE::VERTEX | SHAPE_TYPE::LINE | SHAPE_TYPE::FACE);
    else if (name == SC_SELECT_VERTEX)
        state = make_shared<scSelectState>(scene, coordinateHelper, SHAPE_TYPE::VERTEX);
    else if (name == SC_SELECT_LINE)
        state = make_shared<scSelectState>(scene, coordinateHelper, SHAPE_TYPE::LINE);
    else if (name == SC_SELECT_FACE)
        state = make_shared<scSelectState>(scene, coordinateHelper, SHAPE_TYPE::FACE);

	mStateMap[name] = state;
}

void scStateMachine::Transition(const string& name)
{
	assert(mStateMap.find(name) != mStateMap.end());

	mCurrState = mStateMap[name];
}

void scStateMachine::EndState()
{
    if (mCurrState != nullptr)
        mCurrState->EndState();
}

void scStateMachine::Paint(QPainter& painter)
{
    assert(mCurrState != nullptr);

    mCurrState->Paint(painter);
}

shared_ptr<scState> scStateMachine::GetCurrentState() const
{
	assert(mCurrState != nullptr);

	return mCurrState;
}
