#include <iostream>
#include <math.h>
#include "AeroplaneEntity.h"


AeroplaneEntity::AeroplaneEntity(void):
	_imageAeroplane(NULL),
	_mass(700.f),
	_vRotation(0),
	_rotateValue(0),
	_propelValue(0),
	_propelCoef(500.f),
	_cx(0.0006f),
	_czMin(0.01f),
	_czMax(1.f),
	_czMaxVelocity(45.f),
	_MVcoef(0.04f),
	_MVlim(30.f),
	_MelevCoef(1.3f)
{

	_imageAeroplane = new sf::Image();
	if(!_imageAeroplane->LoadFromFile("mustang.png"))
	{
		std::cerr<<"Error while loading rafaletest.png "<<std::endl;
	}
	this->SetImage(*_imageAeroplane);

	//Dummy data
	SetPosition(100,480);
	SetCenter(96,40);
	_velocity.x = 0;
	_velocity.y = 0;
	_landingPoint1.x = 105.f;
	_landingPoint1.y = 57.f;
	_landingPoint2.x = 9.f;
	_landingPoint2.y = 36.f;
}


AeroplaneEntity::~AeroplaneEntity(void)
{
	DeleteReference(_imageAeroplane);
}

void AeroplaneEntity::PreCompute()
{
	_rotationRad = GetRotation()*PI/180.f;
	_cosRotation = std::cosf(_rotationRad);
	_sinRotation = std::sinf(_rotationRad);

	// Local velocity
	_velocity_local.x = _cosRotation*_velocity.x - _sinRotation*_velocity.y;
	_velocity_local.y = _sinRotation*_velocity.x + _cosRotation*_velocity.y;

	// Normal velocity
	_vNormalQuad = _velocity.x*_velocity.x + _velocity.y*_velocity.y;
	_vNormal = std::sqrtf(_vNormalQuad);
}


void AeroplaneEntity::Compute_F_propel()
{
	_F_propel.x = _cosRotation*_propelValue*_propelCoef;
	_F_propel.y = _sinRotation*_propelValue*_propelCoef;
}


void AeroplaneEntity::Compute_F_weight()
{
	_F_weight.x = 0;
	_F_weight.y = -_mass*9.81f;
}


void AeroplaneEntity::Compute_F_Rx()
{
	_F_Rx.x = -_cosRotation*_velocity_local.x*_velocity_local.x*_cx;
	_F_Rx.y = -_sinRotation*_velocity_local.x*_velocity_local.x*_cx;
}


void AeroplaneEntity::Compute_F_Rz(float ellapsedTime)
{
	if(_velocity_local.x < 0)
		// Min value of cz
		_cz = _czMin;
	else if(_velocity_local.x > _czMaxVelocity)
		// Max value of cz
		_cz = _czMax;
	else 
		// Bezier formula for Cz
		_cz = 6.f*(_czMin-_czMax)*(_velocity_local.x*_velocity_local.x*_velocity_local.x/3-_czMaxVelocity*_velocity_local.x*_velocity_local.x/2.f)/(_czMaxVelocity*_czMaxVelocity*_czMaxVelocity) + _czMin;

	// Strenght
	_F_Rz.x = -_sinRotation*_velocity_local.y*_cz*_mass/ellapsedTime;
	_F_Rz.y = _cosRotation*_velocity_local.y*_cz*_mass/ellapsedTime;
}


