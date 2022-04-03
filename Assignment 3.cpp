//short story about the game
//intro sequence
//action scenario
//    turn-based combat?
//quest or purpose
//    stereotyipical non typical rescue the prince who fell down the well....Idiot.....
// three customization options
//    personally thinking class, race,and age.

// inventory system
//    items that can be displayed
//        show something like head chest arms legs feet, and backpack
//    equipped
//        eqipement slots kinda like inventory slots i guess
//    unequipped
//        hand in hand with equipped vectoring back to backpack as opposed to the merchant
//    discarded
//        erase. function
//    used
//        used means reduced quantity

//import merchant assets
//    all the buying and selling stuff
//    display inventory of both the merchant and the player seperately
//    LITTERALLY ADD THE MERCHANT INVENTORY PROGRAM

//three options that impact the story
//    skip combat through riddle for learned
//    get new items from merchant for free
//    loose all gold to win one combat.

//combat system
//    display player health and damage
//    display enemy health and damge
//    win lose condition
//        made of functions

//    three classes of enemies using inheritance
//        thieves
//        brutes
//        learned

//    randomization (see dice roller)

//general knowhow
//    clear use of if else statements and or switch

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Item
{
public:
	string name;
	int value;
};

class Consumable : public Item
{
public:
	int uses;
	void use();
};

class Wearable : public Item
{
public:
	int initiative_bonus = 0;
	bool equipped = true;
};

class Weapon : public Item
{
public:
	int damage_bonus = 0;
	bool equipped = true;
};

class ItemSlot
{
public:
	ItemSlot(string name = "Empty", int value = 0, int quantity = 0);
	Item item;
	int qty;
};

ItemSlot::ItemSlot(string name, int value, int quantity)
{
	item.name = name;
	item.value = value;
	qty = quantity;
}

class Role
{
public:
	string name;
	int health;
	int maxHealth;
	int damage;
	int initiative_bonus;
};

class Player
{
public:
	string name;
	int age;
	int pGold = 100;
	Role role;
	Wearable equippedWearable;
	Wearable defaultWearable;
	Weapon equippedWeapon;
	Weapon defaultWeapon;
	vector<ItemSlot> inventory;
	bool win;
};

class Enemy
{
	int mDamage;
public:
	Enemy(string name = "Enemy", int initiative = 0, int damage = 0, int health = 0, int armor = 0);
	string name;
	int health;
	int initiative;
	int armor;
	void virtual attack(int& health, string enemyName) const;
};

Enemy::Enemy(string name, int initiative, int damage, int health, int armor) :

	mDamage(damage)
{}

void Enemy::attack(int& health, string enemyName) const
{
	cout << enemyName << " hits you for " << mDamage << "damage." << endl;
	(health) -= mDamage;
}

class Thief : public Enemy
{
public:
	int hp;
	Thief(string name, int health, int initiative, int damage, int armor);
};

Thief::Thief(string name, int initiative, int damage, int health, int armor)
{
	Enemy(name, initiative, damage, health, armor);
}

class Merchant
{
public:
	int mGold = 300;
	vector<ItemSlot> inventory;
};

int diceInitiative();
void pAttack(Enemy* enemy, Player* player);
int main();
void fight(Enemy enemy, Player player, Role role, Wearable wearable);
void use();
void discard();
void displayInventory(vector<ItemSlot>* inventory);
void invTransaction(vector<ItemSlot>* inventory, vector<ItemSlot>* inventory2, int choice);
void printName(string playerFirstName, string playerLastName);
void classSelect(Player* player);
void fillHealth(Player* player);
void backpack(vector<ItemSlot>* inventory, Player* player);
void askNumber(int choice, int low, int high);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	unsigned int business = 0;
	string pFN;
	string pLN;
	int age;
	char yesno = 'n';

