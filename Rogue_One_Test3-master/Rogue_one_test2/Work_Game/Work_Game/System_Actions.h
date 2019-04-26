#include <string>
#include <locale>
#include <iostream>
#include <chrono>
#include <thread>
#include "Characters.h"
#include <fstream>


using namespace this_thread;
using namespace chrono;

extern Player player;
extern Rat rat;
extern Goblin goblin;
extern Orc orc;
extern Tutorial_mob tutorial_mob;

string Choice_Input;
string True_Choice;
locale loc;
bool Loaded = false;
bool New = false;
bool First_Time_Asked = true;
bool Game_Run = true;

//All comments are so that as I update or fix game it will be easy to read as well

//This code was provided by Noah thank you
void delayed_out_2(const std::string& message,
	milliseconds letter_delay = milliseconds(75))
{
	const std::size_t msgLen = message.length();
	const std::string erasure_string = std::string(msgLen, '\b') +
		std::string(msgLen, ' ') + std::string(msgLen, '\b');

	std::size_t msgIdx = 0;

	while (msgIdx != msgLen)
	{
		std::cout << message[msgIdx++];
		std::this_thread::sleep_for(letter_delay);
	}
};



//universal function to get user input
void Ask_Action() {
	getline(cin, Choice_Input);
	True_Choice.resize(Choice_Input.length());
	for (string::size_type i = 0; i < Choice_Input.length(); ++i)
		True_Choice[i] = tolower(Choice_Input[i], loc);
};



//The attack sequence
void Attack_Sequence() {
	delayed_out_2("\nYou have entered a fight with a "); cout << player.Mob_Name << endl;
	int Player_Stun_Time = 0;
	int Mob_Stun_Time = 0;
	while (player.Health > 0 && player.Mob_Health > 0) {

		//Monster stun timer
		if (player.Mob_Stun && Mob_Stun_Time == 1) { player.Mob_Stun = false; Mob_Stun_Time = 0; }
		else if (player.Mob_Stun && Mob_Stun_Time != 1) { Mob_Stun_Time++; };

		//Player stun timer
		if (player.Player_Stun && Player_Stun_Time == 1) { player.Player_Stun = false; Player_Stun_Time = 0; }
		else if(player.Player_Stun && Player_Stun_Time != 1){ Player_Stun_Time++; };

		if (!player.Player_Stun) {
			Ask_Action();
			if (True_Choice != "block" && True_Choice != "attack") { continue;};
		}

		else if (player.Player_Stun) {
			delayed_out_2("\nYou are stunned! And can't move this turn!\n");
		};

		//This is used when the monster blocks
		if (rand() % 2 == 1) {
			if(True_Choice == "block" && !player.Player_Stun && !player.Mob_Stun) {
				delayed_out_2("\nYour block does nothing and the monster blocked itself, how weird\n"); player.Mob_Braced = true;
			}

		else if (True_Choice == "attack" && !player.Player_Stun && !player.Mob_Stun) {
					player.Mob_Health = player.Mob_Health - (player.Damage) / 2;
					delayed_out_2("\nIts health is at ");cout << player.Mob_Health << endl;
					if (rand() % 2 == 1) {
						player.Player_Stun = true;
						delayed_out_2("\nYou are stunned!"); cout << endl;
					};
			}
		else if (True_Choice == "attack" && !player.Player_Stun && player.Mob_Stun) {
					player.Mob_Health = player.Mob_Health - player.Damage;
					delayed_out_2("\nIts health is at "); cout << player.Mob_Health << endl;
			}

		else if (player.Player_Stun && !player.Mob_Stun) {
				delayed_out_2("\nYou were stunned but it blocked"); cout << endl;
			};
		}

		//This is the transition to when the monster attacks
		else {
			if (True_Choice == "block" && !player.Player_Stun && !player.Mob_Stun) {
					player.Health = player.Health - (player.Mob_Damage) / 2;
					if (rand() % 2 == 1) {
						player.Mob_Stun = true; delayed_out_2("\nThe monster is stunned\n");
					};
					delayed_out_2("\nYour health is "); cout << player.Health << endl;
			}

			else if (True_Choice == "attack" && !player.Mob_Stun && !player.Player_Stun) {
					player.Health = player.Health - player.Mob_Damage;
					player.Mob_Health = player.Mob_Health - player.Damage;
					delayed_out_2("\nIts health is "); cout << player.Mob_Health << endl;
					delayed_out_2("\nYour health is "); cout << player.Health << endl;
			}

			else if (player.Player_Stun && !player.Mob_Stun) {
					player.Health = player.Health - player.Mob_Damage;
					delayed_out_2("\nYour health is "); cout << player.Health << endl;
			}
			else if (True_Choice == "attack" && !player.Player_Stun && player.Mob_Stun) {
					player.Mob_Health = player.Mob_Health - player.Damage;
					delayed_out_2("\nIts health is "); cout << player.Mob_Health << endl;
			}
			else if (True_Choice == "block" && !player.Player_Stun && player.Mob_Stun) {
				delayed_out_2("\nYou blocked but it was stunned"); cout << endl;
			}
		};
	};
	player.In_Fight = false;
	if (player.Health > 0) { player.Health = 100; delayed_out_2("\nVoice: 'I have restored your health'"); };
	if (player.Health <= 0) { delayed_out_2("\nVoice: 'You have been slain'"); };

};




