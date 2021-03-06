#include "main.h"
#include "GlobalClass.h"

int roll(int min, int max);
void getUserInfo(string &name, int &hp, int &level, int &xp, int &money, double &attack, double &levelAttack, double &defense, double &levelDefense, double &luck, string &userClass, vector<int> &bag);
void saveUserInfo(string name, int hp, int level, int xp, int money, double attack, double levelAttack, double defense, double levelDefense, double luck, string userClass, vector <int> bag);
void getEquipment(vector<int> bag);
void getWeaponInfo(int weapon, string &name, int &att, int &def, int &typ, int &skl, int &rarity, int &price);
void resetBaseStats(string userClass, double &attack, double &defense);
void getEnemy(string &name, int &atk, int &def, int &max, int &min, int floor);
void levelUp(string &name, int &hp, int &level, int &xp, double &attack, double &defense, double &luck, double &levelAttack, double &levelDefense);

int main()
{
#pragma region variables
	random_device rd;
	int userInp;
	int input;
	int menuInp;
	bool exit = false;
	//player stats
	int maxID;
#pragma region getmaxID
	bool foundmaxID = false;
	while (!foundmaxID)
	{
		string tname;
		int tatt;
		int tdef;
		int ttyp;
		int tskl;
		int trar;
		int tprice;
		fstream itemIndexID;
		itemIndexID.open("Item ID index.txt", ios::in);
		while (!itemIndexID.eof())
		{
			itemIndexID >> maxID;
			itemIndexID >> tname;
			itemIndexID >> tatt;
			itemIndexID >> tdef;
			itemIndexID >> ttyp;
			itemIndexID >> tskl;
			itemIndexID >> trar;
			itemIndexID >> tprice;
		}
		foundmaxID = true;
	}
#pragma endregion
	string name;
	int hp;
	int level;
	int xp;
	int money;
	double baseAttack;
	double baseDefense;
	double attack;
	double defense;
	double levelAttack;
	double levelDefense;
	double luck;
	string userClass;
	vector<int> bag(35);
	vector<int> equip(30);
#pragma endregion
	getUserInfo(name, hp, level, xp, money, attack, levelAttack, defense, levelDefense, luck, userClass, bag);
	resetBaseStats(userClass, baseAttack, baseDefense);
	system("cls");
	while (true)
	{
		system("cls");
#pragma region save
		fstream file;
		string fileName = name + ".txt";
		file.open(fileName, ios::out);
		for (int i = 0; i <= 34; i++)
		{
			file << bag[i] << endl;
		}
		file << hp << endl;
		file << level << endl;
		file << xp << endl;
		file << money << endl;
		file << attack << endl;
		file << levelAttack << endl;
		file << defense << endl;
		file << levelDefense << endl;
		file << luck << endl;
		file << userClass << endl;
		file.close();
#pragma endregion 
		cout << "Menu: " << endl;
		cout << "1. Play" << endl;
		cout << "2. Player Profile" << endl;
		cout << "3. Exit" << endl;
		cout << "Input: ";
		int select;
		cin >> menuInp;
#pragma region gameplay
		if (menuInp == 1)
		{
			system("cls");
			resetBaseStats(userClass, baseAttack, baseDefense);
			attack = baseAttack + levelAttack;
			defense = baseDefense + levelDefense;
			for (int i = 0; i <= 4; i++)
			{
				int att;
				int def;
				int typ;
				int skl;
				int rarity;
				int price;
				string name;
				getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
				attack += att;
				defense += def;
			}
			bool dead = false;
			int round = 1;
			while (!dead)
			{
				cout << "Round: " << round << endl;
				int pChoices[3];
				string choices[3];
				for (int i = 0; i <= 2; i++)
				{
					int number = roll(0, 6);
					if (number <= 3)
					{
						choices[i] = "Battle";
						pChoices[i] = 0;
					}
					if (number >= 4)
					{
						choices[i] = "Shop";
						pChoices[i] = 1;
					}
					if (number == 6)
					{
						choices[i] = "Treasure";
						pChoices[i] = 2;
					}
				}
				cout << "Path choices: " << endl;
				cout << "1. " << choices[0] << endl;
				cout << "2. " << choices[1] << endl;
				cout << "3. " << choices[2] << endl;
				cout << "4. Exit" << endl;
				cout << "Input: ";
				int playInp;
				cin >> playInp;
				int playerChoice;
				if (playInp == 1)
				{
					playerChoice = pChoices[0];
				}//choice 1
				if (playInp == 2)
				{
					playerChoice = pChoices[1];
				}//choice 2
				if (playInp == 3)
				{
					playerChoice = pChoices[2];
				}//choice 3
				if (playInp == 4)
				{
					playerChoice = -1;
					dead = true;
				}//end choice
				//GAMEPLAY
				system("cls");
				cout << "Round: " << round << endl;
				if (playerChoice == 1)
				{
					system("cls");
					cout << "You have found a shop!" << endl;
					cout << "Current money: " << money << endl;
					int items[5];
					int prices[5];
					string itemNames[5];
					fstream index;
					index.open("Item ID index.txt", ios::in);
					string wname;
					int watt;
					int wdef;
					int wtyp;
					int wskl;
					int wrar;
					int wprice;
					for (int i = 0; i <= 4; i++)
					{
						index.close();
						index.open("Item ID index.txt", ios::in);
						bool foundWeapon = false;
						while (!foundWeapon)
						{
							int weaponRoll = roll(0, maxID);
							getWeaponInfo(weaponRoll, wname, watt, wdef, wtyp, wskl, wrar, wprice);
							int chanceRoll = roll(0, 99);
							chanceRoll++;
							if (chanceRoll < weaponRoll)
							{
								foundWeapon = true;
								cout << i + 1 << ". " << wname << ": " << wprice << endl;
								items[i] = weaponRoll;
								prices[i] = wprice;
								itemNames[i] = wname;
							}
						}
					}
					cout << "6. Exit" << endl;
					cout << "Input: ";
					int shopInput;
					cin >> shopInput;
					if (money >= prices[shopInput - 1] && shopInput != 6)
					{
						cout << "You have bought a(n) " << itemNames[shopInput - 1] << "!" << endl;
						money -= prices[shopInput - 1];
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[i] = items[shopInput - 1];
								break;
							}
						}
						cout << "Current money: " << money << endl;
						system("pause");
					}
					else if (shopInput == 6)
					{
						cout << "Goodbye. " << endl;
						system("pause");
					}
					else {
						cout << "You do not have enough money to buy this." << endl;
						system("pause");
					}
				}
				if (playerChoice == 2)
				{
					system("cls");
					cout << "You have found treasure!" << endl;
					int treasure[3];
					string treasureName[3];
					fstream index;
					index.open("Item ID index.txt", ios::in);
					string wname;
					int watt;
					int wdef;
					int wtyp;
					int wskl;
					int wrar;
					int wprice;

					for (int i = 0; i <= 2; i++)
					{
						index.close();
						index.open("Item ID index.txt", ios::in);
						bool foundWeapon = false;
						while (!foundWeapon)
						{
							int weaponRoll = roll(0, maxID);
							getWeaponInfo(weaponRoll, wname, watt, wdef, wtyp, wskl, wrar, wprice);
							int chanceRoll = roll(0, 99);
							chanceRoll++;
							if (chanceRoll < weaponRoll)
							{
								foundWeapon = true;
								cout << i + 1 << ". " << wname << endl;
								treasure[i] = weaponRoll;
								treasureName[i] = wname;
							}
						}
					}
					cout << "Input: ";
					int treasureInput;
					cin >> treasureInput;
					if (treasureInput == 1)
					{
						bool foundSpace = false;
						while (!foundSpace)
						{
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = treasure[0];
									foundSpace = true;
									break;
								}
							}
						}
					}
					if (treasureInput == 2)
					{
						bool foundSpace = false;
						while (!foundSpace)
						{
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = treasure[1];
									foundSpace = true;
									break;
								}
							}
						}
					}
					if (treasureInput == 3)
					{
						bool foundSpace = false;
						while (!foundSpace)
						{
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = treasure[2];
									foundSpace = true;
									break;
								}
							}
						}
					}
				}
				if (playerChoice == 0)
				{
					int PlayerHP = hp;
					int EnemyHP = 20;
					bool winner = false;
					string mname;
					int matk;
					int mdef;
					int max;
					int min;
					getEnemy(mname, matk, mdef, max, min, round);
					matk += round;
					mdef += round;
					system("cls");
					cout << "A " << mname << " has appeared!" << endl;
					system("pause");
					while (!winner)
					{
						system("cls");
						cout << name << " HP: " << PlayerHP << endl;
						cout << mname << " HP: " << EnemyHP << endl;
						//Player Turn
						double critChance = 500 * luck;
						bool crit = false;
						double number = roll(0, 10000);
						if (number <= critChance)
						{
							crit = true;
							attack *= 5;
							cout << "Critical hit!" << endl;
						}
						int damage = roll(0, attack) - mdef;
						if (damage >= 1)
						{
							cout << name << " hit " << mname << " for " << damage << " damage!" << endl;
						}
						else {
							damage = 1;
							cout << name << " hit " << mname << " for " << damage << " damage!" << endl;
						}
						EnemyHP -= damage;
						if (crit)
						{
							attack /= 5;
						}
						//Enemy Turn
						critChance = 500;
						crit = false;
						number = roll(0, 10000);
						if (number <= critChance)
						{
							crit = true;
							matk *= 5;
							cout << "Critical hit!" << endl;
						}
						damage = roll(0, matk) - defense;
						if (damage >= 1)
						{
							cout << mname << " hit " << name << " for " << damage << " damage!" << endl;
						}
						else {
							damage = 1;
							cout << mname << " hit " << name << " for " << damage << " damage!" << endl;
						}
						PlayerHP -= damage;
						if (crit)
						{
							matk /= 5;
						}
						system("pause");
						if (PlayerHP <= 0)
						{
							cout << "The winner is " << mname << "!" << endl;
							int xpGained = roll(0, round * 5), moneyGained = roll(0, round * 5);
							money += moneyGained;
							xp += xpGained;
							cout << "You have gained " << xpGained << " (" << xp << "/" << level * 10 << ") xp and " << moneyGained << " money." << endl;
							cout << "Your money: " << money << endl;
							dead = true;
							winner = true;
							levelUp(name, hp, level, xp, attack, defense, luck, levelAttack, levelDefense);
#pragma region save
							fstream file;
							string fileName = name + ".txt";
							file.open(fileName, ios::out);
							for (int i = 0; i <= 34; i++)
							{
								file << bag[i] << endl;
							}
							file << hp << endl;
							file << level << endl;
							file << xp << endl;
							file << money << endl;
							file << attack << endl;
							file << levelAttack << endl;
							file << defense << endl;
							file << levelDefense << endl;
							file << luck << endl;
							file << userClass << endl;
							file.close();
#pragma endregion 
							system("pause");
						}
						else if (EnemyHP <= 0)
						{
							cout << "The winner is " << name << "!" << endl;
							int xpGained = roll(0, round * 5), moneyGained = roll(0, round * 5);
							money += moneyGained;
							xp += xpGained;
							cout << "You have gained " << xpGained << " (" << xp << "/" << level * 10 << ") xp and " << moneyGained << " money." << endl;
							cout << "Your money: " << money << endl;
							winner = true;
							levelUp(name, hp, level, xp, attack, defense, luck, levelAttack, levelDefense);
#pragma region save
							fstream file;
							string fileName = name + ".txt";
							file.open(fileName, ios::out);
							for (int i = 0; i <= 34; i++)
							{
								file << bag[i] << endl;
							}
							file << hp << endl;
							file << level << endl;
							file << xp << endl;
							file << money << endl;
							file << attack << endl;
							file << levelAttack << endl;
							file << defense << endl;
							file << levelDefense << endl;
							file << luck << endl;
							file << userClass << endl;
							file.close();
#pragma endregion 							
							system("pause");
						}
					}
				}//Battle choice
				system("cls");
				round++;
			}//end game loop
		}//if select play
