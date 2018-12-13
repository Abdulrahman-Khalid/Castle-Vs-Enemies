#include "Hidden.h"
#include "..\Castle\Castle.h"

Hidden::Hidden(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region, int rSpeed)
	:Enemy(SNOW, r_region)
{
	S = id;
	arrivalTime = arrival_time;
	Health = health;
	firePower = fire_power;
	reloadPeriod = reload_period;
	Speed = rSpeed;
}

Hidden::~Hidden()
{
}

void Hidden::Move(Castle* castle, int TimeStep)
{
	if (Distance > MinDistance) {
		int D = castle->GetTowerByRegion(Region)->GetunpavedDistance();
		if (D < Distance - GetSpeed() && TimeStep >= arrivalTime) {
			DecrementDist();
		}
		else if (TimeStep != arrivalTime)
		{
			Distance = D + 1;
		}
	}
}

void Hidden::Attack(Castle* castle, int TimeStep)
{
	while (castle->GetTowerByRegion(Region)->isDestroyed()&&castle->GetTowerByRegion(Region)->GetKilledTime()<TimeStep)
	{
		int Reg = Region;
		Reg++;
		Reg = Reg % 4;
		Region = (REGION)Reg;
		if (Distance<castle->GetTowerByRegion(Region)->GetunpavedDistance())
		{
			Distance = castle->GetTowerByRegion(Region)->GetunpavedDistance() + 1;

		}


	}
	int T = TimeStep - arrivalTime;
	int R = reloadPeriod + 1;
	if (T%R == 0) {
		double DT = (1 / (double)Distance)*firePower;
		castle->GetTowerByRegion(Region)->TakeDamage(DT);
	}

}

bool Hidden::TakeDamage(Castle * castle,int StepTime)
{
	if (IsHide(StepTime))
	{
		Health -= ((1 / (double)Distance)*castle->GetTowerByRegion(Region)->GetFirePower());
		return (Health <= 0);
	}
}

TYPE Hidden::GetType()
{
	return HiddenType;
}

int Hidden::GetSpeed()
{
	return Speed;
}

bool Hidden::IsHide(int StepTime)
{
	if (StepTime == 1 || arrivalTime-StepTime % 5 == 0)
	{
		return true;
	}
	return false;
}
