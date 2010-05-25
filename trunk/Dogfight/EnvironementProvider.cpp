#include "EnvironementProvider.h"


EnvironementProvider::EnvironementProvider(void)
{
	_sceneCollisionMask = NULL;
	for(int i=0; i<64;i++)
		_aeroplaneArray[i] = NULL;
}


EnvironementProvider::~EnvironementProvider(void)
{
	if(_sceneCollisionMask != NULL)
		delete _sceneCollisionMask;

	for(int i=0;i<64;i++)
		if(_aeroplaneArray[i] != NULL)
			delete _aeroplaneArray[i];
}