#pragma endregion
#pragma region PlayerProfile
		if (menuInp == 2)
		{
			system("cls");
			fstream index;
			index.open("Item ID index.txt", ios::in);
			cout << "1. Equipment" << endl;
			cout << "2. Bag" << endl;
			cout << "3. Stats" << endl;
			cout << "Input: ";
			cin >> select;
			switch (select)
			{
#pragma region 1.equipment
			default:
				cout << "Could not find menu item." << endl;
			case 1:
				system("cls");
				for (int i = 0; i <= 4; i++)
				{
					index.close();
					index.open("Item ID index.txt", ios::in);
					bool found = false;
					if (i == 0) {
						cout << "1. Weapon: ";
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 1) {
						cout << "2. Helmet: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 2) {
						cout << "3. Chest: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 3) {
						cout << "4. Leg: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 4) {
						cout << "5. Boot: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
				}
				cout << "6. Back" << endl;
				cout << "Input: ";
				int equipInp;
				cin >> equipInp;
				//equipment choice
				if (equipInp == 1)
				{
					system("cls");
					cout << "What would you like to do with the weapon?" << endl;
					cout << "1. Equip" << endl;
					cout << "2. Unequip" << endl;
					int inp;
					cout << "Input: ";
					cin >> inp;
					//check
					cout << "Equippable items: " << endl;
					if (inp == 1)
					{
						system("cls");
						int num = 0;
						vector<int> equip(30);
						for (int i = 5; i <= 34; i++)
						{
							int att;
							int def;
							int typ;
							int skl;
							int rarity;
							int price;
							string name;
							getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
							if (typ == 1)
							{
								equip[num] = bag[i];
								num++;
								cout << num << ". " << name << endl;

							}
						}
						if (num == 0)
						{
							cout << "Could not find any items." << endl;
							system("pause");
						}
						else {
							cout << "Input: ";
							int whatDoEquip;
							cin >> whatDoEquip;
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = bag[0];
									bag[0] = equip[whatDoEquip - 1];
									break;
								}
							}
						}
					}
					if (inp == 2)
					{
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[0] = bag[i];
								bag[i] = 0;
								break;
							}
							else if (i == 34)
							{
								system("cls");
								cout << "Inventory full!" << endl;
								system("pause");
							}
						}
					}
				}//end weapon equipment
				if (equipInp == 2)
				{
					system("cls");
					cout << "What would you like to do with the helmet?" << endl; // change
					cout << "1. Equip" << endl;
					cout << "2. Unequip" << endl;
					int inp;
					cout << "Input: ";
					cin >> inp;
					//check
					cout << "Equippable items: " << endl;
					if (inp == 1)
					{
						system("cls");
						int num = 0;
						vector<int> equip(30);
						for (int i = 5; i <= 34; i++)
						{
							int att;
							int def;
							int typ;
							int skl;
							int rarity;
							int price;
							string name;
							getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
							if (typ == 2)// change
							{
								equip[num] = bag[i];
								num++;
								cout << num << ". " << name << endl;

							}
						}
						if (num == 0)
						{
							cout << "Could not find any items." << endl;
							system("pause");
						}
						else {
							cout << "Input: ";
							int whatDoEquip;
							cin >> whatDoEquip;
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = bag[1];
									bag[1] = equip[whatDoEquip - 1];
									break;
								}
							}
						}
					}
					if (inp == 2)
					{
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[i] = bag[1];
								bag[1] = 0; // change
								break;
							}
							else if (i == 34)
							{
								system("cls");
								cout << "Inventory full!" << endl;
								system("pause");
							}
						}
					}
				}//end weapon equipment
				if (equipInp == 3)
				{
					system("cls");
					cout << "What would you like to do with the chest?" << endl; // change
					cout << "1. Equip" << endl;
					cout << "2. Unequip" << endl;
					int inp;
					cout << "Input: ";
					cin >> inp;
					//check
					cout << "Equippable items: " << endl;
					if (inp == 1)
					{
						system("cls");
						int num = 0;
						vector<int> equip(30);
						for (int i = 5; i <= 34; i++)
						{
							int att;
							int def;
							int typ;
							int skl;
							int rarity;
							int price;
							string name;
							getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
							if (typ == 3)// change
							{
								equip[num] = bag[i];
								num++;
								cout << num << ". " << name << endl;

							}
						}
						if (num == 0)
						{
							cout << "Could not find any items." << endl;
							system("pause");
						}
						else {
							cout << "Input: ";
							int whatDoEquip;
							cin >> whatDoEquip;
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = bag[2];
									bag[2] = equip[whatDoEquip - 1];
									break;
								}
							}
						}
					}
					if (inp == 2)
					{
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[i] = bag[2];// change
								bag[2] = 0; // change
								break;
							}
							else if (i == 34)
							{
								system("cls");
								cout << "Inventory full!" << endl;
								system("pause");
							}
						}
					}
				}//end weapon equipment
				if (equipInp == 4)
				{
					system("cls");
					cout << "What would you like to do with the leggings?" << endl; // change
					cout << "1. Equip" << endl;
					cout << "2. Unequip" << endl;
					int inp;
					cout << "Input: ";
					cin >> inp;
					//check
					cout << "Equippable items: " << endl;
					if (inp == 1)
					{
						system("cls");
						int num = 0;
						vector<int> equip(30);
						for (int i = 5; i <= 34; i++)
						{
							int att;
							int def;
							int typ;
							int skl;
							int rarity;
							int price;
							string name;
							getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
							if (typ == 4)// change
							{
								equip[num] = bag[i];
								num++;
								cout << num << ". " << name << endl;

							}
						}
						if (num == 0)
						{
							cout << "Could not find any items." << endl;
							system("pause");
						}
						else {
							cout << "Input: ";
							int whatDoEquip;
							cin >> whatDoEquip;
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = bag[3];
									bag[3] = equip[whatDoEquip - 1];
									break;
								}
							}
						}
					}
					if (inp == 2)
					{
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[i] = bag[3];// change
								bag[3] = 0; // change
								break;
							}
							else if (i == 34)
							{
								system("cls");
								cout << "Inventory full!" << endl;
								system("pause");
							}
						}
					}
				}//end weapon equipment
				if (equipInp == 5)
				{
					system("cls");
					cout << "What would you like to do with the boots?" << endl; // change
					cout << "1. Equip" << endl;
					cout << "2. Unequip" << endl;
					int inp;
					cout << "Input: ";
					cin >> inp;
					//check
					cout << "Equippable items: " << endl;
					if (inp == 1)
					{
						system("cls");
						int num = 0;
						vector<int> equip(30);
						for (int i = 5; i <= 34; i++)
						{
							int att;
							int def;
							int typ;
							int skl;
							int rarity;
							int price;
							string name;
							getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
							if (typ == 5)// change
							{
								equip[num] = bag[i];
								num++;
								cout << num << ". " << name << endl;

							}
						}
						if (num == 0)
						{
							cout << "Could not find any items." << endl;
							system("pause");
						}
						else {
							cout << "Input: ";
							int whatDoEquip;
							cin >> whatDoEquip;
							for (int i = 5; i <= 34; i++)
							{
								if (bag[i] == 0)
								{
									bag[i] = bag[4];
									bag[4] = equip[whatDoEquip - 1];
									break;
								}
							}
						}
					}
					if (inp == 2)
					{
						for (int i = 5; i <= 34; i++)
						{
							if (bag[i] == 0)
							{
								bag[i] = bag[4];// change
								bag[4] = 0; // change
								break;
							}
							else if (i == 34)
							{
								system("cls");
								cout << "Inventory full!" << endl;
								system("pause");
							}
						}
					}
				}//end weapon equipment
				break;
