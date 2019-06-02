//Name:Kevin Davis
//Course:CS2143
//Project:#4 FlatLand
//Teacher: Richard Simpson
//Due-Date:04/11/2019
/*Purpose: Create a program to represent the world as potrayed in the
Flatland book, using OOP principles such as inheritance, polimorphism etc.
*/









// LIFE iS AT 5, CHANGE IT ******************************************** <= IMPORTANT
#include <SFML/Graphics.hpp>
#include "FlatPerson.h"
#include "LowClass.h"
#include "Workman.h"
#include "Soldier.h"
#include "Woman.h"

int window_width = 1600, window_height = 700;

// ************************************WALL CONFIG*************************
int gap = 120;
int wall_width = 4;
float size_of_battlefield = (float) window_width / 5;
// ( 1600 - [1600/5] ) / 2
float left_wall_h_pos = (window_width - (size_of_battlefield)) / 2;
float right_wall_h_pos = left_wall_h_pos + size_of_battlefield;
float short_wall_length = window_height / 4 - (float) gap;
float long_wall_length = 3 * (float)window_height / 4;

int main()
{	
	int EasternSoldier = 0, WesternSoldier = 0;
	srand(time(NULL));
	float Damage = 50;
	int moveSpeed = 10;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height),
		"Flatland: West    <- Battlefield ->    East");

	//****************WALL DIMENSTION *****************************************
	sf::RectangleShape top_left_wall
		(sf::Vector2f((float)wall_width, long_wall_length));
	sf::RectangleShape bottom_left_wall
		(sf::Vector2f((float)wall_width, short_wall_length));
	sf::RectangleShape top_right_wall
		(sf::Vector2f((float)wall_width, short_wall_length));
	sf::RectangleShape bottom_right_wall
		(sf::Vector2f((float)wall_width, long_wall_length));

	//****************WALL POSITION *******************************************
	top_left_wall.setPosition(left_wall_h_pos, 0);
	/*max height - line length*/
	bottom_left_wall.setPosition
		(left_wall_h_pos, window_height - short_wall_length); 
	top_right_wall.setPosition(right_wall_h_pos, 0);
	/*max height - line length*/
	bottom_right_wall.setPosition
		(right_wall_h_pos, window_height - long_wall_length);

	//****************WALL COLOR **********************************************
	top_left_wall.setFillColor(sf::Color::White);
	bottom_left_wall.setFillColor(sf::Color::White);
	top_right_wall.setFillColor(sf::Color::White);
	top_right_wall.setFillColor(sf::Color::White);

	//************************** Person Dec  ********************************

	vector<FlatPerson*> population;

	Workman workman1(Tribe::EASTERNER);
	Workman workman2(Tribe::WESTERNER);
	Workman workman3(Tribe::EASTERNER);
	Workman workman4(Tribe::WESTERNER);
	Soldier soldier1(Tribe::EASTERNER);
	Soldier soldier2(Tribe::WESTERNER);
	Soldier soldier3(Tribe::EASTERNER);
	Soldier soldier4(Tribe::WESTERNER);
	Soldier soldier5(Tribe::EASTERNER);
	Soldier soldier6(Tribe::WESTERNER);
	Soldier soldier7(Tribe::EASTERNER);
	Soldier soldier8(Tribe::WESTERNER);
	Woman woman1(Tribe::EASTERNER);
	Woman woman2(Tribe::WESTERNER);

	population.push_back(&workman1);
	population.push_back(&workman2);
	population.push_back(&workman3);
	population.push_back(&workman4);
	population.push_back(&soldier1);
	population.push_back(&soldier2);
	population.push_back(&soldier3);
	population.push_back(&soldier4);
	population.push_back(&soldier5);
	population.push_back(&soldier6);
	population.push_back(&soldier7);
	population.push_back(&soldier8);
	population.push_back(&woman1);
	population.push_back(&woman2);

	//get total number of soldiers for each side
	for (unsigned int x = 0; x < population.size(); x++)
	{

		if (population[x]->GetTribe() == Tribe::EASTERNER && population[x]->GetPType() == PType::SOLDIER)
			EasternSoldier++;
		else if
			(population[x]->GetTribe() == Tribe::WESTERNER && population[x]->GetPType() == PType::SOLDIER)
			WesternSoldier++;
	}

	//*************************************************************************

	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		//*************** WALLS *******************************
		window.draw(top_left_wall);
		window.draw(bottom_left_wall);
		window.draw(top_right_wall);
		window.draw(bottom_right_wall);

		// cycle through population and draw and move them
		for (unsigned int x = 0; x < population.size(); x++)
		{
		
			if (population[x]->Alive())
			{
				population[x]->Draw(window);
				population[x]->Move(moveSpeed);

				for (int y = 0; y < population.size(); y++)
				{
					for (int z = y + 1; z < population.size(); z++)
					{
						//if the global bounds of pop[z] intersects global bounds of pop[y]
						if (population[z]->GetPerson().getGlobalBounds().intersects(population[y]->GetPerson().getGlobalBounds()))
						{
							//if both tribes are different
							if (population[y]->GetTribe() != population[z]->GetTribe())
							{

								if (population[y]->GetPType() == PType::SOLDIER && population[z]->GetPType() != PType::SOLDIER)
								{
									if (population[y]->Alive() && population[z]->Alive())
									{
										population[z]->Wound();
										if (population[z]->Alive() == 0)
										{
											cout << "Civilian Killed \n";
										}
									}
								}
								else if (population[z]->GetPType() == PType::SOLDIER && population[y]->GetPType() != PType::SOLDIER)
								{
									
									if (population[y]->Alive() && population[z]->Alive())
									{
										population[y]->Wound();
										if (population[y]->Alive() == 0)
										{
											cout << "Civilian Killed \n";
										}	
									}	
								}

								else if (population[y]->GetPType() == PType::SOLDIER && population[z]->GetPType() == PType::SOLDIER)
								{
									if (population[y]->Alive() && population[z]->Alive())
									{
										int winner = rand() % 100 + 1;
										if (winner < Damage)
										{
											if (population[z]->GetTribe() == Tribe::EASTERNER)
											{
												population[z]->Wound();
												if (population[z]->Alive() == 0)
												{
													EasternSoldier--;
													cout << EasternSoldier << " Eastern Soldiers Left - 1 Killed\n";
												}
											}
											else if (population[y]->GetTribe() == Tribe::EASTERNER)
											{
												population[y]->Wound();
												if (population[y]->Alive() == 0)
												{
													EasternSoldier--;
													cout << EasternSoldier << " Eastern Soldiers Left - 1 Killed\n";
												}
											}
										}
										else if (winner > Damage)
										{
											if (population[z]->GetTribe() == Tribe::WESTERNER)
											{
												population[z]->Wound();
												if (population[z]->Alive() == 0)
												{
													WesternSoldier--;
													cout << WesternSoldier << " Western Soldiers Left - 1 Killed\n";
												}
											}
											else if (population[y]->GetTribe() == Tribe::WESTERNER)
											{
												population[y]->Wound();
												if (population[y]->Alive() == 0)
												{
													WesternSoldier--;
													cout << WesternSoldier << " Western Soldiers Left - 1 Killed\n";
												}
											}
										}
									}
								}
							}
						}
					}
				}

			}
			else
				population[x]->Draw(window);

		}

		window.display();

		// checks to see if anyone won the game
		if (EasternSoldier == 0)
		{
			cout << "West Wins \n";
			system("PAUSE");
			//stop the loop and end game
			break;
		}
		else if
			(WesternSoldier == 0)
		{
			cout << "East Wins \n";
			system("PAUSE");
			//stop the loop and end game
			break;
		}
	}
	return 0;
}