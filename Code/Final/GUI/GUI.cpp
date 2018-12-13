#include "GUI.h"
//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	CastleColor = GRAY,
	LineColor = BLACK,
	MsgColor = DARKBLUE,		//Messages color
	BkGrndColor = LIGHTBLUE,	//Background color
	StatusBarColor = WHITE;
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,int region,int br) const	//Prints a message on status bar
{	
	pWind->SetPen(MsgColor, MsgSize);
	int fontSize = 20;
	pWind->SetFont(fontSize, PLAIN, BY_NAME, "Arial");
	fontSize *= 0.5;
	int y = WindHeight - (int)(StatusBarHeight / 1.02);
	int x = 5;
	switch(region)
	{
	case A_REG:
		y += br * fontSize * 1.7 + 5;
		break;
	case B_REG:
		x += WindWidth / 2;
		y += br * fontSize * 1.7 + 5;
		break;
	case C_REG:
		x += WindWidth / 2;
		y += br * fontSize * 1.7 + 12 + StatusBarHeight/2.5;
		break;
	case D_REG:
		y += br * fontSize * 1.7 + 12 + StatusBarHeight / 2.5;
		break;
	default:
		ClearStatusBar();
		break;
	};
	pWind->DrawString(x, y, msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[INTERACTIVE] = "images\\MenuItems\\interactive.jpg";
	MenuItemImages[STEP_BY_STEP] = "images\\MenuItems\\stepbystep.jpg";
	MenuItemImages[SILENT] = "images\\MenuItems\\silent.jpg";
	MenuItemImages[MENU_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\exit.jpg";
	MenuItemImages[MENU_NEW] = "images\\MenuItems\\icon-new.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BLACK, 5);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(StatusBarColor, 3);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(BkGrndColor, 3);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle(Castle* C) const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the castle
	pWind->SetPen(BLACK);
	pWind->SetBrush(CastleColor);
	pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(LineColor, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth / 2, MenuBarHeight, WindWidth / 2, WindHeight - StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth / 2, YHalfBattleArea - CastleWidth / 2, WindWidth / 2, YHalfBattleArea + CastleWidth / 2);
	pWind->DrawLine(WindWidth / 2 - CastleWidth / 2, YHalfBattleArea, WindWidth / 2 + CastleWidth / 2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(BLACK);
	/*
	pWind->SetBrush(WHITE);
	pWind->DrawCircle((CastleStartX + L / 2), (CastleStartY + L / 2), 15);
	pWind->DrawCircle((CastleStartX + L / 2), (CastleEndY - L / 2), 15);
	pWind->DrawCircle((CastleEndX - L / 2), (CastleStartY + L / 2), 15);
	pWind->DrawCircle((CastleEndX - L / 2), (CastleEndY - L / 2), 15);
	*/
	pWind->SetBrush(DARKGRAY);
	int X1 = CastleStartX + 7;
	int X2 = X1 + 25;
	int Y1 = CastleStartY + 7;
	int Y2 = Y1 + 25;
	for (int i = 0; i < 36; i++)
	{
		if (i == 7 || i == 10 || i == 25 || i == 28) {
			X1 += 40;
			X2 += 40;
			continue;
		}
		pWind->DrawRectangle(X1, Y1, X2, Y2);
		X1 += 40;
		X2 += 40;
		if ((i + 1) % 6 == 0) {
			X1 = CastleStartX + 7;
			X2 = X1 + 25;
			Y1 += 40;
			Y2 += 40;
		}
	}
	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BLACK);
	pWind->SetFont(25, BOLD, BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5 * L / 12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5 * L / 12, "D");
	pWind->DrawString(WindWidth / 2 + 0.44*L, CastleStartY + 5 * L / 12, "B");
	pWind->DrawString(WindWidth / 2 + 0.44*L, YHalfBattleArea + 5 * L / 12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance * EnemyWidth - MaxDistance - 1, MenuBarHeight,
		CastleStartX - MaxDistance * EnemyWidth - MaxDistance - 1, WindHeight - StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance * EnemyWidth + MaxDistance + 1, MenuBarHeight,
		CastleEndX + MaxDistance * EnemyWidth + MaxDistance + 1, WindHeight - StatusBarHeight);
	pWind->SetPen(RED, 3);
	if (C->GetTowerByRegion(A_REG)->isDestroyed()) { // Tower A destroyed
		pWind->DrawLine(CastleStartX, CastleStartY, CastleStartX + L, CastleStartY + L);
		pWind->DrawLine(CastleStartX + L, CastleStartY, CastleStartX, CastleStartY + L);
	}
	if (C->GetTowerByRegion(B_REG)->isDestroyed()) { // Tower B destroyed
		pWind->DrawLine(CastleEndX, CastleStartY, CastleEndX - L, CastleStartY + L);
		pWind->DrawLine(CastleEndX - L, CastleStartY, CastleEndX, CastleStartY + L);
	}
	if (C->GetTowerByRegion(C_REG)->isDestroyed()) { // Tower C destroyed
		pWind->DrawLine(CastleEndX, CastleEndY, CastleEndX - L, CastleEndY - L);
		pWind->DrawLine(CastleEndX - L, CastleEndY, CastleEndX, CastleEndY - L);
	}
	if (C->GetTowerByRegion(D_REG)->isDestroyed()) { // Tower D destroyed
		pWind->DrawLine(CastleStartX, CastleEndY - L, CastleStartX + L, CastleEndY);
		pWind->DrawLine(CastleStartX + L, CastleEndY - L, CastleStartX, CastleEndY);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawStatusBarBoxes() const
{
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, MenuBarHeight + BattleAreaHeight + 7 + StatusBarHeight / 2.5, WindWidth, MenuBarHeight + 7 + BattleAreaHeight + StatusBarHeight / 2.5);
	pWind->DrawLine(WindWidth / 2, WindHeight - StatusBarHeight, WindWidth / 2, WindHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int start, int size,int StepTime) const
{
	//draw enemies at each region 
	for (int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
								// else print number of enemy in the region
		bool draw = true;
		for (int distance = MaxDistance; distance >= MinDistance; distance--)
		{
			CountEnemies = 0;

			for (int i = 0; i < start; i++)
			{
				if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			for (int i = size; i < 300; i++)
			{
				if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if (CountEnemies > 15)
			{
				draw = false;
				break;
			}
		}
		if (draw)
		{
			for (int distance = MaxDistance; distance > 1; distance--)
			{
				CountEnemies = 0;

				for (int i = 0; i < start; i++)
				{
					if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region && enemies[i]->IsHide(StepTime))
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
				for (int i = size; i < 300; i++)
				{
					if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region && enemies[i]->IsHide(StepTime))
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region + 1) +
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawUnpavedArea(int region_num, int unpaved_dist) const
{
	int L = CastleWidth / 2;
	int X1, X2, Y1, Y2;
	switch (region_num) {
	case A_REG:
		pWind->SetPen(LineColor);
		pWind->SetBrush(GRAY);
		X1 = CastleStartX - (EnemyWidth + 1) * (unpaved_dist);
		X2 = CastleStartX;
		Y1 = MenuBarHeight;
		Y2 = CastleEndY - L;
		pWind->DrawRectangle(X1, Y1, X2, Y2);
		break;
	case B_REG:
		pWind->SetPen(LineColor);
		pWind->SetBrush(SEASHELL);
		X1 = CastleEndX;
		X2 = CastleEndX + (EnemyWidth+1) * (unpaved_dist);
		Y1 = MenuBarHeight;
		Y2 = CastleEndY - L;
		pWind->DrawRectangle(X1, Y1, X2, Y2);
		break;	
	case C_REG:
		pWind->SetPen(LineColor);
		pWind->SetBrush(NAVYBLUE);
		X1 = CastleEndX;
		X2 = CastleEndX + (EnemyWidth+1) * (unpaved_dist );
		Y1 = CastleEndY - L;
		Y2 = WindHeight - StatusBarHeight;
		pWind->DrawRectangle(X1, Y1, X2, Y2);
		break;
	case D_REG:
		pWind->SetPen(LineColor);
		pWind->SetBrush(PALEGREEN);
		X1 = CastleStartX - (EnemyWidth+1) * (unpaved_dist );
		X2 = CastleStartX;
		Y1 = CastleEndY - L;
		Y2 = WindHeight - StatusBarHeight;
		pWind->DrawRectangle(X1, Y1, X2, Y2);
		break;
	default:
		break;
	}
}