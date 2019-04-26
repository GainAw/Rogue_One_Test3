#include "System_Actions.h"
#include "Characters.h"

//Windows terminal redraw size !!ONLY FOR WINDOWS!!
#define _WIN32_WINNT 0x0500
#include <windows.h>


int main() {
	/*
	Rogue Lite Text based Adventure
	*/

	//Windows terminal redraw size !!ONLY FOR WINDOWS!!
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 800, true);

	while (Game_Run) {
		delayed_out_2("Welcome to a rogue test");
		Ask_Action();
		if (True_Choice == "save") { player.Name = "will"; player.Age = 7; Save_Game();  player.Name = "";  Load_Game(); };
		if (!Loaded || New) {
			Tutorial();

			}
		};
	};
