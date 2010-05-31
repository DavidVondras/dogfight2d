#include <SFML\System.hpp>

class CollisionPoint: 
	public sf::Vector2f
{
private:
	int _isInCollision;
	float _strenghtX;
	float _strenghtY;

public:
	//Initialization
	CollisionPoint(void) : 
		sf::Vector2f(),
		_isInCollision(false),
		_strenghtX(0),
		_strenghtY(0){}

	CollisionPoint(sf::Vector2f& vector2f) : 
		sf::Vector2f(vector2f),
		_isInCollision(false),
		_strenghtX(0),
		_strenghtY(0){}

	CollisionPoint(float x, float y) : 
		sf::Vector2f(x, y),
		_isInCollision(false),
		_strenghtX(0),
		_strenghtY(0){}

	~CollisionPoint(void){}

	//Properties
	int IsInCollision(void) { return _isInCollision; }
	float GetStrenghtX(void) { return _strenghtX; }
	void SetStrenghtX(float value) { _strenghtX = value; }
	float GetStrenghtY(void) { return _strenghtY; }
	void SetStrenghtY(float value) { _strenghtY = value; }
};