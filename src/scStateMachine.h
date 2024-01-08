#pragma once

// system
#include <map>
#include <memory>
#include <string>

// Simple2DCAD
#include "scState.h"

// Forward Declaration
class QPainter;
class scScene;
class scCoordinateHelper;

class scStateMachine
{
// [Member function section]
public:
	scStateMachine();

	void AddState(const std::string& name, const std::shared_ptr<scScene>& scene, const std::shared_ptr<scCoordinateHelper>& coordinateHelper);
	void Transition(const std::string& name);
	void EndState();
	void Paint(QPainter& painter);

	std::shared_ptr<scState> GetCurrentState() const;

// [Member variable section]
private:
	std::map<std::string, std::shared_ptr<scState>> mStateMap;
	std::shared_ptr<scState> mCurrState;
};