//choices
	int choice;
	int action;
	string role;
	Item pain_meds;
	Item fancy_book;
	Item dagger;
	Item smokebomb;
	Item boots;
	Item water_bucket;

	pain_meds.name = "Pain Meds";
	pain_meds.value = 100;
	fancy_book.name = "Fancy book";
	fancy_book.value = 100;
	dagger.name = "Dagger";
	dagger.value = 100;
	smokebomb.name = "Smokebomb";
	smokebomb.value = 100;
	boots.name = "Boots";
	boots.value = 100;
	water_bucket.name = "Water Bucket";
	water_bucket.value = 100;

	ItemSlot mSlot1;
	ItemSlot mSlot2;
	ItemSlot mSlot3;
	ItemSlot mSlot4;
	ItemSlot mSlot5;
	ItemSlot pSlot1;
	ItemSlot pSlot2;
	ItemSlot pSlot3;

	mSlot1.item = pain_meds;
	mSlot1.qty = 2;
	mSlot2.item = fancy_book;
	mSlot2.qty = 1;
	mSlot3.item = dagger;
	mSlot3.qty = 1;
	mSlot4.item = smokebomb;
	mSlot4.qty = 2;
	mSlot5.item = boots;
	mSlot5.qty = 1;
	pSlot1.item = water_bucket;
	pSlot1.qty = 1;

	Player player;
	Merchant merchant;

	Weapon Fist;
	player.defaultWeapon = Fist;

	Wearable Crocks;
	player.defaultWearable = Crocks;

	merchant.inventory.push_back(mSlot1);
	merchant.inventory.push_back(mSlot2);
	merchant.inventory.push_back(mSlot3);
	merchant.inventory.push_back(mSlot4);
	merchant.inventory.push_back(mSlot5);
	player.inventory.push_back(pSlot1);

	Thief TheThief("Thief", 15, 4, 18, 0);
	// Learned
	// Brute

	std::cout << "What is your first name?" << std::endl;
	std::cin >> pFN;
	std::cout << "\nWhat is your last name?" << std::endl;
	std::cin >> pLN;
	classSelect(&player);
	std::cout << "\nLastly, how old are you?\n";
	std::cin >> age;
	player.age = age;

	do
	{

		std::cout << "\nFirst Name: " << pFN << "\nLast Name: " << pLN << "\nRole: " << player.role.name << "\nAge: " << age << std::endl;
		fillHealth(&player);

		std::cout << "\n--------------------------------------------\nYou are a princess sleeping in bed." << std::endl;
		std::cout << "You wake up uncomfortable and decide it might be best to do something about it.\n--------------------------------------------" << endl;

		std::cout << "You can either:\n"
			"1. Go to the Well\n"
			"2. Go to the Store\n"
			"3. Check under your mattress\n"
			"4. Open Backpack\n" << std::endl;
		std::cout << "Choice: ";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			//go to well
			std::cout << "you go to the well and remember that you have an empty bucket that you could fill with water.\n"
				"Also, while strolling you realize that the scenery around here is very pretty,\n it might serve you well to look around for a bit.\n"
				"However, you also do still feel tired and might consider just going back to bed.\n"
				"Lastly as always you can open your back pack to check what inside\n"
				"choices: 1. Get water.\n\t2.Look around and admire the scenery.\n\t3.You're tired so you go back to bed\n\t4.Open Backpack.";
			std::cin >> action;
			switch (action)
			{
			case 1:
				//get water
				break;
			case 2:
				//coin fight
				break;
			case 3:
				//tbtb
				break;
			case 4:
				backpack(&player.inventory, &player);
				break;
			default:
				std::cout << "uhh ohh we messed up ohh well damn";
				break;
			}
			break;
		case 2:
			{
			//go to store
			std::cout << "On the way to the store you check your pockts and realize you have " << player.pGold << "in your pocket."
				"\nWith this in mind do you want to enter the front door or sneak around back"
				"action 1: go inside\n 2: go around back";

			switch (action)
			case 1:
				//SHOPPING
				std::cout << "\nShopkeep: Well hi, ";
				printName(pFN, pLN);
				std::cout << "! How can I help you today? \n ";
				do
				{
					for (;;)
					{
						std::cout << "\n0 - I want to make a purchase!\n1 - I want to sell my items!\n2 - I would like to leave!\n\nChoice: " << flush;
						std::cin >> business;
						if (std::cin.fail())
						{
							cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
							std::cin.clear();
							std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						if (business < 0 || business > 3)
						{
							cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
							continue;
						}
						break;
					}
					switch (business)
					{
					case 0:
						std::cout << "\nShopkeep: A paying customer? Of course, happy to help!\nHave a look at my wares!\n\nWares:\n";
						displayInventory(&merchant.inventory);

						for (;;)
						{
							std::cout << "What would you like to buy? (0 to Exit) " << flush;
							std::cin >> choice;
							if (std::cin.fail())
							{
								cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
								std::cin.clear();
								std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
								continue;
							}
							if (choice < 0 || choice > merchant.inventory.size())
							{
								cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
								continue;
							}
							break;
						}

						choice -= 1;

						if (choice < merchant.inventory.size() || choice > 0)
						{
							if (merchant.inventory[choice].qty == 0)
							{
								std::cout << "\nShopkeep: Outta luck, wish I had more to sell you, but I don't.\n\nCan I help you with something else?\n";
								break;
							}

							std::cout << "\nWould you like to buy the " << merchant.inventory[choice].item.name << "?" << endl;
							std::cout << "Your current gold: " << player.pGold << " $" << endl;
							std::cout << "This " << merchant.inventory[choice].item.name << " costs " << merchant.inventory[choice].item.value << "$" << endl;

							if (player.pGold < merchant.inventory[choice].item.value)
							{
								std::cout << "Sorry it looks like you don't have enough gold for that.\n\nCan I help you with something else?\n";
								break;
							}

							std::cout << "Will you buy this " << merchant.inventory[choice].item.name << "? (y/n)\n" << endl;
							std::cin >> yesno;

							if (yesno == 'y')
							{
								std::cout << "\nYou bought the " << merchant.inventory[choice].item.name << "!" << endl;
								player.pGold -= merchant.inventory[choice].item.value;
								merchant.inventory[choice].qty -= 1;
								invTransaction(&player.inventory, &merchant.inventory, choice);
								std::cout << "your remaining gold balance is : " << player.pGold << "$" << endl;
							}
							else
							{
								std::cout << "you did not buy the " << merchant.inventory[choice].item.name << "." << endl;
							}
						}

						std::cout << "\nIs there anything else I can help you with?\n\n";
						break;

					case 1:
						std::cout << "\nShopkeep: I'm always happy to buy stuff you don't need, materials are getting scarce here.\n";
						std::cout << "\nYour items:\n";
						displayInventory(&player.inventory);

						for (;;)
						{
							std::cout << "Which item do you want to sell? (0 To Exit) " << flush;
							std::cin >> choice;

							if (std::cin.fail())
							{
								cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
								std::cin.clear();
								std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
								continue;
							}

							if (choice < 0 || choice > player.inventory.size())
							{
								cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
								continue;
							}

							break;
						}

						choice -= 1;

						if (choice < player.inventory.size() || choice > 0)
						{
							std::cout << "\nWould you like to sell the " << player.inventory[choice].item.name << "?" << std::endl;
							std::cout << "This " << player.inventory[choice].item.name << " will pay " << player.inventory[choice].item.value / 2 << "$" << std::endl;
							std::cout << "Merchant gold: " << merchant.mGold << "$" << std::endl;
							std::cout << "Will you sell this " << player.inventory[choice].item.name << "? (y/n)" << std::endl;
							std::cin >> yesno;

							if (yesno == 'y')
							{
								std::cout << "You sold the " << player.inventory[choice].item.name << "!" << std::endl;
								player.pGold += player.inventory[choice].item.value / 2;
								std::cout << "your remaining gold balance is : " << player.pGold << "$" << std::endl;
								invTransaction(&merchant.inventory, &player.inventory, choice);

								if (player.inventory[choice].qty > 1)
								{
									player.inventory[choice].qty -= 1;
								}
								else
								{
									vector<ItemSlot>::iterator eraser;
									eraser = player.inventory.begin() + choice;
									player.inventory.erase(eraser);
								}
							}
							else
							{
								std::cout << "You did not sell the " << player.inventory[choice].item.name << "." << std::endl;
							}
						}

						std::cout << "\nIs there anything else I can help you with?\n\n";
						break;

					case 2:
						std::cout << "\nShopkeep: Well, if you change your mind, you know where to find me.\n";
						break;

					default:
						break;

					} while (business < 0 && business > 1);

				} while (business != 2);//shop mechanic is hidden here <--
				break;

			case 2:
				//go around back
				std::cout << "as you make your way around to the back of the ";
				fight(Thief, player, Role, Wearable);// i tried here but its weird
				break;
			}
		case 3://check under mattress
			switch (action)
			case 1://take the pea
				break;
			case 2://eat the pea

				break;
			case 3://ignore the pea
				fight(Brute, player, Role, Wearable);
				break;

			
			break;
		case 4:
			//open backpack
			break;
		default: std::cout << "uhh ohh we messed up somewhere";

		} // end switch choice

		//        choice 1 (go to well)
		//            cout: 1. Draw some water
		//                  2. Nevermind, someone else can do it
		//                  3. Look around the well
		//                  4. Open Backpack
		//
		//            cin choice
		//
		//            switch statement
		//            {            
		//            choice 1
		//                get bucket of water
		//                    add bucket of water to inventory
		//                tired back to bed(tbtb)
		//                break out
		//
		//            choice 2 
		//                tbtb
		//                break out
		//
		//            choice 3 
		//                explore/ find a coin
		//                    add coin to player money
		//                battle function(thief)
		//                tbtb
		//                break out
		//            }
		//        choice 2 (go to store)
		//        {
		//            cin choice: 1. Rob Store
		//                        2. Enter shop
		//                        3. Open Backpack
		//
		//            switch choice 1 (sneak out back and try to rob){
		//                rob store
		//                battle function(thief)
		//                tbtb
		//                break out
		//       
		//            choice 2 (buy pain meds)
		//            {
		//                Enter shop mode
		//                when you leave shop
		//
		//          !!!!!!!!!!!!!!!!!!!!! find item goes here!!!!!!!!!!!!!!
		//  if player leaves shop and has fancy book (inventory find item from assignment 1)
		//            {
		//            encounter scholarly fellow
		//            riddle:
		//                    if correct
		//                    {
		//                        make friend
		//                        tbtb
		//                        break out
		//                    }
		//                    else
		//                    {
		//                        battle function(learned)
		//                        tbtb
		//                        break out
		//                    }
		//            }
		//            else
		//            {
		//                tbtb
		//                break out
		//            }
		//            
		//        choice 3 (check under bed)
		//{
			//            cin choice: 1. Take pea
			//                        2. C0NSUME pea
			//                        3. Ignore pea
			//                        4. Open Backpack
			//
			//            switch choice 1 (take the pea with you)
			//                encounter scholarly fellow
			//                riddle:
			//                        if true
			//                            make friend
			//                            tbtb
			//                            break out
			//
			//                        if false
			//                            battle function(learned)
			//                            tbtb
			//                            break out
			//
			//            choice 2 (consume pea)
			//                player win = true
			//                turns out it was magic, you feel the empowerment of 1000 princess
			//                that haven't been saved by this prince and decide he is not worthy of your hand.
			//                You decide to go blow up his house.
			//                congratulations message you win by not being stuck to no prince.
			//                
			//
			//            choice 3 (ignore the pea)
			//                cout: still uncomfortable you decide to sleep it off
			//                battle function(brute) NIGHTMARE NIGHTMARE NIGHTMARE NIGHTMARE
			//                tbtb
			//                break out
			//                end of do loop 1
			//            default:
			//            break;
		//}
					/*case 4:
						backpack(&player.inventory, &player);
						break;*/
						//}
	} while (player.role.health > 0 && (player.win = false));
	return 0;
}

