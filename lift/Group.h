#pragma once
#include "ElevatorLift.h"

class Group
{
public:
	Group(ElevatorLift *e1, ElevatorLift *e2);
	~Group();
	void action();
private:
	ElevatorLift *e1;
	ElevatorLift *e2;
	friend class Passenger;

};