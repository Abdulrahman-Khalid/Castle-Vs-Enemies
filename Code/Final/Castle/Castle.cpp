#include "Castle.h"

#include "..\GUI\GUI.h"

Castle::Castle()
{
}

void Castle::initialize(double health, int attack_num, double fire_power, double C1, double C2, double C3)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].initializeTower(health, attack_num, fire_power, C1, C2, C3);
	}
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}

Tower * Castle::GetTowers()
{
	return Towers;
}

Tower * Castle::GetTowerByRegion(int R)
{
	return (R >= NoOfRegions || R < 0) ? nullptr : &(Towers[R]);
}

bool Castle::isDestroyed() const
{
	return (Towers[A_REG].isDestroyed() && Towers[B_REG].isDestroyed() && Towers[C_REG].isDestroyed() && Towers[D_REG].isDestroyed());
}
