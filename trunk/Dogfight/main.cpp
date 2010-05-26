#include <stdlib.h>
#include <iostream>

#include "SceneManager.h"
#include "FrameRateManager.h"


// Declarations
FrameRateManager frameRateManager(30.f);
void EndStepMethod(void);


///
/// Main method
///
int main(void)
{
	SceneManager sceneManager;
	sceneManager.SetStepEndMethod(EndStepMethod);

	//Main loop
	frameRateManager.Reset();
	do
	{
		sceneManager.Step();
	}
	while(!sceneManager.GetEventListener()->GetInputClose());

	return EXIT_SUCCESS;
}


///
/// Method invoked at the endInvoke of the step method
///
void EndStepMethod(void)
{
	if(!frameRateManager.WaitBalance())
		printf("Warning: Framerate is too fast [%f secondes]\n", frameRateManager.GetLastSleepDuration());
}