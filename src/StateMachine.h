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

	void AddState(const std::string name, std::shared_ptr<State> state);
	void Transition(const std::string name);
	std::shared_ptr<State> GetCurrentState() const;

private:
	std::map<std::string, std::shared_ptr<State>> mStateMap;
	std::shared_ptr<State> mCurrState;

};