void fight(Enemy enemy, Player player, Role role, Wearable wearable)
{
	int dice;
	int diceInitiative();
	int playerInitiative;
	bool playerTurnHad;
	int playerChoice;

	dice = diceInitiative();

	playerInitiative = (dice + role.initiative_bonus + wearable.initiative_bonus);

	do
	{
		if ((enemy.initiative > playerInitiative) || (playerTurnHad == true) && (enemy.health > 0))
		{
			enemy.attack(role.health, enemy.name);
			playerTurnHad = false;
		}

		if (playerTurnHad == false && player.role.health > 0)
		{
			//			do player turn
			cout << "Player Health: " << player.role.health << "\t Enemy Health: " << enemy.health << endl;
			cout << "1. Attack\n 2. Use Item\n 3. Run Away!\n";
			cin >> playerChoice;

			switch (playerChoice)
			{
			case 1:
				pAttack(&enemy, &player);
				break;
			case 2:
				backpack(&player.inventory, &player);
				continue;
			case 3:
				break;
			default:
				break;
			}
			cout << "Turn change!" << endl;
			playerTurnHad = true;
		}
	} while (player.role.health > 0 && enemy.health > 0 && playerChoice != 3);
	//    Congratz player! Or Tell them they dead.
	//    Add loot to inventory
}

