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
	int initiative_bonus;
	bool equipped;
};
class Weapon : public Item
{
public:
	int damage_bonus;
	bool equipped;
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
	Weapon equippedWeapon;
	vector<ItemSlot> inventory;
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
	void virtual attack(int &health, string enemyName) const;
};
Enemy::Enemy(string name, int initiative, int damage, int health, int armor) :

	mDamage(damage)
{}
void Enemy::attack(int &health, string enemyName) const
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
void attack();
void fight(Enemy enemy, Player player, Role role, Wearable wearable);
void use();
void discard();
void displayInventory(vector<ItemSlot>* inventory);
void invTransaction(vector<ItemSlot>* inventory, vector<ItemSlot>* inventory2, int choice);
void printName(string playerFirstName, string playerLastName);
void classSelect(string role, Player player);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	unsigned int business = 0;
	string pFN;
	string pLN;
	int age;
	char yesno = 'n';
	int choice = 0;
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
	

	merchant.inventory.push_back(mSlot1);
	merchant.inventory.push_back(mSlot2);
	merchant.inventory.push_back(mSlot3);
	merchant.inventory.push_back(mSlot4);
	merchant.inventory.push_back(mSlot5);
	player.inventory.push_back(pSlot1);

	Thief TheThief("Thief", 15, 4, 18, 0);
	// Learned
	// Brute

//intro: 
//
	cout << "What is your first name?"<< endl;
	cin >> pFN;
	cout << "What is your last name?" << endl;
	cin >> pLN;
	cout << "What class would you like to be?\nList of classes:\n\tRogue\n\tWizard\n\tFighter" << endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Role needs to be changed?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cin >> role;
	classSelect(role, player);
	cout << "Lastly, how old are you?\n";
	cin >> age;
	player.age = age;
//    do loop
//    {
//        cout choices you made above
//
//        cout: you are a princess sleeping in bed to wake up uncomfortable and decide it might be
//              best to do something about it.
//
//        cout:   You can either
//                1. Go to the Well
//                2. Go to the Store
//                3. Check under your mattress
//                4. Open Backpack
//
//        cin choice
//
//        switch statement
//        {
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
//                switch case 0:
	cout << "\nShopkeep: Well hi, ";
	printName(pFN, pLN);
	cout << "! How can I help you today? \n ";
	do
	{
		for (;;)
		{
			cout << "\n0 - I want to make a purchase!\n1 - I want to sell my items!\n2 - I would like to leave!\n\nChoice: " << flush;
			cin >> business;
			if (cin.fail())
			{
				cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
			cout << "\nShopkeep: A paying customer? Of course, happy to help!\nHave a look at my wares!\n\nWares:\n";
			displayInventory(&merchant.inventory);

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
					cout << "\nShopkeep: Outta luck, wish I had more to sell you, but I don't.\n\nCan I help you with something else?\n";
					break;
				}

				cout << "\nWould you like to buy the " << merchant.inventory[choice].item.name << "?" << endl;
				cout << "Your current gold: " << player.pGold << " $" << endl;
				cout << "This " << merchant.inventory[choice].item.name << " costs " << merchant.inventory[choice].item.value << "$" << endl;

				if (player.pGold < merchant.inventory[choice].item.value)
				{
					cout << "Sorry it looks like you don't have enough gold for that.\n\nCan I help you with something else?\n";
					break;
				}

				cout << "Will you buy this " << merchant.inventory[choice].item.name << "? (y/n)\n" << endl;
				cin >> yesno;

				if (yesno == 'y')
				{
					cout << "\nYou bought the " << merchant.inventory[choice].item.name << "!" << endl;
					player.pGold -= merchant.inventory[choice].item.value;
					merchant.inventory[choice].qty -= 1;
					invTransaction(&player.inventory, &merchant.inventory, choice);
					cout << "your remaining gold balance is : " << player.pGold << "$" << endl;
				}
				else
				{
					cout << "you did not buy the " << merchant.inventory[choice].item.name << "." << endl;
				}
			}

			cout << "\nIs there anything else I can help you with?\n\n";
			break;

		case 1:
			cout << "\nShopkeep: I'm always happy to buy stuff you don't need, materials are getting scarce here.\n";
			cout << "\nYour items:\n";
			displayInventory(&player.inventory);

			for (;;)
			{
				cout << "Which item do you want to sell? (0 To Exit) " << flush;
				cin >> choice;

				if (cin.fail())
				{
					cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
				cout << "\nWould you like to sell the " << player.inventory[choice].item.name << "?" << endl;
				cout << "This " << player.inventory[choice].item.name << " will pay " << player.inventory[choice].item.value / 2 << "$" << endl;
				cout << "Merchant gold: " << merchant.mGold << "$" << endl;
				cout << "Will you sell this " << player.inventory[choice].item.name << "? (y/n)" << endl;
				cin >> yesno;

				if (yesno == 'y')
				{
					cout << "You sold the " << player.inventory[choice].item.name << "!" << endl;
					player.pGold += player.inventory[choice].item.value / 2;
					cout << "your remaining gold balance is : " << player.pGold << "$" << endl;
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
					cout << "You did not sell the " << player.inventory[choice].item.name << "." << endl;
				}
			}

			cout << "\nIs there anything else I can help you with?\n\n";
			break;

		case 2:
			cout << "\nShopkeep: Well, if you change your mind, you know where to find me.\n";
			break;

		default:
			break;

		} while (business < 0 && business > 1);

	} while (business != 2);
	
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
//        {
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
//            }
//    } while player health > 0 && player win = false
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
			cout << "1. Attack\n 2. Use Item\n 3. Run Away!\n";
			cin >> playerChoice;

			switch (playerChoice)
			{
				case 1:
					cout << "You hit " << enemy.name << "for " << player.role.damage + player.equippedWeapon.damage_bonus << endl;
					break;
				case 2:
			

					break;
				case 3:
			
					break;
			}
			cout << "Turn change!" << endl;
			playerTurnHad = true;
        }
	} while (player.role.health > 0 && enemy.health > 0);
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

void attack()
{

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

void backpack(vector<ItemSlot>* inventory)
{
	int pick;
	do{

		for (int i = 0; i < inventory->size(); i++)
		{
		cout << (i + 1) << ": " << (*inventory)[i].item.name << endl;
		cout << "\tValue: " << (*inventory)[i].item.value << endl;
		cout << "\tQuantity: " << (*inventory)[i].qty << endl << endl;
		}
	 
		cin >> pick;
		cout << "1. Equip\n 2. Use\n 3. Discard" << endl;
		cout << "0. Go back" << endl;

	} while (pick > 0 && pick < inventory->size());
}

void classSelect(string role, Player player) 
{
	string Rogue = "Rogue";
	string Warrior = "Warrior";
	string Wizard = "Wizard";
	player.role.name = role;

	if (role == "Rogue") {
		player.role.name = Rogue;
		player.role.health = 25;
		player.role.damage = 4-6;
		player.role.initiative_bonus = 5;
	}
	else if (role == "Warrior") {
		player.role.name = Warrior;
		player.role.health = 35;
		player.role.damage = 8-10;
		player.role.initiative_bonus = 0;
	}
	else {
		player.role.name = Wizard;
		player.role.health = 30;
		player.role.damage = 6-8;
		player.role.initiative_bonus = 2;
	}
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