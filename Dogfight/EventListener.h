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
		_inputDown,
		_inputPropNum,
		_inputPropNumValue,
		_inputZoomIn,
		_inputZoomOut;
	sf::RenderWindow* const _renderWindow;

public:
	//Initialization
	EventListener(sf::RenderWindow* const renderWindow)
		:_renderWindow(renderWindow),
		_inputPropNumValue(0),
		_inputClose(false){}

	~EventListener(void){}

	//Render properties
	float GetEllapsedTime(void) const { return _renderWindow->GetFrameTime(); }

	//Input Properties
	int GetInputClose(void) const { return _inputClose; }
	int GetInputLeft(void) const { return _inputLeft; }
	int GetInputRight(void) const { return _inputRight; }
	int GetInputUp(void) const { return _inputUp; }
	int GetInputDown(void) const { return _inputDown; }
	int GetInputPropNum(void) const { return _inputPropNum; }
	int GetInputPropNumValue(void) const { return _inputPropNumValue; }
	int GetInputZoomIn(void) const { return _inputZoomIn; }
	int GetInputZoomOut(void) const { return _inputZoomOut; }

	//Methods
	void CheckEvents(void);
};

#endif