#pragma endregion			
			case 2:
				system("cls");
				int max;
				max = -1;
				for (int i = 0; i <= 34; i++)
				{
					index.close();
					index.open("Item ID index.txt", ios::in);
					bool found = false;
#pragma region equipment
					if (i == 0) {
						cout << "1. Weapon: ";
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 1) {
						cout << "2. Helmet: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 2) {
						cout << "3. Chest: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 3) {
						cout << "4. Leg: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
					if (i == 4) {
						cout << "5. Boot: ";
						found = true;
						while (!index.eof() || !found)
						{
							int num;
							index >> num;
							string indexName;
							getline(index, indexName);
							if (num == bag[i])
							{
								found = true;
								cout << indexName << endl;
							}
						}
					}
#pragma endregion
					if (i > 4)
					{
						int att;
						int def;
						int typ;
						int skl;
						int rarity;
						int price;
						string name;
						getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
						if (bag[i] != 0)
						{
							cout << i + 1 << ". " << name << ": " << endl;
							max = i + 1;
						}
					}
				}
				if (max == -1)
					max = 5;
				cout << max + 1 << ". Exit" << endl;
				cout << "Input: ";
				int bagInput;
				cin >> bagInput;
				if (bagInput != max + 1)
				{
					int att;
					int def;
					int typ;
					int skl;
					int rarity;
					int price;
					string name;
					getWeaponInfo(bag[bagInput - 1], name, att, def, typ, skl, rarity, price);
					system("cls");
					cout << "What would you like to do with " << name << "?" << endl;
					cout << "1. Sell (" << price << ")" << endl;
					cout << "2. Get info" << endl;
					cout << "3. Cancel" << endl;
					cout << "Input: ";
					cin >> bagInput;
					if (bagInput == 1)
					{
						system("cls");
						cout << "Sell " << name << "?" << endl;
						cout << "1. Yes" << endl << "2. No" << endl;
						int getInput;
						cin >> getInput;
						if (getInput == 1)
						{
							cout << "You have sold " << name << " for " << price << "!" << endl;
							money += price;
							bag[bagInput - 1] = 0;
							cout << "Your money: " << money << endl;
							system("pause");
						}
					}
					if (bagInput == 2)
					{
						system("cls");
						cout << name << ":" << endl;
						cout << "Attack: " << att << endl;
						cout << "Defense: " << def << endl;
						cout << "Type: " << typ << endl;
						cout << "Rarity: " << rarity << endl;
						cout << "Price: " << price << endl;
						system("pause");
					}
					select = -1;
				}
			case 3:
				resetBaseStats(userClass, baseAttack, baseDefense);
				attack = baseAttack + levelAttack;
				defense = baseDefense + levelDefense;
				for (int i = 0; i <= 4; i++)
				{
					int att;
					int def;
					int typ;
					int skl;
					int rarity;
					int price;
					string name;
					getWeaponInfo(bag[i], name, att, def, typ, skl, rarity, price);
					attack += att;
					defense += def;
				}
				system("cls");
				cout << "Name: " << name << endl;
				cout << "Health: " << hp << endl;
				cout << "Class: " << userClass << endl;
				cout << "Attack: " << attack << endl;
				cout << "Defense: " << defense << endl;
				cout << "Level: " << level << endl;
				cout << "Exp: " << xp << "/" << level * 10 << endl;
				cout << "Money: " << money << endl;
				cout << "Luck: " << luck << endl;
				system("pause");
			}
		}