#define ComputeMOffsetCoef(vCoef, vLim) 3.f*vCoef*(_vNormalQuad*_vNormal/3.f - vLim*vLim*_vNormal)/(2*vLim*vLim*vLim)
#define ComputeMElevCoef(coef, vLim) 6.f*coef*(vLim*_velocity_local.x*_velocity_local.x/2.f - _velocity_local.x*_velocity_local.x*_velocity_local.x/3.f)/(vLim*vLim*vLim)
void AeroplaneEntity::Think(EventListener* const eventListener, EnvironementProvider* const environementprovider)
{
	// Check input
	_rotateValue = 0;
	if(eventListener->GetInputLeft())
		_rotateValue = 1;
	if(eventListener->GetInputRight())
		_rotateValue = -1;
	if(eventListener->GetInputPropNum())
		_propelValue = (float)eventListener->GetInputPropNumValue();

	//Pre compute values
	PreCompute();

	// Strenghts
	Compute_F_weight();
	Compute_F_propel();
	Compute_F_Rx();
	Compute_F_Rz(eventListener->GetEllapsedTime());
	
	// Velocity
	_velocity.x += (_F_weight.x + _F_propel.x + _F_Rx.x + _F_Rz.x)*eventListener->GetEllapsedTime()/_mass;
	_velocity.y -= (_F_weight.y + _F_propel.y + _F_Rx.y + _F_Rz.y)*eventListener->GetEllapsedTime()/_mass;

	//Momentum offset
	_rotationIncidence = GetRotation() + std::atan2f(_velocity.y, _velocity.x)*180.f/PI;
	if(_rotationIncidence > 180.f) _rotationIncidence -= 360.f;
	else if(_rotationIncidence < -180.f) _rotationIncidence += 360.f;

	if(_vNormal >= _MVlim)  _Moffset = -_rotationIncidence*_MVcoef;
	else if(_vNormal <= -_MVlim) _Moffset = _rotationIncidence*_MVcoef;
	else _Moffset = _rotationIncidence*ComputeMOffsetCoef(_MVcoef, _MVlim);

	//Moment Elev
	if(_velocity_local.x >= _MVlim) _MCelev = _MelevCoef;
	else if(_velocity_local.x <= 0.f) _MCelev = 0;
	else _MCelev = ComputeMElevCoef(_MelevCoef, _MVlim);

	this->Rotate(_Moffset);
	_vRotation += 1.f*_rotateValue*_MCelev;
	_vRotation *= 0.6f;

	this->Move(_velocity.x, _velocity.y);
	this->Rotate(_vRotation);

	//Compute global landing points
	_landingPoint1_global = this->TransformToGlobal(_landingPoint1);
	_landingPoint2_global = this->TransformToGlobal(_landingPoint2);

	_landingPoint1_isInCollision = _landingPoint1_global.y >= 535;
	_landingPoint2_isInCollision = _landingPoint2_global.y >= 535;

	if(_landingPoint1_isInCollision && _landingPoint2_isInCollision)
	{
		float newRotation = std::atan2f(_landingPoint1.y - _landingPoint2.y, _landingPoint1.x - _landingPoint2.x);
		this->SetRotation( newRotation*180.f/PI);
		this->SetY( 535 - ( _landingPoint1.y - GetCenter().y )*std::cosf(newRotation) );
		this->_velocity.y = 0;
	}
	else if(_landingPoint1_isInCollision)
	{
		
	}
	else if(_landingPoint2_isInCollision)
	{

	}
}


void AeroplaneEntity::Draw(sf::RenderWindow* const renderWindow)
{
	renderWindow->Draw(*this);
	DrawStrengthData(renderWindow);
}


void AeroplaneEntity::AddDebugFields(DashBoard* const dashBoard)
{
	dashBoard->Add(&_velocity.x, "A. Global Vx");
	dashBoard->Add(&_velocity.y, "A. Global Vy");
	dashBoard->Add(&_velocity_local.x, "A. Local Vx");
	dashBoard->Add(&_velocity_local.y, "A. Local Vy");
	dashBoard->Add(&_propelValue, "A. Propel");
	dashBoard->Add(&_cz, "A. Cz");
	dashBoard->Add(&_rotationIncidence, "A. Rotation vel offset");
	dashBoard->Add(&_Moffset, "Moment offset");
	dashBoard->Add(&_MCelev, "Moment Elev");
}


#define STRENGHT_VECTOR_COEF 0.01f
#define DrawStrenght(strenght) sf::Shape::Line(position, sf::Vector2f( position.x + strenght.x*STRENGHT_VECTOR_COEF, position.y - strenght.y*STRENGHT_VECTOR_COEF), 2, sf::Color(0,0,255));
void AeroplaneEntity::DrawStrengthData(sf::RenderWindow* const renderWindow)
{
	sf::Vector2f position = GetPosition();
	sf::Shape vectorStrenght = DrawStrenght(_F_weight);

	//horizon
	renderWindow->Draw(sf::Shape::Line(sf::Vector2f(-800,535), sf::Vector2f(2000,535), 1, sf::Color(0,0,0)));

	//Strenght vectors
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_F_propel);
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_F_Rx);
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_F_Rz);
	renderWindow->Draw(vectorStrenght);

	//Gravity center
	renderWindow->Draw(sf::Shape::Circle(position, 2, sf::Color(255, 0, 0)));

	//Landing points
	renderWindow->Draw(sf::Shape::Circle(_landingPoint1_global, 2, sf::Color(255, 255, 0)));
	renderWindow->Draw(sf::Shape::Circle(_landingPoint2_global, 2, sf::Color(255, 255, 0)));
}