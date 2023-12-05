#pragma once
#include "State.h"
#include <map>
#include <memory>
#include <string>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	//void Transition(std::string name);
	//void AddState(std::string name, State state);
	State& GetCurrentState();

private:
	std::map<std::string, std::shared_ptr<State>> mStateMap;
	std::shared_ptr<State> mCurrState; 

};