#pragma endregion
#pragma region ExitFunc
		if (menuInp == 3)
		{
			fstream file;
			string fileName = name + ".txt";
			file.open(fileName, ios::out);
			for (int i = 0; i <= 34; i++)
			{
				file << bag[i] << endl;
			}
			file << hp << endl;
			file << level << endl;
			file << xp << endl;
			file << money << endl;
			file << attack << endl;
			file << levelAttack << endl;
			file << defense << endl;
			file << levelDefense << endl;
			file << luck << endl;
			file << userClass << endl;
			file.close();
			return 0;

#pragma endregion 
		}
	}
	return 0;
}
#pragma region functions
int roll(int min, int max)
{
	random_device rd;
	int x;
	int y;
	if (min > 0)
	{
		x = min + 1;
		y = min;


	}
	else if (min == 0) {
		y = 0;
		x = max + 1;
	}
	return rd() % x + y;
}

void getEnemy(string &name, int &atk, int &def, int &max, int &min, int floor)
{
	random_device rd;
	bool found = false;
	int maxID;
	fstream index;
	string tname;
	int tatk;
	int tdef;
	int tmin;
	int tmax;
	index.open("Enemy ID index.txt", ios::in);
	while (!index.eof())
	{
		index >> maxID;
		index >> tname;
		index >> tatk;
		index >> tdef;
		index >> tmin;
		index >> tmax;
	}
	maxID++;
	index.close();
	index.open("Enemy ID index.txt", ios::in);
	while (!found)
	{
		int roll = rd() % maxID;
		int pos = index.tellg();
		int indexNum;
		index >> indexNum;
		index >> name;
		index >> atk;
		index >> def;
		index >> min;
		index >> max;
		if (roll == indexNum && floor <= max && floor >= min)
		{
			found = true;
		}
		else if (maxID - 1 == indexNum)
		{
			roll = rd() % maxID;
			index.close();
			index.open("Enemy ID index.txt", ios::in);
		}
	}
	index.close();
}
void resetBaseStats(string userClass, double &attack, double &defense)
{
	if (userClass == "Mage")
	{
		attack = 3;
		defense = 1;
	}
	if (userClass == "Archer")
	{
		attack = 2.5;
		defense = 2;
	}
	if (userClass == "Warrior")
	{
		attack = 4;
		defense = 2;
	}
}

