#pragma once
#include "scState.h"

#include <map>
#include <memory>
#include <string>

class QPainter;
class scScene;
class scStateMachine
{
public:
	scStateMachine();
	~scStateMachine();

	void AddState(const std::string& name, const std::shared_ptr<scScene>& scene);
	void Transition(const std::string& name);
	void Paint(QPainter& painter);

	std::shared_ptr<scState> GetCurrentState() const;

private:
	std::map<std::string, std::shared_ptr<scState>> mStateMap;
	std::shared_ptr<scState> mCurrState;

};

