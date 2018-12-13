#include "Battle.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

Battle::Battle()
{
	EnemyCount = 0;
	ShelidedStartIndex = MaxEnemyCount;
	TimeStep = 1;
	Flag = false;
}

Battle::~Battle()
{
	Q1.destruct();
	Killed.destruct();
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < ShelidedStartIndex)
	{
		if (Ptr->GetType() == SHIELDEDFIGHTER)
		{
			Ptr->SetPrioroty(&BCastle, GetTimeStep());
			BEnemiesForDraw[--ShelidedStartIndex] = Ptr;
		}
		else
		{
			BEnemiesForDraw[EnemyCount++] = Ptr;
			Active.Enqueue(Ptr);
		}
	}
	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw,  EnemyCount,ShelidedStartIndex,TimeStep);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::DrawUnpavedArea(GUI * pGUI)
{
	Tower* Towers = BCastle.GetTowers();
	for (int i = 0; i < NoOfRegions; i++)
	{
		pGUI->DrawUnpavedArea(i, Towers[i].GetunpavedDistance());
	}
}

//void Battle::MoveEnemies()
//{
//	for (int i = 0; i < EnemyCount; i++)
//	{
//		BEnemiesForDraw[i]->Move(&BCastle, TimeStep);
//	}
//	for (int i = ShelidedStartIndex; i < MaxEnemyCount; i++)
//	{
//		BEnemiesForDraw[i]->Move(&BCastle, TimeStep);
//	}
//}
void Battle::HeapSortShelided()
{
	int n = MaxEnemyCount - ShelidedStartIndex;
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(n, i);

	// Heap sort
	for (int i = n - 1; i >= 0; i--)
	{
		Swap(BEnemiesForDraw[ShelidedStartIndex], BEnemiesForDraw[i + ShelidedStartIndex]);

		// Heapify root element to get highest element at root again
		Heapify(i, 0);
	}
}

void Battle::Heapify(int n, int i)
{
	// Find samllest among root, left child and right child
	int samllest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && BEnemiesForDraw[l + ShelidedStartIndex]->GetPriority() < BEnemiesForDraw[samllest + ShelidedStartIndex]->GetPriority())
	{
		samllest = l;
	}

	if (r < n && BEnemiesForDraw[r + ShelidedStartIndex]->GetPriority() < BEnemiesForDraw[samllest + ShelidedStartIndex]->GetPriority())
	{
		samllest = r;
	}

	// Swap and continue heapifying if root is not largest
	if (samllest != i)
	{
		Swap(BEnemiesForDraw[i + ShelidedStartIndex], BEnemiesForDraw[samllest + ShelidedStartIndex]);
		Heapify(n, samllest);
	}
}

void Battle::Swap(Enemy *& E1, Enemy *& E2)
{
	Enemy* Temp = E1;
	E1 = E2;
	E2 = Temp;
}

void Battle::incrementTimeStep()
{
	TimeStep++;
}

int Battle::GetTimeStep() const
{
	return TimeStep;
}

