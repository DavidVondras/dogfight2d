#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SFML\Window.hpp>

///
/// Input events interface
///
class EventListener
{
private:
	int _inputClose,
		_inputLeft,
		_inputRight,
		_inputUp,
		_inputDown;
	sf::RenderWindow* _renderWindow;

public:
	//Initialization
	EventListener(sf::RenderWindow* renderWindow)
		:_renderWindow(renderWindow),
		_inputClose(false){}

	~EventListener(void){}

	//Properties
	int GetInputClose(void) { return _inputClose; }
	int GetInputLeft(void) { return _inputLeft; }
	int GetInputRight(void) { return _inputRight; }
	int GetInputUp(void) { return _inputUp; }
	int GetInputDown(void) { return _inputDown; }

	//Methods
	void CheckEvents(void);
};

#endif