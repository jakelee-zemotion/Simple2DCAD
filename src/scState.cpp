#include "scState.h"

#include "scScene.h"

using namespace std;

scState::scState(const shared_ptr<scScene>& scene)
	:mScene(scene)
{
}

scState::~scState()
{
}