//Phase 1
//void Battle::Simulator()
//{
//	//SortShelided();
//	int a = 0, b = 0, c = 0, d = 0;
//	int N = 1;
//	bool flag = false;
//	List Temp;
//	for (int i = ShelidedStartIndex; i < MaxEnemyCount; i++)
//	{
//		flag = false;
//		BEnemiesForDraw[i]->Move(&BCastle, TimeStep);
//		BEnemiesForDraw[i]->Attack(&BCastle, TimeStep);
//		switch (BEnemiesForDraw[i]->GetRegion()) {
//		case A_REG:
//			if (a<N && !BCastle.GetTowerByRegion(A_REG)->isDestroyed())
//			{
//				flag = true;
//				a++;
//			}
//			break;
//		case B_REG:
//			if (b<N && !BCastle.GetTowerByRegion(B_REG)->isDestroyed())
//			{
//				flag = true;
//				b++;
//			}
//			break;
//		case C_REG:
//			if (c<N && !BCastle.GetTowerByRegion(C_REG)->isDestroyed())
//			{
//				flag = true;
//				c++;
//			}
//			break;
//		case D_REG:
//			if (d<N && !BCastle.GetTowerByRegion(D_REG)->isDestroyed())
//			{
//				flag = true;
//				d++;
//			}
//			break;
//		}
//		BEnemiesForDraw[i]->SetPrioroty(&BCastle, TimeStep);
//		if (flag)
//		{
//			int FD = BEnemiesForDraw[i]->GetFirstShotTime() - BEnemiesForDraw[i]->GetArrivalTime();
//			int KD = TimeStep - BEnemiesForDraw[i]->GetFirstShotTime();
//			Temp.add(TimeStep, BEnemiesForDraw[i]->GetSequence(), FD, KD);
//			delete BEnemiesForDraw[i];
//			BEnemiesForDraw[i] = BEnemiesForDraw[ShelidedStartIndex];
//			ShelidedStartIndex++;
//		}
//	}
//	for (int i = 0; i < EnemyCount; i++)
//	{
//		flag = false;
//		Enemy* CurrentEnemy = Active.GetEn();
//		Active.Dequeue();
//		CurrentEnemy->Move(&BCastle, TimeStep);
//		CurrentEnemy->Attack(&BCastle, TimeStep);
//		switch (CurrentEnemy->GetRegion()) {
//		case A_REG:
//			if (a<N)
//			{
//				flag = true;
//				a++;
//			}
//			break;
//		case B_REG:
//			if (b<N)
//			{
//				flag = true;
//				b++;
//			}
//			break;
//		case C_REG:
//			if (c<N)
//			{
//				flag = true;
//				c++;
//			}
//			break;
//		case D_REG:
//			if (d<N)
//			{
//				flag = true;
//				d++;
//			}
//			break;
//		}
//		if (flag)
//		{
//			int FD = CurrentEnemy->GetFirstShotTime() - CurrentEnemy->GetArrivalTime();
//			int KD = TimeStep - CurrentEnemy->GetFirstShotTime();
//			Temp.add(TimeStep, CurrentEnemy->GetSequence(), FD, KD);
//			delete CurrentEnemy;
//			CurrentEnemy = NULL;
//			EnemyCount--;
//			i--;
//		}
//		else
//		{
//			Active.Enqueue(CurrentEnemy);
//			BEnemiesForDraw[i] = CurrentEnemy;
//		}
//	}
//	Killed.connect(Temp);
//}

