#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
struct Player {
	//This is all player stats and what they have and such
	string Name;
	unsigned int Age;
	string Gender;
	double Health;
	double Damage;
	bool Player_Stun = false;

	/* To be added
	vector<string> Inventory;
	vector<string> Equipped;
	vector<string> Resistances;
	*/

	//This is what the player is doing ex. Fighting a mob and its stats
	bool Mob_Stun = false;
	bool In_Fight;
	string Mob_Name;
	double Mob_Health;
	double Mob_Damage;
	bool Mob_Braced;
} player;



// Structs to hold the Monsters Data


struct Rat {
	string Name = "Rat";
	int Health = 15;
	int Damage = 5;
} rat;

struct Zombie {
	string Name = "Zombie";
	int Health = 50;
	int Damage = 10;
} zombie;

struct Orc {
	string Name = "Orc";
	int Health = 75;
	int Damage = 15;
} orc;

struct Goblin {
	string Name = "Goblin";
	int Health = 25;
	int Damage = 7;
} goblin;


struct Tutorial_mob {
	string Name = "Rat";
	int Health = 10;
	int Damage = 2;
} tutorial_mob;