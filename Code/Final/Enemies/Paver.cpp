#include "Paver.h"
#include "..\Castle\Castle.h"

Paver::Paver(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region, int rSpeed)
	:Enemy(DARKBLUE, r_region)
{
	S = id;
	arrivalTime = arrival_time;
	Health = health;
	firePower = fire_power;
	reloadPeriod = reload_period;
	Speed = rSpeed;
}

Paver::~Paver()
{
}

void Paver::Move(Castle* castle, int TimeStep)
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

void Paver::Attack(Castle* castle, int TimeStep)
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
	if (Distance > MinDistance) {
		int T = TimeStep - arrivalTime;
		int R = reloadPeriod + 1;
		int D;
		if (T%R == 0) {
			for (int i = 0; i < firePower; i++) {
				D = castle->GetTowerByRegion(Region)->GetunpavedDistance();
				if (D >Distance - GetSpeed()) {
					Distance=D+1;
				}
				if(D==Distance-1){
					castle->GetTowerByRegion(Region)->pave();
					if (Distance > MinDistance)
					Distance--;
					}
				}
				if(D!=Distance-GetSpeed() && D <Distance - GetSpeed())
				DecrementDist();
			}
		}
	}

bool Paver::TakeDamage(Castle * castle,int StepTime)
{
	Health -= ((1 / (double)Distance)*castle->GetTowerByRegion(Region)->GetFirePower());
	return (Health <= 0);
}

TYPE Paver::GetType()
{
	return PAVER;
}
int Paver::GetSpeed()
{
	return Speed;
}
bool Paver::IsHide(int StepTime)
{
	return true;
}