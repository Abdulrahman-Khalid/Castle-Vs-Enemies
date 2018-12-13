#include "Fighter.h"
#include "..\Castle\Castle.h"

Fighter::Fighter(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region,int rSpeed) 
	:Enemy(DARKOLIVEGREEN, r_region)
{
	S = id;
	arrivalTime = arrival_time;
	Health = health;
	firePower = fire_power;
	reloadPeriod = reload_period;
	Speed = rSpeed;
}

Fighter::~Fighter()
{
}

void Fighter::Move(Castle* castle, int TimeStep)
{
	int DD = Distance - GetSpeed();
	if (Distance > MinDistance) {
		int D = castle->GetTowerByRegion(Region)->GetunpavedDistance();
		if (D < Distance - GetSpeed() && TimeStep >= arrivalTime) {
			DecrementDist();
		}
		else if(TimeStep != arrivalTime)
		{
			Distance = D+1;
		}
	}
}

void Fighter::Attack(Castle* castle, int TimeStep)
{
	while (castle->GetTowerByRegion(Region)->isDestroyed()&&castle->GetTowerByRegion(Region)->GetKilledTime()<TimeStep)
	{
		int Reg=Region;
		Reg++;
		Reg=Reg%4;
		Region=(REGION)Reg;
		if (Distance<castle->GetTowerByRegion(Region)->GetunpavedDistance())
		{
			Distance=castle->GetTowerByRegion(Region)->GetunpavedDistance()+1;

		}


	}
	int T = TimeStep - arrivalTime;
	int R = reloadPeriod + 1;
	if (T%R == 0) {
		double DT = (1 / (double)Distance)*firePower;
		castle->GetTowerByRegion(Region)->TakeDamage(DT);
	}
	
}

bool Fighter::TakeDamage(Castle * castle,int StepTime)
{
	Health -= ((1 / (double)Distance)*castle->GetTowerByRegion(Region)->GetFirePower());
	return (Health <= 0);
}

TYPE Fighter::GetType()
{
	return FIGHTER;
}
int Fighter::GetSpeed()
{
	return Speed;
}
bool Fighter::IsHide(int StepTime)
{
	return true;
}