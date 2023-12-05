#pragma once
#include "State.h"

#include <QScopedPointer>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	//void AddState(State)
	State& GetCurrentState();

private:
	// QMap<QString, QScopedPointer<State>>
	QScopedPointer<State> mState;

};

