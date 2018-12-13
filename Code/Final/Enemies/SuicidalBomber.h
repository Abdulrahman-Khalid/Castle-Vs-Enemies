#pragma once
#include "Enemy.h"
class SuicidalBomber
	:public Enemy
{
public:
	SuicidalBomber(int id, int arrival_time, double health, double fire_power, REGION r_region, int rspeed);
	~SuicidalBomber();

	// Inherited via Enemy
	virtual void Move(Castle* castle, int TimeStep) override;
	virtual void Attack(Castle* castle, int TimeStep) override;

	// Inherited via Enemy
	virtual bool TakeDamage(Castle * castle,int TimeStep) override;

	// Inherited via Enemy
	virtual TYPE GetType() override;
	int GetSpeed();
	bool IsHide(int);
};