//function to wander the halls
void Wander_Halls() {
	int Halls_Number = rand() % 3;
	int Hall_Sides;
	bool left = false;
	bool right = false;
	bool top = false;
	int Fight_Mob = rand() % 3;
	if (Halls_Number == 3) {
		left = true;
		right = true;
		top = true;
	}
	else if (Halls_Number == 2) {
		Hall_Sides = rand() % 3;
		if (Hall_Sides == 3) { left = true; top = true; }
		else if (Hall_Sides == 2) { right = true; top = true; }
		else { right = true; left = true; };
	}
	else {
		Hall_Sides = rand() % 3;
		if (Hall_Sides == 3) { left = true; }
		else if (Hall_Sides == 2) { top = true; }
		else { right = true; };
	};
	if (left && right && top) {
		delayed_out_2("\nYou can go Left, Right or Straight.");
		while (true) {
			Ask_Action();
			if (True_Choice == "left") { delayed_out_2("\nYou have gone left\n"); break; }
			else if (True_Choice == "right") { delayed_out_2("\nYou have gone right\n"); break; }
			else if (True_Choice == "straight") { delayed_out_2("\nYou have gone top\n"); break; }
		};
	}
	else if (left && right) {
		delayed_out_2("\nYou can go Left or Right.");
		while (true) {
			Ask_Action();
			if (True_Choice == "left") { delayed_out_2("\nYou have gone left\n"); break; }
			else if (True_Choice == "right") { delayed_out_2("\nYou have gone right\n"); break; }
		};
	}
	else if (left && top) {
		delayed_out_2("\nYou can go Left or Straight.");
		while (true) {
			Ask_Action();
			if (True_Choice == "left") { delayed_out_2("\nYou have gone left\n"); break; }
			else if (True_Choice == "top") { delayed_out_2("\nYou have gone top\n"); break; }
		};
	}
	else if (top && right) {
		delayed_out_2("\nYou can go Right or Straight.");
		while (true) {
			Ask_Action();
			if (True_Choice == "right") { delayed_out_2("\nYou have gone right\n"); break; }
			else if (True_Choice == "top") { delayed_out_2("\nYou have gone top\n"); break; }
		};
	}
	else if (top) { delayed_out_2("\nyou go top\n"); }
	else if (left) { delayed_out_2("\nyou go left\n"); }
	else if (right) { delayed_out_2("\nyou go right\n"); };

	//this determines if you get into a fight or not
	if (Fight_Mob != 3) { player.In_Fight = true; };
};

//used to be a function here it was redundant



//This function determins what you fight
void Mob_Fighter() {
	int Mob_Champion = rand() % 4;
	switch (Mob_Champion) {
	case 1:
	{
		player.Mob_Name = rat.Name;
		player.Mob_Health = rat.Health;
		player.Mob_Damage = rat.Damage;
	} break;
	case 2:
	{
		player.Mob_Name = zombie.Name;
		player.Mob_Health = zombie.Health;
		player.Mob_Damage = zombie.Damage;
	}break;
	case 3:
	{
		player.Mob_Name = orc.Name;
		player.Mob_Health = orc.Health;
		player.Mob_Damage = orc.Damage;
	}break;
	case 4:
	{
		player.Mob_Name = goblin.Name;
		player.Mob_Health = goblin.Health;
		player.Mob_Damage = goblin.Damage;
	}break;
	};
};



//These functions are going to be save and load

