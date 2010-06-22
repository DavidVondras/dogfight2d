#include <SFML\System.hpp>

class CollisionPoint: 
	public sf::Vector2f
{
private:
	int _isInCollision;

public:
	//Initialization
	CollisionPoint(void) : 
		sf::Vector2f(),
		_isInCollision(false){}

	CollisionPoint(sf::Vector2f& vector2f) : 
		sf::Vector2f(vector2f),
		_isInCollision(false){}

	CollisionPoint(float x, float y) : 
		sf::Vector2f(x, y),
		_isInCollision(false){}

	~CollisionPoint(void){}

	//Properties
	int IsInCollision(void) { return _isInCollision; }
	void SetIsInCollision(int value) { _isInCollision = value; }
};