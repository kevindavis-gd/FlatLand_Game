#include "FlatPerson.h"
FlatPerson::FlatPerson() {}

FlatPerson::FlatPerson(float radius)
{
	Person.setRadius(radius);
	//speed of people
	vel.x = 0.5;
	vel.y = 0.5;
	//set the life to full
	energy = 2000;
	// set the person to alive
	dead = 0;
}
FlatPerson::~FlatPerson(){}

//***************************Draw Method *************************************
void FlatPerson::Draw(sf::RenderWindow & window)
{
	window.draw(Person);
}

//*************************************Virtual Move Method ********************
void FlatPerson::Move(float s)
{
	// move the person by the amount of velocity
	Person.move(vel.x * s, vel.y * s);
	//call the random movement method
	ChangeDir(deg);

	//if the Y position is <= 0 or >= window height then reverse Y
	if (Person.getPosition().y <= 0 ||
		Person.getPosition().y + height >= window_height)
	{
		vel.y = -vel.y;
	}

	//if the X position is < Lwall or then reverse X
	if (Person.getPosition().x < Lwall)
	{
		vel.x = -vel.x;
		Person.setPosition(-Person.getPosition().x 
			+ 2 * Lwall, Person.getPosition().y);
	}

	//if the X position pluss width is > Rwall width or then reverse X
	if (Person.getPosition().x + width > Rwall)
	{
		vel.x = -vel.x;
		Person.setPosition(-(Person.getPosition().x + 2 * width)
			+ 2 * Rwall, Person.getPosition().y);
	}
}

//*******************************Random Movement******************************
void FlatPerson::ChangeDir(float deg)
{
	sf::Transform transMat;
	float range = 2 * deg;
	deg = (rand() / (float)RAND_MAX)*range - deg;
	transMat.rotate(deg);
	vel = transMat * vel;
}

//***********************************Wound************************
bool FlatPerson:: Wound()
{
	if (!dead)
	{
		energy -= 5;
	}

	if (energy <= 0 && !dead)
	{
		Person.setFillColor(sf::Color::Color(128, 128, 128));
		Person.setOutlineColor(sf::Color::Color(128, 128, 128));
		dead = 1;
		vel.x = 0.0;
		vel.y = 0.0;
	}
	return dead;
}

//***********************************Get Dead **********************

bool FlatPerson:: Alive()
{
	bool alive = !dead;
	return alive;
}

//**********************************Get Ptype***********************

PType FlatPerson:: GetPType()
{
	return ptype;
}

//************************************Get Tribe **********************

Tribe FlatPerson::GetTribe()
{
	return tribe;
}

//*************************************Get Person *********************

sf::CircleShape FlatPerson::GetPerson()
{

	return Person;
}