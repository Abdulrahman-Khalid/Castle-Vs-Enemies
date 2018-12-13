#pragma once

//#include "..\Defs.h" //7atetha f el tower
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];
public:
	Castle();
	void initialize(double health, int attack_num, double fire_power, double C1, double C2, double C3);
	void SetTowersHealth(double h);
	Tower* GetTowers();
	Tower* GetTowerByRegion(int R);
	bool isDestroyed() const;
}; 
