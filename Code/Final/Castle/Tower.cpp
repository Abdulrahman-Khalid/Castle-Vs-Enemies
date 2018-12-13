#include "Tower.h"
Tower::Tower()
{
	TotalDamage = killedNum = activeNum = 0;
	killedTime = -1;
}
int Tower::GetKilledTime() const
{
	return killedTime;
}
void Tower::SetKilledTime(int time)
{
	killedTime = time;
}

void Tower::initializeTower(double health, int attack_num, double fire_power,double C1,double C2, double C3)
{
	SetHealth(health);
	FirstHealth = health;
	unpavedDistance = 30;
	firePower = fire_power;
	attackNum = attack_num;
	this->C1 = C1;
	this->C2 = C2;
	this->C3 = C3;
}

void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return (Health <= 0) ? 0 : Health;
}
double Tower::GetC1() const
{
	return C1;
}
double Tower::GetC2() const
{
	return C2;
}
double Tower::GetC3() const
{
	return C3;
}

void Tower::pave()
{
	if (unpavedDistance >= MinDistance) {
		unpavedDistance--;
		mciSendString("stop Pave.mp3", NULL, 0, NULL);
		mciSendString("play Pave.mp3", NULL, 0, NULL);
	}
}

int Tower::GetunpavedDistance() const
{
	return unpavedDistance;
}

void Tower::TakeDamage(double Damage)
{
	Health -= Damage;
}

bool Tower::isDestroyed() const
{
	return Health <= 0;
}

int Tower::GetFirePower() const
{
	return firePower;
}

int Tower::GetAttackNum() const
{
	return attackNum;
}

float Tower::GetTotalDamage() const
{
	if (isDestroyed()) {
		return FirstHealth;
	}
	return FirstHealth - Health;
}

void Tower::AddToKilledNum(int n)
{
	killedNum += n;
}

void Tower::SetActiveNum(int n)
{
	activeNum = n;
}

int Tower::GetActiveNum()
{
	return activeNum;
}

int Tower::GetKilledNum()
{
	return killedNum;
}