int diceInitiative()
{
	int randomNumber;
	int dieRoll;

	randomNumber = rand();
	dieRoll = (randomNumber % 20) + 1;

	return dieRoll;
}

void pAttack(Enemy* enemy, Player* player)
{
	int damage;
	damage = (*player).role.damage + (*player).equippedWeapon.damage_bonus;

	cout << "You hit " << (*enemy).name << "for " << damage << endl;
	(*enemy).health -= damage;
}

void displayInventory(vector<ItemSlot>* inventory)
{
	for (int i = 0; i < inventory->size(); i++)
	{
		cout << (i + 1) << ": " << (*inventory)[i].item.name << endl;
		cout << "\tValue: " << (*inventory)[i].item.value << endl;

		if ((*inventory)[i].qty == 0)
		{
			cout << "\tQuantity: Out Of Stock" << endl << endl;
		}
		else
		{
			cout << "\tQuantity: " << (*inventory)[i].qty << endl << endl;
		}
	}
}
// Sample: backpack(player.inventory, player, Fist, Crocks)
void backpack(vector<ItemSlot>* inventory, Player* player)
{
	int pick;
	int select;

	do
	{

		for (int i = 0; i < inventory->size(); i++)
		{
			cout << (i + 1) << ": " << (*inventory)[i].item.name << endl;
			cout << "\tValue: " << (*inventory)[i].item.value << endl;
			cout << "\tQuantity: " << (*inventory)[i].qty << endl << endl;
		}

		cout << "(0 to Exit) Choice: ";
		cin >> pick;
		if (pick > 0 && pick <= (*inventory).size())
		{
			pick--;
			cout << "\n\t" << (*inventory)[pick].item.name << endl;
			cout << "\tValue: " << (*inventory)[pick].item.value << endl;
			cout << "\tQuantity: " << (*inventory)[pick].qty << endl << endl;

			cout << "1. Equip/Unequip\n2. Use\n3. Discard\n" << endl;
			cout << "(0 to Exit) Choice: ";
			cin >> select;

			switch (select)
			{
			case 1:
				if ((*inventory)[pick].item.name == "Dagger" && (*player).equippedWeapon.name == "Dagger")
				{
					cout << "You put the dagger back into your backpack" << endl;
					(*player).equippedWeapon = player->defaultWeapon;
				}
				else if ((*inventory)[pick].item.name == "Boots" && (*player).equippedWearable.name == "Boots")
				{
					cout << "You put the boots back into your backpack" << endl;
					(*player).equippedWearable = player->defaultWearable;
				}
				else if ((*inventory)[pick].item.name == "Dagger")
				{
					(*player).equippedWeapon.name = "Dagger";
					(*player).equippedWeapon.damage_bonus = 3;
				}
				else if ((*inventory)[pick].item.name == "Boots")
				{
					(*player).equippedWearable.name = "Boots";
					(*player).equippedWearable.initiative_bonus = 5;
				}
				else
				{
					cout << "You cannot equip this";
				}
			case 2:

				break;

			case 3:

				break;

			default:
				break;
			}
		}
		else
		{
			continue;
		}
		pick++;
	} while (pick != 0);
}

