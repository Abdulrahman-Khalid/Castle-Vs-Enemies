#pragma once
#include "Enemy.h"
class Fighter
	:public Enemy
{
public:
	Fighter(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region,int);
	~Fighter();

	// Inherited via Enemy
	virtual void Move(Castle* castle, int TimeStep) override;
	virtual void Attack(Castle* castle, int TimeStep) override;

	// Inherited via Enemy
	virtual bool TakeDamage(Castle * castle,int StepTime) override;

	// Inherited via Enemy
	virtual TYPE GetType() override;
	int GetSpeed();
	bool IsHide(int);
};

