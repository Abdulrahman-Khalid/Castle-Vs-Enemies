#pragma once
#include "Enemy.h"
class shieldedFighter
	:public Enemy
{
	double Priority;
public:
	shieldedFighter(int id, int arrival_time, double health, double fire_power, int reload_period, REGION r_region, int rspeed);
	~shieldedFighter();

	// Inherited via Enemy
	virtual void Move(Castle* castle, int TimeStep) override;
	virtual void Attack(Castle* castle, int TimeStep) override;

	// Inherited via Enemy
	virtual bool TakeDamage(Castle * castle,int StepTime) override;

	// Inherited via Enemy
	virtual TYPE GetType() override;
	virtual void SetPrioroty(Castle* castle, int TimeStep)override;
	virtual double GetPriority() const override;
	int GetSpeed();
	bool IsHide(int);
};