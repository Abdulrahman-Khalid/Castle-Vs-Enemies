#include "Enemy.h"

Enemy::Enemy(color r_c, REGION r_region, int d)
{
	Clr = r_c;
	Region = r_region;
	SetDistance(d);
	T_FirstShot = -1;
}

Enemy::~Enemy()
{
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
	{
		Distance -= GetSpeed();
		mciSendString("open pave.mp3 type mpegvideo", NULL, 0, NULL);
	}
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrivalTime() const
{
	return arrivalTime;
}

void Enemy::SetFirstShotTime(int T)
{
	T_FirstShot = T;
}

int Enemy::GetFirstShotTime() const
{
	return T_FirstShot;
}

bool Enemy::isKilled() const
{
	return (Health <= 0);
}

int Enemy::GetSequence() const
{
	return S;
}

double Enemy::GetHealth() const
{
	return Health;
}

int Enemy::GetFirePower() const
{
	return firePower;
}

int Enemy::GetReloadPeriod() const
{
	return reloadPeriod;
}

void Enemy::SetPrioroty(Castle* castle, int TimeStep)
{
}

double  Enemy::GetPriority() const
{
	return 0;
}