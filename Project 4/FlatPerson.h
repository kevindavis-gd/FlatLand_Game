#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//**********************Wall***************************************************
// every class needs to know where the walls are
extern int window_width;
extern int window_height;
extern int gap;
extern float size_of_battlefield;
extern float left_wall_h_pos;
extern float right_wall_h_pos;
extern float short_wall_length;
extern float long_wall_length;

enum class Territory { EAST, WEST, BATTLEFIELD };
enum class PType { WOMAN, WORKMAN, SOLDIER, KING, NOBLE };
enum class Tribe { EASTERNER, WESTERNER };

using namespace std;

class FlatPerson
{
	protected:
	// Random movement
	float deg = 0.7;
	// The velocity vector
	sf::Vector2f vel;
	// contains all the person attributes
	sf::CircleShape Person;
	// The territory the person is presently in
	enum class Territory territory;
	enum class PType ptype;
	enum class Tribe tribe;
	int Lwall;
	int Rwall;
	float width;
	float height;
	//life and energy
	int energy;
	bool dead;

	public:
	FlatPerson();
	// float is the radius of this person
	FlatPerson(float);
	// s is a multiplier to allow larger moves
	virtual void Move(float s);
	void Draw(sf::RenderWindow & window);
	void ChangeDir(float deg);
	bool Wound();
	bool Alive();
	PType GetPType();
	Tribe GetTribe();
	sf::CircleShape GetPerson();

	~FlatPerson();
};