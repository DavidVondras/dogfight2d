#include <stdlib.h>
#include <iostream>

#include "SceneManager.h"


// Declarations
void EndStepMethod(void);


///
/// Main method
///
int main(void)
{
	SceneManager sceneManager;
	sceneManager.SetStepEndMethod(EndStepMethod);

	//Main loop
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
	
}