void Battle::SortShelided_MoveAll_AttackAll()
{
	HeapSortShelided();
	int a = 0, b = 0, c = 0, d = 0;
	int N = BCastle.GetTowerByRegion(A_REG)->GetAttackNum();
	if (N > 0 && (EnemyCount != 0 || ShelidedStartIndex != MaxEnemyCount))
	{
		mciSendString("stop fire.mp3", NULL, 0, NULL);
		mciSendString("play fire.mp3", NULL, 0, NULL);
	}
	bool flag = false;
	List Temp;
	int activeNumA = 0, activeNumB = 0, activeNumC = 0, activeNumD = 0;
	int killedNumA = 0, killedNumB = 0, killedNumC = 0, killedNumD = 0;
	for (int i = ShelidedStartIndex; i < MaxEnemyCount; i++)
	{
		flag = false;
		BEnemiesForDraw[i]->Move(&BCastle, TimeStep);
		BEnemiesForDraw[i]->Attack(&BCastle, TimeStep);
		
		
		REGION Region = BEnemiesForDraw[i]->GetRegion();
		if (BCastle.GetTowerByRegion(Region)->isDestroyed()&&BCastle.GetTowerByRegion(Region)->GetKilledTime()==-1)
		{
			BCastle.GetTowerByRegion(Region)->SetKilledTime(TimeStep);

		}
		switch (Region) {
		case A_REG:
			activeNumA++;
			if (a<N && !BCastle.GetTowerByRegion(A_REG)->isDestroyed())
			{
				flag = BEnemiesForDraw[i]->TakeDamage(&BCastle,TimeStep);
				if (BEnemiesForDraw[i]->GetFirstShotTime() == -1) {
					BEnemiesForDraw[i]->SetFirstShotTime(TimeStep);
				}
				a++;
			}
			break;
		case B_REG:
			activeNumB++;
			if (b<N && !BCastle.GetTowerByRegion(B_REG)->isDestroyed())
			{
				flag = BEnemiesForDraw[i]->TakeDamage(&BCastle,TimeStep);
				if (BEnemiesForDraw[i]->GetFirstShotTime() == -1) {
					BEnemiesForDraw[i]->SetFirstShotTime(TimeStep);
				}
				b++;
			}
			break;
		case C_REG:
			activeNumC++;
			if (c<N && !BCastle.GetTowerByRegion(C_REG)->isDestroyed())
			{
				flag = BEnemiesForDraw[i]->TakeDamage(&BCastle,TimeStep);
				if (BEnemiesForDraw[i]->GetFirstShotTime() == -1) {
					BEnemiesForDraw[i]->SetFirstShotTime(TimeStep);
				}
				c++;
			}
			break;
		case D_REG:
			activeNumD++;
			if (d<N && !BCastle.GetTowerByRegion(D_REG)->isDestroyed())
			{
				flag = BEnemiesForDraw[i]->TakeDamage(&BCastle,TimeStep);
				if (BEnemiesForDraw[i]->GetFirstShotTime() == -1) {
					BEnemiesForDraw[i]->SetFirstShotTime(TimeStep);
				}
				d++;
			}
			break;
		}
		BEnemiesForDraw[i]->SetPrioroty(&BCastle, TimeStep);
		if (flag)
		{
			switch (Region) {
			case A_REG:
				activeNumA--;
				killedNumA++;
				break; 
			case B_REG:
				activeNumB--;
				killedNumB++;
				break;
			case C_REG:
				activeNumC--;
				killedNumC++;
				break; 
			case D_REG:
				activeNumD--;
				killedNumD++;
				break;
			}
			int FD = BEnemiesForDraw[i]->GetFirstShotTime() - BEnemiesForDraw[i]->GetArrivalTime();
			int KD = TimeStep - BEnemiesForDraw[i]->GetFirstShotTime();
			Temp.add(TimeStep, BEnemiesForDraw[i]->GetSequence(), FD, KD);
			delete BEnemiesForDraw[i];
			BEnemiesForDraw[i] = BEnemiesForDraw[ShelidedStartIndex];
			BEnemiesForDraw[ShelidedStartIndex]=NULL;
			ShelidedStartIndex++;
		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		flag = false;
		Enemy* CurrentEnemy = Active.GetEn();
		Active.Dequeue();
		CurrentEnemy->Move(&BCastle, TimeStep);
		CurrentEnemy->Attack(&BCastle, TimeStep);
		REGION Region = CurrentEnemy->GetRegion();
		if (BCastle.GetTowerByRegion(Region)->isDestroyed()&&BCastle.GetTowerByRegion(Region)->GetKilledTime()==-1)
		{
			BCastle.GetTowerByRegion(Region)->SetKilledTime(TimeStep);

		}
		
		switch (Region)
		{
		case A_REG:
			activeNumA++;
			if (a<N && !BCastle.GetTowerByRegion(A_REG)->isDestroyed())
			{
				flag = CurrentEnemy->TakeDamage(&BCastle,TimeStep);
				if (CurrentEnemy->GetFirstShotTime() == -1) {
					CurrentEnemy->SetFirstShotTime(TimeStep);
				}
				a++;
			}
			break;
		case B_REG:
			activeNumB++;
			if (b<N && !BCastle.GetTowerByRegion(B_REG)->isDestroyed())
			{
				flag = CurrentEnemy->TakeDamage(&BCastle,TimeStep);
				if (CurrentEnemy->GetFirstShotTime() == -1) {
					CurrentEnemy->SetFirstShotTime(TimeStep);
				}
				b++;
			}
			break;
		case C_REG:
			activeNumC++;
			if (c<N && !BCastle.GetTowerByRegion(C_REG)->isDestroyed())
			{
				flag = CurrentEnemy->TakeDamage(&BCastle,TimeStep);
				if (CurrentEnemy->GetFirstShotTime() == -1) {
					CurrentEnemy->SetFirstShotTime(TimeStep);
				}
				c++;
			}
			break;
		case D_REG:
			activeNumD++;
			if (d<N && !BCastle.GetTowerByRegion(D_REG)->isDestroyed())
			{
				flag = CurrentEnemy->TakeDamage(&BCastle,TimeStep);
				if (CurrentEnemy->GetFirstShotTime() == -1) {
					CurrentEnemy->SetFirstShotTime(TimeStep);
				}
				d++;
			}
			break;
		}
		if (flag)
		{
			switch (Region) {
			case A_REG:
				activeNumA--;
				killedNumA++;
				break;
			case B_REG:
				activeNumB--;
				killedNumB++;
				break;
			case C_REG:
				activeNumC--;
				killedNumC++;
				break;
			case D_REG:
				activeNumD--;
				killedNumD++;
				break;
			}
			int FD = CurrentEnemy->GetFirstShotTime() - CurrentEnemy->GetArrivalTime();
			int KD = TimeStep - CurrentEnemy->GetFirstShotTime();
			Temp.add(TimeStep, CurrentEnemy->GetSequence(), FD, KD);
			delete CurrentEnemy;
			CurrentEnemy = NULL;
			EnemyCount--;
			i--;
		}
		else
		{
			Active.Enqueue(CurrentEnemy);
			BEnemiesForDraw[i] = CurrentEnemy;
		}
	}

	BCastle.GetTowerByRegion(A_REG)->SetActiveNum(activeNumA);
	BCastle.GetTowerByRegion(B_REG)->SetActiveNum(activeNumB);
	BCastle.GetTowerByRegion(C_REG)->SetActiveNum(activeNumC);
	BCastle.GetTowerByRegion(D_REG)->SetActiveNum(activeNumD);

	BCastle.GetTowerByRegion(A_REG)->AddToKilledNum(killedNumA);
	BCastle.GetTowerByRegion(B_REG)->AddToKilledNum(killedNumB);
	BCastle.GetTowerByRegion(C_REG)->AddToKilledNum(killedNumC);
	BCastle.GetTowerByRegion(D_REG)->AddToKilledNum(killedNumD);

	Killed.connect(Temp);
}

void Battle::FullQueue(Enemy * E)
{
	Q1.Enqueue(E);
}

void Battle::UpdateActive()
{
	bool Flag = true;
	while (Flag)
	{
		if (Q1.GetCounter() != 0)
		{
			if (Q1.QueueTop() > TimeStep)
			{
				Flag = false;
			}
			else if (Q1.QueueTop() == TimeStep)
			{
				AddEnemy(Q1.GetEn());
				Q1.Dequeue();
			}
			else
				Flag = false;
		}
		else
			Flag = false;
	}
}

void Battle::FullOutputFile(ofstream & Write)
{
	int counter = Killed.GetCounter();
	if (counter != 0)
	{
		Killed.BeforeGetToPrint();
		Write << "KTS\tS\tFD\tKD\tLT\n ";
		int kts, s, fd, kd;
		for (int i = 0; i < counter; i++)
		{
			Killed.GetToPrint(kts, s, fd, kd);
			Write << kts << "\t" << s << "\t" << fd << "\t" << kd << "\t" << fd + kd << "\n ";
		}
	}
	Write << "T1_Total_Damage   T1_Total_Damage   T1_Total_Damage   T1_Total_Damage\n    ";
	for (int i = A_REG; i < NoOfRegions; i++)
	{
		float TotalDamage = BCastle.GetTowerByRegion(i)->GetTotalDamage();
		Write << TotalDamage << "               ";
	}
	Write << "\n R1_Unpaved_Dist   R2_Unpaved_Dist   R3_Unpaved_Dist   R4_Unpaved_Dist\n    ";
	for (int i = A_REG; i < NoOfRegions; i++)
	{
		int unpaved = BCastle.GetTowerByRegion(i)->GetunpavedDistance();
		Write << unpaved << "                ";
	}
	Write << "\n ";
	if ((Q1.GetCounter() + EnemyCount + MaxEnemyCount - ShelidedStartIndex) == 0)
	{
		Write << "Game is WIN\n ";
		mciSendString("pause Bastard.mp3", NULL, 0, NULL);
		mciSendString("play win.mp3", NULL, 0, NULL);
	}
	else if (BCastle.isDestroyed())
	{
		Write << "Game is LOSS\n ";
		mciSendString("pause Bastard.mp3", NULL, 0, NULL);
		mciSendString("play lose.mp3", NULL, 0, NULL);
	}
	int TotalEnemies = Killed.GetCounter() + Q1.GetCounter() + EnemyCount + (MaxEnemyCount - ShelidedStartIndex);
	Write << "Total Enemies = " << TotalEnemies << "\n ";
	float avgFD = 0, avgKD = 0;
	avgFD = Killed.GetavgFD_KD(avgKD);
	Write << "Average First-Shot Delay = " << avgFD << "\n ";
	Write << "Average Kill Delay = " << avgKD;
}

bool Battle::GameIsOver() const
{ 
	return (((Q1.GetCounter() + EnemyCount + MaxEnemyCount - ShelidedStartIndex) == 0) || BCastle.isDestroyed());
}

void Battle::PrintMSG(GUI *pGUI)
{
	pGUI->ClearStatusBar();
	pGUI->DrawStatusBarBoxes();

	string msg = "Tower A INFO:";
	pGUI->PrintMessage(msg, A_REG);

	msg = "Unpaved Distance = " + to_string(BCastle.GetTowerByRegion(A_REG)->GetunpavedDistance())
		+ "                                     " + "Health = " + to_string(BCastle.GetTowerByRegion(A_REG)->GetHealth());
	pGUI->PrintMessage(msg, A_REG, 1);

	msg = "Number Of Active Enemies = " + to_string(BCastle.GetTowerByRegion(A_REG)->GetActiveNum())
		+ "                          Number Of Killed Enemies = " + to_string(BCastle.GetTowerByRegion(A_REG)->GetKilledNum());
	pGUI->PrintMessage(msg, A_REG, 2);

	msg = "Tower B INFO:";
	pGUI->PrintMessage(msg, B_REG);

	msg = "Unpaved Distance = " + to_string(BCastle.GetTowerByRegion(B_REG)->GetunpavedDistance())
		+ "                                     " + "Health = " + to_string(BCastle.GetTowerByRegion(B_REG)->GetHealth());
	pGUI->PrintMessage(msg, B_REG, 1);

	msg = "Number Of Active Enemies = " + to_string(BCastle.GetTowerByRegion(B_REG)->GetActiveNum())
		+ "                          Number Of Killed Enemies = " + to_string(BCastle.GetTowerByRegion(B_REG)->GetKilledNum());
	pGUI->PrintMessage(msg, B_REG, 2);

	msg = "Tower C INFO:";
	pGUI->PrintMessage(msg, C_REG);

	msg = "Unpaved Distance = " + to_string(BCastle.GetTowerByRegion(C_REG)->GetunpavedDistance())
		+ "                                     " + "Health = " + to_string(BCastle.GetTowerByRegion(C_REG)->GetHealth());
	pGUI->PrintMessage(msg, C_REG, 1);

	msg = "Number Of Active Enemies = " + to_string(BCastle.GetTowerByRegion(C_REG)->GetActiveNum())
		+ "                          Number Of Killed Enemies = " + to_string(BCastle.GetTowerByRegion(C_REG)->GetKilledNum());
	pGUI->PrintMessage(msg, C_REG, 2);

	msg = "Tower D INFO:";
	pGUI->PrintMessage(msg, D_REG);

	msg = "Unpaved Distance = " + to_string(BCastle.GetTowerByRegion(D_REG)->GetunpavedDistance())
		+ "                                     "  + "Health = " + to_string(BCastle.GetTowerByRegion(D_REG)->GetHealth());
	pGUI->PrintMessage(msg, D_REG, 1);

	msg = "Number Of Active Enemies = " + to_string(BCastle.GetTowerByRegion(D_REG)->GetActiveNum())
		+ "                          Number Of Killed Enemies = " + to_string(BCastle.GetTowerByRegion(D_REG)->GetKilledNum());
	pGUI->PrintMessage(msg, D_REG, 2);
}
//////////////////////////////////////////////////////////////////////


void Battle::LoadFun(GUI* pGUI)
{
	//Create files 
	/////////////////////////////////////////////////////////
	pGUI->PrintMessage("Enter the input file name without(.txt)");
	string input = pGUI->GetString();
	input += ".txt";
	pGUI->PrintMessage("Now, Enter the output file name without(.txt)");
	string output = pGUI->GetString();
	output += ".txt";
	OutPut = output;
	pGUI->PrintMessage("Select the mode to start game");
	//////////////////////////////////////////////////////////

	//Fill files
	//////////////////////////////////////////////////////////

	ifstream Read(input);
	if (!Read.is_open()) {
		throw "Error: Can't open the input file!";
	}
	double TH;
	int N;
	double TF;
	Read >> TH >> N >> TF;
	double C1, C2, C3;
	Read >> C1 >> C2 >> C3;
	GetCastle()->initialize(TH, N, TF, C1, C2, C3);
	int S;
	int TYP;
	int T;
	double H;
	double POW;
	int RLD;
	char R;
	int Sp;
	REGION region;
	Read >> S;
	while (S != -1) {
		Read >> TYP >> T >> H >> POW;
		if (TYP != SUICIDALBOMBER)
		{
			Read >> RLD;
		}
		Read >> R >> Sp;
		switch (R)
		{
		case 'A':
			region = A_REG;
			break;
		case 'B':
			region = B_REG;
			break;
		case 'C':
			region = C_REG;
			break;
		case 'D':
			region = D_REG;
			break;
		default:
			throw "Error: Wrong enemy type has been loaded!";
			break;
		}
		Enemy* createdEnemy = nullptr;
		switch (TYP)
		{
		case PAVER:
			createdEnemy = new Paver(S, T, H, POW, RLD, region,Sp);
			break;
		case FIGHTER:
			createdEnemy = new Fighter(S, T, H, POW, RLD, region,Sp);
			break;
		case SHIELDEDFIGHTER:
			createdEnemy = new shieldedFighter(S, T, H, POW, RLD, region,Sp);
			break;
		case HiddenType:
			createdEnemy = new Hidden(S, T, H, POW, RLD, region, Sp);
			break;
		case SUICIDALBOMBER:
			createdEnemy = new SuicidalBomber(S, T, H, POW, region, Sp);
			break;
		default:
			throw "Error: Wrong enemy type has been loaded!";
			break;
		}
		if (T == 1) {
			AddEnemy(createdEnemy);
		}
		else {
			FullQueue(createdEnemy);                                               //
		}
		Read >> S;
	}
	Read.close();

	//////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////

void Battle::WriteFun()
{
	ofstream Write(OutPut);
	FullOutputFile(Write);
	Write.close();
}
/////////////////////////////////////////////////////




void Battle::PlayMode(Mode M,GUI* pGUI,bool& Flag2)
{
	switch (M)
	{
	case InterActive && Flag  : 
		if (Flag)
		{
			pGUI->PrintMessage("You selected the interactive mode");
			PlayInterActive(pGUI, Flag2);
		}
		
		else
		{
			pGUI->PrintMessage("Please load the file first");
			PlayMode(SelectMode(pGUI), pGUI, Flag2);
		}
		break;
	case StepByStep  : 
		if (Flag)
		{
			pGUI->PrintMessage("You selected the step by step mode");
			PlayStepByStep(pGUI, Flag2);
		}
		else
		{
			pGUI->PrintMessage("Please load the file first");
			PlayMode(SelectMode(pGUI), pGUI, Flag2);
		}
		break;
	case Silent  : 
		if (Flag)
		{
				pGUI->PrintMessage("You selected the silent mode");
				PlaySilent(pGUI, Flag2);
		}
		else
		{
			pGUI->PrintMessage("Please load the file first");
			PlayMode(SelectMode(pGUI), pGUI, Flag2);
		}
		break;
	case Load : Flag = true; 
		LoadMode(pGUI, Flag2);
		break;
	case Empty: pGUI->PrintMessage("Select a mode form the modes bar");
		PlayMode(SelectMode(pGUI),pGUI, Flag2);
		break;
	case NewMode:
		if (Flag)
		{
			pGUI->PrintMessage("You can select this mode when you finish your game to start again");
		}
		else
		{
			pGUI->PrintMessage("Please load the file first");
			PlayMode(SelectMode(pGUI), pGUI, Flag2);
		}
		break;
	case Exit : ExitMode(pGUI,Flag2);
		break;
	};
}
/////////////////////////////////////////////////////

Mode Battle::SelectMode(GUI* pGUI)
{
	Point P;
	pGUI->GetPointClicked(P);

	if (P.y>0 && P.y < 50 && P.x<300)
	{
		int SlectedMode = (P.x / 50);

		switch (SlectedMode)
		{
		case INTERACTIVE: return InterActive;
		case STEP_BY_STEP: return StepByStep;
		case SILENT: return Silent;
		case MENU_LOAD: return Load;
		case MENU_EXIT: return Exit;
		case MENU_NEW: return NewMode;
		}
	}
	else
		return Empty;
}
//////////////////////////////////////////////////////

void Battle::PlayInterActive(GUI* pGUI,bool& Flag2)
{
	bool Flag100=true;
	bool Flag3 = true;
	Point p;
	pGUI->GetPointClicked(p);
	pGUI->ClearStatusBar();
	pGUI->ClearBattleArea();
	DrawEnemies(pGUI);
	DrawUnpavedArea(pGUI);		
	pGUI->DrawCastle(GetCastle());
	SortShelided_MoveAll_AttackAll();
	PrintMSG(pGUI);
	
	if (!GameIsOver())
	{
			while (Flag100)
		{
			if (GameIsOver())
			{
			
				Flag100=false;
				break;
			}
			pGUI->GetPointClicked(p);
			if (IsExit(p)==true)
			{
				ExitMode(pGUI,Flag2);
				break;
			}
			else if (IsNew(p)==true)
			{
				Flag3 = false;
				break;
			}
			pGUI->ClearStatusBar();
			pGUI->ClearBattleArea();
			SortShelided_MoveAll_AttackAll();
			DrawEnemies(pGUI);
			DrawUnpavedArea(pGUI);
			
			pGUI->DrawCastle(GetCastle());
			PrintMSG(pGUI);
			incrementTimeStep();
			UpdateActive();
		}
	}
	        pGUI->ClearStatusBar();
			pGUI->ClearBattleArea();
			DrawEnemies(pGUI);
			DrawUnpavedArea(pGUI);
			
			pGUI->DrawCastle(GetCastle());
			PrintMSG(pGUI);
			incrementTimeStep();
			UpdateActive();
	End();
	if(Flag3&&Flag2)
	{
		Sleep(2000);
		pGUI->PrintMessage("The Game is over , if you want to start again select the new mode");
		pGUI->GetPointClicked(p);
	}
	SelectAfterGameing(p,Flag2,pGUI);
}
void Battle::SelectAfterGameing(Point p,bool& Flag2, GUI* pGUI)
{
	while (!IsExit(p) && !IsNew(p))
	{
		Sleep(2000);
		pGUI->PrintMessage("The Game is over , if you want to start again select the new mode");
		pGUI->GetPointClicked(p);
	}
	if (IsNew(p) == true)
	{
		Flag2 = true;
	}
	else
	{
		Flag2 = false;
	}
}
void Battle::PlayStepByStep(GUI* pGUI,bool& Flag2)
{
	bool Flag100=true;
	Point p;
	pGUI->GetPointClicked(p);
	pGUI->ClearStatusBar();
	pGUI->ClearBattleArea();
	DrawEnemies(pGUI);
	DrawUnpavedArea(pGUI);		
	pGUI->DrawCastle(GetCastle());
	SortShelided_MoveAll_AttackAll();
	PrintMSG(pGUI);
	std::chrono::duration<int, std::milli> timespan(1000);
	if (!GameIsOver())
	{
			while (Flag100)
		{
			if (GameIsOver())
			{
				Flag100=false;
				break;
			}
		std::chrono::duration<int, std::milli> timespan(1000);
		std::this_thread::sleep_for(timespan);
		if (IsExit(p) == true)
		{
			ExitMode(pGUI,Flag2);
			break;
		}
		pGUI->ClearStatusBar();
		pGUI->ClearBattleArea();
		SortShelided_MoveAll_AttackAll();
		DrawEnemies(pGUI);
		DrawUnpavedArea(pGUI);
		pGUI->DrawCastle(GetCastle());
		PrintMSG(pGUI);
		incrementTimeStep();
		UpdateActive();
		}
	}
	 pGUI->ClearStatusBar();
	pGUI->ClearBattleArea();
	DrawEnemies(pGUI);
	DrawUnpavedArea(pGUI);		
	pGUI->DrawCastle(GetCastle());
	PrintMSG(pGUI);
	incrementTimeStep();
	UpdateActive();
	End();
	Sleep(2000);
	pGUI->PrintMessage("The Game is over , if you want to start again select the new mode");
	pGUI->GetPointClicked(p);
	SelectAfterGameing(p, Flag2, pGUI);

}
void Battle::PlaySilent(GUI* pGUI,bool& Flag2)
{
	/////////////////////////////////////////////////////
	bool Flag100=true;
	Point p;
	SortShelided_MoveAll_AttackAll();
	if (!GameIsOver())
	{
			while (Flag100)
		{
			if (GameIsOver())
			{
				Flag100=false;
				break;
			}
		SortShelided_MoveAll_AttackAll();
		incrementTimeStep();
		UpdateActive();
		}
	}
	incrementTimeStep();
	UpdateActive();

	End();
	pGUI->PrintMessage("The Game is over , if you want to start again select the new mode");
	pGUI->GetPointClicked(p);
	SelectAfterGameing(p, Flag2, pGUI);
	/////////////////////////////////////////////////////
}
void Battle::LoadMode(GUI* pGUI, bool& Flag2)
{
	LoadFun(pGUI);
	pGUI->PrintMessage("Select the mode to start the game");
	PlayMode(SelectMode(pGUI),pGUI,Flag2);
}
void Battle::ExitMode(GUI* pGUI,bool& Flag2)
{
	End();
	Flag2 = false;
}
bool Battle::IsExit(Point P)
{
	
	if (P.y>0 && P.y < 50)
	{
		int Result= P.x / 50 ;
		if (Result==MENU_EXIT)
			return true;
	}
	return false;
}
void Battle::End()
{
	WriteFun();
	Q1.destruct();
	Active.destruct();
	Killed.destruct();
}
bool Battle::IsNew(Point P)
{
	if (P.y>0 && P.y < 50)
	{
		int Result= P.x / 50 ;
		if (Result==MENU_NEW)
			return true;
	}
	return false;
}