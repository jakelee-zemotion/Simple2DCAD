#pragma once
#include "scStateInterface.h"
#include <map>
#include <memory>
#include <string>

class scStateMachine
{
public:
	scStateMachine();
	~scStateMachine();

	void AddState(const std::string name, std::shared_ptr<scStateInterface> state);
	void Transition(const std::string name);
	std::shared_ptr<scStateInterface> GetCurrentState() const;

private:
	std::map<std::string, std::shared_ptr<scStateInterface>> mStateMap;
	std::shared_ptr<scStateInterface> mCurrState;

};

