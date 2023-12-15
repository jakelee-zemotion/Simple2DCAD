#include "scSelectFaceState.h"

using namespace std;

scSelectFaceState::scSelectFaceState(shared_ptr<scScene>& scene)
	:scSelectState(scene, SHAPE_TYPE::FACE)
{
}

scSelectFaceState::~scSelectFaceState()
{
}