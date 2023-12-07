#pragma once
#include "scState.h"
#include <map>
#include <memory>
#include <string>

class scStateMachine
{
public:
	scStateMachine();
	~scStateMachine();

	void AddState(const std::string name, std::shared_ptr<scState> state);
	void Transition(const std::string name);
	std::shared_ptr<scState> GetCurrentState() const;

private:
	std::map<std::string, std::shared_ptr<scState>> mStateMap;
	std::shared_ptr<scState> mCurrState;

};

