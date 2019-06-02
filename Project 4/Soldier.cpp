#include "Soldier.h"

Soldier::Soldier() {}

//************************ Constructor*****************************************
Soldier::Soldier(Tribe trb)
{
	//store tribe data in tribe
	tribe = trb;
	ptype = PType::SOLDIER;

	if (tribe == Tribe::WESTERNER)
	{
		Rwall = left_wall_h_pos;
		Lwall = 0;
		int x = rand() % (Rwall - 10);
		int y = rand() % ((int)window_height - 100);
		Person.setPosition(x, y);

		Person.setFillColor(sf::Color::Red);
		Person.setOutlineThickness(Soldier_border);
		Person.setOutlineColor(sf::Color::Green);
		//set the erritory to west
		territory = Territory::WEST;
	}
	else
	{
		Rwall = window_width;
		Lwall = right_wall_h_pos;
		unsigned int x = Lwall + (rand() % (Rwall - Lwall - 10));
		unsigned int y = rand() % ((int)window_height - 100);
		Person.setPosition(x, y);

		Person.setFillColor(sf::Color::Green);
		Person.setOutlineThickness(Soldier_border);
		Person.setOutlineColor(sf::Color::Red);
		territory = Territory::EAST;
	}
}

Soldier::~Soldier(){}

//*******************************  Move ***************************************
void Soldier::Move(float s)
{
	
	

	/*This is a perimeter set around the gap. if the soldier in anywhere
	along the length of the gap within 50 pixels of either side */
	if (Person.getPosition().y > long_wall_length &&
		Person.getPosition().y + height < long_wall_length + gap && 
		Person.getPosition().x > left_wall_h_pos - 50 && 
		Person.getPosition().x < left_wall_h_pos + 50
		||
		Person.getPosition().y > short_wall_length && 
		Person.getPosition().y + height < short_wall_length + gap && 
		Person.getPosition().x > right_wall_h_pos - 50 && 
		Person.getPosition().x < right_wall_h_pos + 50)
	{
		// call change territory method
		ChangeTerritory();
		// move the person by he amount of velocity
		Person.move(vel.x * s, vel.y * s);
	}
	else
	{
		FlatPerson::Move(s);
	}
}

//*********************************** Change Territory **********************
void Soldier::ChangeTerritory()
{
	//if soldier position is greater than Rwall and terriroty is west
	if (Person.getPosition().x > Rwall  && territory == Territory::WEST)
	{
		territory = Territory::BATTLEFIELD;
		Rwall = right_wall_h_pos;
		Lwall = left_wall_h_pos;
		//cout << "Soldier Moved From West to Battlefield\n";
	}
	//if soldier position is less than Lwall and terriroty is Battlefield
	if (Person.getPosition().x < Lwall && territory == Territory::BATTLEFIELD)
	{
		territory = Territory::WEST;
		Rwall = left_wall_h_pos;
		Lwall = 0;
		//cout << "Soldier Moved From Battlefield to West\n";
	}

	//if soldier position is greater than Rwall and terriroty is battlefield
	if (Person.getPosition().x > Rwall && territory == Territory::BATTLEFIELD)
	{
		territory = Territory::EAST;
		Rwall = window_width;
		Lwall = right_wall_h_pos;
		//cout << "Soldier Moved From Battlefield to East\n";
	}

	//if soldier position is greater than Lwall and terriroty is east
	if (Person.getPosition().x < Lwall && territory == Territory::EAST)
	{
		territory = Territory::BATTLEFIELD;
		Rwall = right_wall_h_pos;
		Lwall = left_wall_h_pos;
		//cout << "Soldier Moved From East to Battlefield\n";
	}

}




