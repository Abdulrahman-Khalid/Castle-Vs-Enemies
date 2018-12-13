#pragma once
#include "..\Defs.h"
#include <Windows.h>
#include <MMSystem.h>

class Tower
{
	double Health;
	double FirstHealth;
	int unpavedDistance;
	float TotalDamage;
	int attackNum;
	double firePower;
	double C1, C2, C3;
	int killedNum;
	int activeNum;
	int killedTime;
public:
	Tower();
	void initializeTower(double health, int attack_num, double fire_power, double C1, double C2, double C3);
	void SetHealth(double h);
	double GetHealth() const;
	double GetC1() const;
	double GetC2() const;
	double GetC3() const;
	void pave();
	int GetunpavedDistance() const;
	void TakeDamage(double Damage);
	bool isDestroyed() const;
	int GetFirePower() const;
	int GetAttackNum() const;
	int GetKilledTime() const;
	void SetKilledTime(int time);
	float GetTotalDamage() const;
	void AddToKilledNum(int n);
	void SetActiveNum(int n);
	int GetActiveNum();
	int GetKilledNum();
};