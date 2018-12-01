#include "pch.h"
#include "Group.h"


Group::Group(ElevatorLift * e1, ElevatorLift * e2)
{
	this->e1 = e1;
	this->e2 = e2;
}

Group::~Group()
{
}

void Group::action()
{
	e1->action();
	e2->action();
}

