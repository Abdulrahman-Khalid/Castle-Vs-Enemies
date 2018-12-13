#include "Battle.h"
#include "GUI\GUI.h"

int main()
{
	bool Flag=true;
	do
	{
		GUI * pGUI = new GUI;
		Battle* pGameBattle = new Battle;
		Point p;

		mciSendString("open Bastard.mp3 type mpegvideo", NULL, 0, NULL);
		mciSendString("play Bastard.mp3 repeat", NULL, 0, NULL);

		////////////////////////////////////////////////////

		pGUI->PrintMessage("Select the load to load the file then select the mode of game");
		pGameBattle->PlayMode(pGameBattle->SelectMode(pGUI), pGUI, Flag);
		
		delete pGameBattle;
		delete pGUI;
	} while (Flag);
	return 0;
}