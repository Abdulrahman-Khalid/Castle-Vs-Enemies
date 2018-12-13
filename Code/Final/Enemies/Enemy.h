#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class Castle;
class Tower;
// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{
protected:
	int S;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	int arrivalTime;
	double firePower;
	int reloadPeriod;
	int T_FirstShot;
	int Speed;
public:
	Enemy(color r_c, REGION r_region, int d = MaxDistance);
	virtual ~Enemy();

	color GetColor() const;
	REGION GetRegion() const;

	void DecrementDist();

	void SetDistance(int d);
	int GetDistance() const;
	int GetArrivalTime() const;
	void SetFirstShotTime(int T);
	int	GetFirstShotTime() const;
	bool isKilled() const;
	int GetSequence() const;
	double GetHealth() const;
	int GetFirePower() const;
	int GetReloadPeriod() const;
	virtual int GetSpeed() = 0;
	virtual bool IsHide(int) = 0;

	// Virtual Functions: ----------------

	virtual void Move(Castle* castle, int TimeStep) = 0;	    //All enemies can move
	virtual void Attack(Castle* castle, int TimeStep) = 0;	//All enemies can attack (attacking is paving or shooting)
	virtual bool TakeDamage(Castle* castle,int StepTime) = 0;
	virtual TYPE GetType() = 0;
	virtual void SetPrioroty(Castle* castle, int TimeStep);
	virtual double GetPriority() const;
};