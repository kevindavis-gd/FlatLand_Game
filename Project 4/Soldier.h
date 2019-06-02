#pragma once
#include "LowClass.h"
class Soldier :
	public LowClass
{
private:
	//size of soldier border
	int Soldier_border = 2;
public:
	Soldier();
	Soldier(Tribe trb);
	void Move(float s); // virtual
	void ChangeTerritory();

	~Soldier();
};