void Save_Game() {
	ofstream save_file;
	save_file.open("Save_File.txt");
	save_file << player.Name << endl;
	save_file << player.Age << endl;
	save_file << player.Gender << endl;
	save_file << player.Health << endl;
	save_file << player.Damage << endl;
	save_file.close();
};
void Load_Game() {
	ifstream save_file;
	string Num_Holder;
	save_file.open("Save_File.txt");
	getline(save_file, player.Name);
	getline(save_file, Num_Holder);
	player.Age = stod(Num_Holder);
	getline(save_file, player.Gender);
	getline(save_file, Num_Holder);
	player.Health = stod(Num_Holder);
	getline(save_file, Num_Holder);
	player.Damage = stod(Num_Holder);
};

//This is the intro to the game of a new game
void Tutorial() {
	delayed_out_2("As any person who has been unconscious for oh lets say about 2, 3 hours.");
	delayed_out_2("\nYou find it dificult to know how or why you are where you are.");
	delayed_out_2("\nBut it would be wise to find this knowledge out.");
	delayed_out_2("\nVoice: 'Hey get up!'");
	while (true) {
		delayed_out_2("\nVoice: 'Do you want to get up? yes or no?' ");
		Ask_Action();
		if (True_Choice == "yes") {
			delayed_out_2("\nVoice: 'Then get up!'");
			break;
		}
		else if (True_Choice == "no") {
			Game_Run = false;
			delayed_out_2("\nVoice: 'Then it is here you rot!'");
			sleep_for(seconds(2));
			break;
		}
		else {
			delayed_out_2("\nVoice: 'I can't understand you.'"); continue;
		};
	};
	delayed_out_2("\nAs you get up, you feel a heavy sensation fall upon your shoulders...");

	delayed_out_2("\nand you smell a hint of sulfur?");

	delayed_out_2("\nVoice: 'I think you have a visitor...'");
	sleep_for(seconds(2));
	player.Health = 100;
	player.Damage = 2;
	player.Mob_Name = tutorial_mob.Name;
	player.Mob_Health = tutorial_mob.Health;
	player.Mob_Damage = tutorial_mob.Damage;
	delayed_out_2("\nVoice: 'In combat you can do many things.'");
	delayed_out_2("\nVoice: 'As for instance you can attack.' ");
	while (true) {
		Ask_Action();
		if (True_Choice == "attack") {
			player.Mob_Health = player.Mob_Health - player.Damage;
			delayed_out_2("\nIts health is "); cout << player.Mob_Health;
			break;
		}
		delayed_out_2("\nVoice: 'No Attack it can be typed with caps or not!'");
	};
	delayed_out_2("\nVoice: 'But be warned they can attack too'");
	player.Health = player.Health - player.Mob_Damage;
	delayed_out_2("\nYour health is "); cout << player.Health;
	sleep_for(seconds(1));
	delayed_out_2("\nVoice: 'You can do other things as well such as block, but you won't attack'");
	while (true) {
		Ask_Action();
		if (True_Choice == "block") {
			player.Health = player.Health - (player.Mob_Damage) / 2;
			break;
		}
		delayed_out_2("\nVoice: 'No Block it can be typed with caps or not!'");
	};
	delayed_out_2("\nYour health is "); cout << player.Health << endl;
	delayed_out_2("\nVoice: 'You take Damage still but only half as much, also you can stun them! Now finish 'em off!'");
	Attack_Sequence();
	delayed_out_2("\nVoice: 'What is your name by any chance?' ");
	Ask_Action();
	player.Name = Choice_Input;
	while (true) {
		if (First_Time_Asked) { delayed_out_2("\nVoice: 'How old are you?' "); }
		else { delayed_out_2("\nVoice: 'Tell me your age' "); };
		cin >> player.Age;
		if (player.Age <= 28) { delayed_out_2("\nAren't we all."); First_Time_Asked = false; break; }
		else if (player.Age > 28 || player.Age <= 40) { delayed_out_2("\nAlmost to the halfway mark aren't we?"); First_Time_Asked = false; break; }
		else if (player.Age > 40) { delayed_out_2("\nThen Kick some ass gramps!"); First_Time_Asked = false; break; }
		else { First_Time_Asked = false; }
	};
	delayed_out_2("\nVoice: 'What is your gender? (it will accept everything)' ");
	player.Gender = Choice_Input;
	delayed_out_2("\nVoice: 'When you have finish a battle You can save or wander' ");
	delayed_out_2("\nVoice: 'Saving saves your progres and dying will delete it' ");
	delayed_out_2("\nVoice: 'Wandering allows your character to roam the next halls and a possible next fight' ");
	delayed_out_2("\nVoice: 'We will be saving your game now' ");
	delayed_out_2("\nVoice: 'Saving...................' ");
	Save_Game();
	delayed_out_2("\nVoice: 'You are free to do as you please' ");
};