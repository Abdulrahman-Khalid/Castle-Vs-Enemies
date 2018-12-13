#include "SuicidalBomber.h"
#include "..\Castle\Castle.h"


SuicidalBomber::SuicidalBomber(int id, int arrival_time, double health, double fire_power, REGION r_region, int rspeed) 
	:Enemy(DARKRED, r_region)
{
	S = id;
	arrivalTime = arrival_time;
	Health = health;
	firePower = fire_power;
	reloadPeriod = 0;
	Speed = rspeed;
}

SuicidalBomber::~SuicidalBomber()
{
}


void SuicidalBomber::Move(Castle* castle, int TimeStep)
{
	int DD = Distance - GetSpeed();
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


void SuicidalBomber::Attack(Castle* castle, int TimeStep)
{
	while (castle->GetTowerByRegion(Region)->isDestroyed() && castle->GetTowerByRegion(Region)->GetKilledTime()<TimeStep)
	{
		int Reg = Region;
		Reg++;
		Reg = Reg % 4;
		Region = (REGION)Reg;
		if (Distance < castle->GetTowerByRegion(Region)->GetunpavedDistance())
		{
			Distance = castle->GetTowerByRegion(Region)->GetunpavedDistance() + 1;
		}
	}
	if (Distance == 2)
	{
		mciSendString("play GUN.mp3", NULL, 0, NULL);
		double DT = 10 * ((1 / (double)Distance)*firePower);
		castle->GetTowerByRegion(Region)->TakeDamage(DT);
		Health = -1;
	}
}


bool SuicidalBomber::TakeDamage(Castle * castle,int TimeStep)
{
	Health -= ((1 / (double)Distance)*castle->GetTowerByRegion(Region)->GetFirePower());
	return (Health <= 0);
}


TYPE SuicidalBomber::GetType()
{
	return SUICIDALBOMBER;
}
int SuicidalBomber::GetSpeed()
{
	return Speed;
}

bool SuicidalBomber::IsHide(int StepTime)
{
	return true;
}