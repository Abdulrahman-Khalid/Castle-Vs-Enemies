#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Paver.h"
#include "Enemies\shieldedFighter.h"
#include "Enemies\Hidden.h"
#include "Enemies\SuicidalBomber.h"

#include "Castle\Castle.h"
#include "DS\Queue.h"
#include "DS\List.h"
#include <fstream>
// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ShelidedStartIndex;
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
											// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	int TimeStep;
	Queue Active;
	Queue Q1;
	List Killed;
	void HeapSortShelided();
	void Heapify(int n, int i);
	void Swap(Enemy*& E1, Enemy*& E2);
	string OutPut;
	bool Flag;
public:
	Battle();
	~Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	void DrawUnpavedArea(GUI * pGUI);
	//void MoveEnemies();
	void incrementTimeStep();
	int GetTimeStep() const;
	//void Simulator();
	void SortShelided_MoveAll_AttackAll();
	void FullQueue(Enemy* E);
	//void UpdateKilled(GUI* pGUI);
	void UpdateActive();
	void FullOutputFile(ofstream & Write);
	bool GameIsOver() const;
	void PrintMSG(GUI* pGUI);
	void LoadFun(GUI*);
	void WriteFun();
	Mode SelectMode(GUI*);
	void PlayMode(Mode,GUI*,bool&);
	void PlayInterActive(GUI*,bool&);
	void PlayStepByStep(GUI*, bool&);
	void PlaySilent(GUI*,bool&);
	void LoadMode(GUI*,bool&);
	void ExitMode(GUI*,bool&);
	bool IsExit(Point);
	void End();
	bool IsNew(Point);
	void SelectAfterGameing(Point, bool& ,GUI*);
};