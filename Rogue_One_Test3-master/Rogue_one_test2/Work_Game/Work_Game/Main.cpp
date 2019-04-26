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

	delayed_out_2("Welcome to a rogue test");
	while (true) {
		Ask_Action();
		if (True_Choice == "load") { Load_Game(); Loaded = true; break; }
		else if (True_Choice == "new") { New = true; break; };
	};

	while (Game_Run) {
		if (!Loaded && New) {
			Tutorial();
		};
		if (!player.In_Fight) {
			delayed_out_2("\nVoice: 'What would you like to do? ' ");
			while (true) {
			Ask_Action();
			if (True_Choice == "wander") {delayed_out_2("\nYou have chosen to wander the halls"); Wander_Halls();  break; }
			else if (True_Choice == "save") { Save_Game(); delayed_out_2("\nYour game has been saved"); break; }
			else if (True_Choice == "exit") { break; Game_Run = false; };
			};
		};
		if (player.In_Fight) {
			Mob_Fighter();
			Attack_Sequence();		
		};

		};
	if (player.Health == 0) {
		ofstream save_file;
		save_file.open("Save_File.txt", ofstream::trunc);
		delayed_out_2("\nVoice: 'You as many others were taking but the underground labyrinth' ");
		delayed_out_2("\nVoice: 'Taken by the Monsters within' ");
		delayed_out_2("\nVoice: 'Now your soul will walk these unholy grounds in search of a way out...' ");
		delayed_out_2("\nYou have Died");
		sleep_for(seconds(10));
	}
	else { delayed_out_2("\nVoice: 'You Find a soft place to sleep forgeting the area around you to find slumber...' "); };
	sleep_for(seconds(10));
	};
