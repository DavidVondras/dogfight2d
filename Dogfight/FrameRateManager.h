#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

#include <SFML\System.hpp>

class FrameRateManager :
	public sf::Clock
{
private:
	float _frameDuration;
	float _lastSleepDuration;
	float _lastElapsedTime;
	int _isLate;

public:
	//Initialization
	FrameRateManager(void);
	FrameRateManager(float frameRate);
	~FrameRateManager(void);

	//Properties
	void SetFrameDuration(float value) { _frameDuration = value; }
	void SetFrameRate(float value) { _frameDuration = 1.f/value; }
	int IsLate(void) { return _isLate; }
	float GetLastSleepDuration(void) { return _lastSleepDuration; }

	//Methods
	int WaitBalance(void);
};

#endif