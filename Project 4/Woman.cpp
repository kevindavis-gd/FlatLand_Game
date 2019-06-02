#include "Woman.h"



Woman::Woman() 
{
}

Woman::Woman(Tribe trb) :FlatPerson(15.f)
{
	Person.setPointCount(20);
	width = Person.getLocalBounds().width;
	height = Person.getLocalBounds().height;


	tribe = trb;
	ptype = PType::WOMAN;

	//if tribe is westerner set colour to red and 
	//randomly set position in the west
	if (tribe == Tribe::WESTERNER)
	{
		Rwall = left_wall_h_pos;
		Lwall = 0;

		int x = rand() % (Rwall - 10);
		int y = rand() % (window_height - 100);
		Person.setPosition(x, y);
		Person.setFillColor(sf::Color::Red);
	}
	//if tribe is easterner set colour to green and 
	//randomly set position in the east
	else
	{
		Rwall = window_width;
		Lwall = right_wall_h_pos;

		int x = Lwall + (rand() % (Rwall - Lwall - 100));
		int y = rand() % (window_height - 10);
		Person.setPosition(x, y);
		Person.setFillColor(sf::Color::Green);
	}
}

Woman::~Woman()
{
}
