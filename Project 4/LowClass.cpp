#include "LowClass.h"



LowClass::LowClass() :FlatPerson(15.f)
{
	Person.setPointCount(3);
	width = Person.getLocalBounds().width;
	height = Person.getLocalBounds().height;
}

LowClass::~LowClass()
{
}