void classSelect(Player* player)
{
	string role;

	for (;;)
	{
		cout << "\nWhat class would you like to be?\nList of classes:\n\n\tRogue\n\tWizard\n\tFighter\n" << endl << flush;
		cin >> role;
		if (cin.fail())
		{
			cerr << "\nPlease select an available Role\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (role != "Rogue" && role != "Fighter" && role != "Wizard")
		{
			cerr << "\nSorry What? Did you misspell?\n" << endl;
			continue;
		}
		break;
	}

	string Rogue = "Rogue";
	string Warrior = "Warrior";
	string Wizard = "Wizard";
	(*player).role.name = role;

	if (role == "Rogue") {
		(*player).role.name = Rogue;
		(*player).role.maxHealth = 25;
		(*player).role.health = 25;
		(*player).role.damage = 5;
		(*player).role.initiative_bonus = 5;
	}
	else if (role == "Warrior") {
		(*player).role.name = Warrior;
		(*player).role.maxHealth = 35;
		(*player).role.health = 35;
		(*player).role.damage = 9;
		(*player).role.initiative_bonus = 0;
	}
	else {
		(*player).role.name = Wizard;
		(*player).role.health = 30;
		(*player).role.maxHealth = 30;
		(*player).role.damage = 7;
		(*player).role.initiative_bonus = 2;
	}
}

void fillHealth(Player* player)
{
	(*player).role.health = (*player).role.maxHealth;
}

void invTransaction(vector<ItemSlot>* inventory, vector<ItemSlot>* inventory2, int choice)
{
	vector<ItemSlot>::iterator iter;
	bool itemFound = false;

	for (iter = (*inventory).begin(); iter != (*inventory).end(); iter++)
	{
		if (iter->item.name == (*inventory2)[choice].item.name)
		{
			(*inventory)[distance((*inventory).begin(), iter)].qty++;
			itemFound = true;
		}
	}

	if (!itemFound)
	{
		ItemSlot slot;
		slot.item.name = (*inventory2)[choice].item.name;
		slot.item.value = (*inventory2)[choice].item.value;
		slot.qty = 1;
		inventory->push_back(slot);
	}
}

void printName(string playerFirstName, string playerLastName)
{
	cout << playerFirstName;
	cout << " ";
	cout << playerLastName;
}

void askNumber(int choice, int low, int high)
{
	for (;;)
	{
		cout << "What would you like to buy? (0 to Exit) " << flush;
		cin >> choice;
		if (cin.fail())
		{
			cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (choice < low || choice > high)
		{
			cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
			continue;
		}
		break;
	}
}

//void askQuestion(string choice, int low, int high)
//{
//	for (;;)
//	{
//		cout << "What would you like to buy? (0 to Exit) " << flush;
//		cin >> choice;
//		if (cin.fail())
//		{
//			cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
//			cin.clear();
//			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//			continue;
//		}
//		if (choice < low || choice > high)
//		{
//			cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
//			continue;
//		}
//		break;
//	}
//}


//Enemy::Thief
//{
// string = "Thief";
// health 18;
// damage 4 - 6 (randomly generated);
// initiative 15;
//}
//Enemy::learned
//{
//	name "Learned";
//health 20;
//damage 6 - 8 (randomly generated);
//initiative 12;
//}
//Enemy::brute
//{
//	name "Brute";
//health 20;
//damage 8 - 10 (randomly generated);
//initiative 10;
//1 damage reduction(armor);
//}