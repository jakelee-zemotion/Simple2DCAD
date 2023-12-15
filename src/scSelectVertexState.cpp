#include "scSelectVertexState.h"

using namespace std;

scSelectVertexState::scSelectVertexState(shared_ptr<scScene>& scene)
	:scSelectState(scene, SHAPE_TYPE::VERTEX)
{
}

scSelectVertexState::~scSelectVertexState()
{
}