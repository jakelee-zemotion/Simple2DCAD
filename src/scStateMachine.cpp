#include "scStateMachine.h"

// qt
#include <QPainter>

// Simple2DCAD
#include "scDrawLineState.h"
#include "scSelectAllState.h"
#include "scScene.h"
#include "scCoordinateHelper.h"
#include "scCommon.h"

using namespace std;

scStateMachine::scStateMachine()
{
}

scStateMachine::~scStateMachine()
{
}

void scStateMachine::AddState(const string& name, const std::shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper)
{
    shared_ptr<scState> state;
        
    if (name == SC_DRAW_LINE)
        state = make_shared<scDrawLineState>(scene, coordinateHelper);
    else if (name == SC_SELECT_ALL)
        state = make_shared<scSelectAllState>(scene, coordinateHelper, scShapeType::VERTEX | scShapeType::LINE | scShapeType::FACE);
    else if (name == SC_SELECT_VERTEX)
        state = make_shared<scSelectAllState>(scene, coordinateHelper, scShapeType::VERTEX);
    else if (name == SC_SELECT_LINE)
        state = make_shared<scSelectAllState>(scene, coordinateHelper, scShapeType::LINE);
    else if (name == SC_SELECT_FACE)
        state = make_shared<scSelectAllState>(scene, coordinateHelper, scShapeType::FACE);

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
