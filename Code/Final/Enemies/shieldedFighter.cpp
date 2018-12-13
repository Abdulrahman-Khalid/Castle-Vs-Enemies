#include "shieldedFighter.h"
#include "..\Castle\Castle.h"

shieldedFighter::shieldedFighter(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region, int rSpeed)
	:Enemy(ORANGERED, r_region)
{
	S = id;
	arrivalTime = arrival_time;
	Health = health;
	firePower = fire_power;
	reloadPeriod = reload_period;
	Priority = 0;
	Speed = rSpeed;
}

shieldedFighter::~shieldedFighter()
{
}

void shieldedFighter::Move(Castle* castle, int TimeStep)
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
void shieldedFighter::SetPrioroty(Castle* castle, int TimeStep)
{
	int remaning_time_to_shot =reloadPeriod-((TimeStep - arrivalTime)%reloadPeriod);
	if (remaning_time_to_shot == reloadPeriod)
	{
		remaning_time_to_shot=0;
	}
	Priority = ((firePower*castle->GetTowerByRegion(Region)->GetC1() / Distance)) + (castle->GetTowerByRegion(Region)->GetC2() /
		(remaning_time_to_shot + 1)) + (Health*castle->GetTowerByRegion(Region)->GetC3());
}
double shieldedFighter::GetPriority() const
{
	return Priority;
}
void shieldedFighter::Attack(Castle* castle, int TimeStep)
{
	while (castle->GetTowerByRegion(Region)->isDestroyed()&&castle->GetTowerByRegion(Region)->GetKilledTime()<TimeStep)
	{
		int Reg=Region;
		Reg++;
		Reg=Reg%4;
		Region=(REGION)Reg;
		if (Distance < castle->GetTowerByRegion(Region)->GetunpavedDistance())
		{
			Distance = castle->GetTowerByRegion(Region)->GetunpavedDistance() + 1;
		}
	}
	int T = TimeStep - arrivalTime;
	int R = reloadPeriod + 1;
	if (T%R == 0) {
		double DT = (2 / (double)Distance)*firePower;
		castle->GetTowerByRegion(Region)->TakeDamage(DT);
	}
}

bool shieldedFighter::TakeDamage(Castle * castle,int StepTime)
{
	Health -= ((1/ (double)Distance)*castle->GetTowerByRegion(Region)->GetFirePower() * 0.5);
	return (Health <= 0);
}

TYPE shieldedFighter::GetType()
{
	return SHIELDEDFIGHTER;
}
int shieldedFighter::GetSpeed()
{
	return Speed;
}
bool shieldedFighter::IsHide(int StepTime)
{
	return true;
}