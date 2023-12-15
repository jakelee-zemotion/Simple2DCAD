#include "scSelectLineState.h"

using namespace std;

scSelectLineState::scSelectLineState(shared_ptr<scScene>& scene)
	:scSelectState(scene, SHAPE_TYPE:: LINE)
{
}

scSelectLineState::~scSelectLineState()
{
}