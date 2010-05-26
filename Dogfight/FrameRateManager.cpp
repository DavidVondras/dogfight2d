#include "FrameRateManager.h"
#include <iostream>


FrameRateManager::FrameRateManager(void)
	:sf::Clock(), 
	_frameDuration(1.f/30.f),
	_lastSleepDuration(0.f),
	_isLate(false)
{}


FrameRateManager::FrameRateManager(float frameRate)
	:sf::Clock(), 
	_frameDuration(1.f/frameRate),
	_lastSleepDuration(0.f),
	_isLate(false)
{}


FrameRateManager::~FrameRateManager(void)
{}


int FrameRateManager::WaitBalance(void)
{
	//Retrieve clock data
	_lastElapsedTime = GetElapsedTime();

	//Compute frameRate status
	_lastSleepDuration = _frameDuration - _lastElapsedTime - (_isLate ? _lastSleepDuration : 0.f);
	_isLate = (_lastSleepDuration < 0.f);

	//balance frameRate action
	if(!_isLate) sf::Sleep(_lastSleepDuration);
	
	Reset();
	return !_isLate;
}