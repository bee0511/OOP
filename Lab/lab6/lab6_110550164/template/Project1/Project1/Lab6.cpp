#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define fileName "input1.txt"
using namespace std;



int main() {
	ifstream input(fileName);
	int numOfRoles;
	string temp;
	// TODO : Read the file
	// 1. Read the input file to get the imformation

	if (!input.is_open()) {
		cout << "Could not open the file - " << fileName << " -" << endl;
		input.close();
		system("pause");
	}
	cout << fileName << " is opened successfully." << endl;
	getline(input, temp, '\n');
	numOfRoles = stoi(temp);

	// TODO : Create the Role according to the input file
	// 1. Create the role
	// 2. Print this role's Infomation
	// 3. Show Role ( refer to spec )
	// Example :
	// -------------------------------------------------------
	// Role* warrior = new Warrior( warrior's Name, warrior's Level, warrior's Money, warrior's HP);
	// warrior->printAllInfo();
	// warrior->ShowRole();
	// cout << endl;
	// 
	// Role* archer = new Archer(archer's Name, archer's Level, archer's Money, archer's HP);
	// archer->printAllInfo();
	// archer->ShowRole();
	// cout << endl;
	// 
	// Role* magician = new Magician(magician's Name, magician's Level, magician's Money, magician's HP);
	// magician->printAllInfo();
	// magician->ShowRole();
	// cout << endl;
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles

	vector<Role*> player;
	for (int i = 0; i < numOfRoles; i++) {
		string name, role, slevel, smoney, shp;
		getline(input, name, ',');
		getline(input, role, ',');
		getline(input, slevel, ',');
		getline(input, smoney, ',');
		getline(input, shp, '\n');
		int level = stoi(slevel);
		int money = stoi(smoney);
		int hp = stoi(shp);
		Role* playerclass = 0;
		if (role == " Warrior") {
			playerclass = new Warrior(name, level, money, hp);
		}
		else if (role == " Archer") {
			playerclass = new Archer(name, level, money, hp);
		}
		else if (role == " Magician") {
			playerclass = new Magician(name, level, money, hp);
		}
		playerclass->printAllInfo();
		playerclass->ShowRole();
		player.push_back(playerclass);
		cout << endl;
	}
	//
	// TODO : Check wheather all characters can get staff or not
	// Example :
	// -------------------------------------------------------
	// staff->equipable(warrior);
	// staff->equipable(archer);
	// staff->equipable(magician);
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	Staff* staff = new Staff("flame");
	cout << "Checking whether the role can equip a staff.." << endl;
	for (int i = 0; i < numOfRoles; i++) {
		staff->equipable(player[i]);
	}

	input.close();
	system("PAUSE");
	return 0;
}