void getWeaponInfo(int weapon, string &name, int &att, int &def, int &typ, int &skl, int &rarity, int &price)
{
	/*
	int att;
	int def;
	int typ;
	int skl;
	string name;
	getWeaponInfo(bag[i], name, att, def, typ, skl);
	*/
	//Find Weapon
	bool found = false;
	fstream index;
	index.open("Item ID index.txt", ios::in);
	while (!found)
	{
		int indexNum;
		index >> indexNum;
		index >> name;
		index >> att;
		index >> def;
		index >> typ;
		index >> skl;
		index >> rarity;
		index >> price;
		//cout << indexNum << name << endl;
		if (indexNum == weapon)
		{
			found = true;
		} 
	}
}

void getEquipment(vector<int> bag)
{
	for (int i = 0; i <= 34; i++)
	{
		//
	}
}

void saveUserInfo(string name, int hp, int level, int xp, int money, double attack, double levelAttack, double defense, double levelDefense, double luck, string userClass, vector <int> bag)
{
	fstream file;
	string fileName = name + ".txt";
	file.open(fileName, ios::out);
	for (int i = 0; i <= 34; i++)
	{
		file << bag[i] << endl;
	}
	file << hp << endl;
	file << level << endl;
	file << xp << endl;
	file << money << endl;
	file << attack << endl;
	file << levelAttack << endl;
	file << defense << endl;
	file << levelDefense << endl;
	file << luck << endl;
	file << userClass << endl;
	file.close();
}
void levelUp(string &name, int &hp, int &level, int &xp, double &attack, double &defense, double &luck, double &levelAttack, double &levelDefense)
{
	bool done = false;
	while (!done)
	{
		if (xp >= level * 10)
		{
			int addAttack = roll(1, level + 1);
			int addDefense = roll(1, level + 1);
			int addHealth = roll(1, level + 1);
			levelAttack += addAttack;
			levelDefense += addDefense;
			hp += addHealth;
			double addLuck = .01;
			xp -= level * 10;
			luck += addLuck;
			level++;
			cout << name << " has leveled up to level " << level << "!" << endl;
			cout << "Current xp: " << xp << "/" << level * 10 << endl;
			cout << "Attack: " << attack << " + " << addAttack << endl;
			cout << "Defense: " << defense << " + " << addDefense << endl;
			cout << "Health: " << hp - addHealth << " + " << addHealth << endl;
			cout << "Luck: " << luck - addLuck << " + " << ".01" << endl;
		}
		else {
			done = true;
		}
	}
}
void getUserInfo(string &name, int &hp, int &level, int &xp, int &money, double &attack, double &levelAttack, double &defense, double &levelDefense, double &luck, string &userClass, vector<int> &bag)
{
	bool finish = false;
	cout << "Input Name: ";
	cin >> name;
	finish = false;
	fstream file;

	string fileName = name + ".txt";
	file.open(fileName, ios::in);

	if (file.is_open())
	{
		cout << "Player found" << endl;
		//cout << "Bag: " << endl;
		for (int i = 0; i <= 34; i++)
		{
			int num[35];
			file >> num[i];
			bag[i] = num[i];
			//cout << i << ". " << bag[i] << endl;
		}
		//cout << "Stats: " << endl;
		file >> hp;
		file >> level;
		file >> xp;
		file >> money;
		file >> attack;
		file >> levelAttack;
		file >> defense;
		file >> levelDefense;
		file >> luck;
		file >> userClass;
	}
	else {
		cout << "New player found!" << endl;
		cout << "Choose Class:" << endl;
		cout << "1. Warrior\n2. Mage\n3. Archer" << endl;
		int choice;
		cin >> choice;
		level = 1;
		xp = 0;
		money = 0;
		if (choice == 1)
		{
			userClass = "Warrior";
			bag[0] = 1;
			hp = 30;
			attack = 4;
			defense = 2;
			levelAttack = 0;
			levelDefense = 0;
			luck = 1;
		}
		else if (choice == 2)
		{
			userClass = "Mage";
			bag[0] = 3;
			hp = 15;
			attack = 3;
			defense = 1;
			levelAttack = 0;
			levelDefense = 0;
			luck = 1.1;
		}
		else {
			userClass = "Archer";
			bag[0] = 2;
			hp = 20;
			attack = 2.5;
			defense = 2;
			levelAttack = 0;
			levelDefense = 0;
			luck = 1.3;
		}

	}
	file.close();
}

#pragma endregion 