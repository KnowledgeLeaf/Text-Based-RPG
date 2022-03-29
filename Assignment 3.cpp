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

class Player
{
public:
	string name;
	int age;
	int money;
	Role role;
	Wearable equippedWearable;
	Weapon equippedWeapon;
};

class Consumable : public Item
{
public:
	int uses;
	void use();
	void discard();
};
class Wearable : public Item
{
public:
	int initiative_bonus;
	bool equipped;
	void discard();
};
class Role
{
public:
	int health;
	int damage;
	int initiative_bonus;
};

class Item
{
public:
	string name;
	int value;
	void virtual discard();
};

class Weapon : public Item
{
public:
	int damage_bonus;
	bool equipped;
	void discard();
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

class Enemy
{
	int mDamage;
public:
	Enemy(string name = "Enemy", int initiative = 0, int damage = 0);
    string name;
    int initiative;
	void virtual attack(int health) const;
};
Enemy::Enemy(string name, int initiative, int damage) :

	mDamage(damage)
{}
void Enemy::attack(int health) const
{
	cout << "Enemy hits you for " << mDamage << "damage." << endl;
	(health) -= mDamage;
}

class Thief : public Enemy
{
public:
	int hp;
	Thief(string name, int health, int initiative, int damage);
	void attack(int health) const;
};
Thief::Thief(string name, int initiative, int damage, int health) :
	hp(health)
{
	Enemy(name, initiative, damage);
}
void Thief::attack(int health) const
{
	Enemy::attack(health);
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

class Merchant
{
public:
	int money;
};


int diceInitiative();
void attack();
void fight(Enemy enemy, Player player, Role role, Wearable wearable);
void use();
void discard();
void displayInventory(vector<ItemSlot>* inventory);
void invTransaction(vector<ItemSlot>* inventory, vector<ItemSlot>* inventory2, int choice);
void printName(string playerFirstName, string playerLastName);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	unsigned int business = 0;
	string pFN;
	string pLN;
	int age;
	char yesno = 'n';
	int choice = 0;

	vector<ItemSlot> merchantInventory;
	vector<ItemSlot> playerInventory;

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
	water_bucket.name = "Bow";
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
	pSlot1.qty = 0;
	Player pGold;
	pGold.money = 100;
	Merchant mGold;
	mGold.money = 300;

	merchantInventory.push_back(mSlot1);
	merchantInventory.push_back(mSlot2);
	merchantInventory.push_back(mSlot3);
	merchantInventory.push_back(mSlot4);
	merchantInventory.push_back(mSlot5);
	playerInventory.push_back(pSlot1);
	playerInventory.push_back(pSlot2);
	playerInventory.push_back(pSlot3);

	Thief TheThief("Thief", 15, 4, 18);

//intro: 
//
	cout << "What is your first name?"<< endl;
	cin >> pFN;
	cout << "What is your last name?" << endl;
	cin >> pLN;
	cout << "What class would you like to be?\nList of classes:\n rogue\n\twizard\n\tfighter";
	cin >> Role;
	cout << "Lastly, how old are you?";
	cin >> age;
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
			displayInventory(&merchantInventory);

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
				if (choice < 0 || choice > merchantInventory.size())
				{
					cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
					continue;
				}
				break;
			}

			choice -= 1;

			if (choice < merchantInventory.size() || choice > 0)
			{
				if (merchantInventory[choice].qty == 0)
				{
					cout << "\nShopkeep: Outta luck, wish I had more to sell you, but I don't.\n\nCan I help you with something else?\n";
					break;
				}

				cout << "\nWould you like to buy the " << merchantInventory[choice].item.name << "?" << endl;
				cout << "Your current gold: " << pGold.money << " $" << endl;
				cout << "This " << merchantInventory[choice].item.name << " costs " << merchantInventory[choice].item.value << "$" << endl;

				if (pGold.money < merchantInventory[choice].item.value)
				{
					cout << "Sorry it looks like you don't have enough gold for that.\n\nCan I help you with something else?\n";
					break;
				}

				cout << "Will you buy this " << merchantInventory[choice].item.name << "? (y/n)\n" << endl;
				cin >> yesno;

				if (yesno == 'y')
				{
					cout << "\nYou bought the " << merchantInventory[choice].item.name << "!" << endl;
					pGold.money -= merchantInventory[choice].item.value;
					merchantInventory[choice].qty -= 1;
					invTransaction(&playerInventory, &merchantInventory, choice);
					cout << "your remaining gold balance is : " << pGold.money << "$" << endl;
				}
				else
				{
					cout << "you did not buy the " << merchantInventory[choice].item.name << "." << endl;
				}
			}

			cout << "\nIs there anything else I can help you with?\n\n";
			break;

		case 1:
			cout << "\nShopkeep: I'm always happy to buy stuff you don't need, materials are getting scarce here.\n";
			cout << "\nYour items:\n";
			displayInventory(&playerInventory);

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

				if (choice < 0 || choice > playerInventory.size())
				{
					cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
					continue;
				}

				break;
			}

			choice -= 1;

			if (choice < playerInventory.size() || choice > 0)
			{
				cout << "\nWould you like to sell the " << playerInventory[choice].item.name << "?" << endl;
				cout << "This " << playerInventory[choice].item.name << " will pay " << playerInventory[choice].item.value / 2 << "$" << endl;
				cout << "Merchant gold: " << mGold.money << "$" << endl;
				cout << "Will you sell this " << playerInventory[choice].item.name << "? (y/n)" << endl;
				cin >> yesno;

				if (yesno == 'y')
				{
					cout << "You sold the " << playerInventory[choice].item.name << "!" << endl;
					pGold.money += playerInventory[choice].item.value / 2;
					cout << "your remaining gold balance is : " << pGold.money << "$" << endl;
					invTransaction(&merchantInventory, &playerInventory, choice);

					if (playerInventory[choice].qty > 1)
					{
						playerInventory[choice].qty -= 1;
					}
					else
					{
						vector<ItemSlot>::iterator eraser;
						eraser = playerInventory.begin() + choice;
						playerInventory.erase(eraser);
					}
				}
				else
				{
					cout << "You did not sell the " << playerInventory[choice].item.name << "." << endl;
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
	

//	choices for buying/selling/making money (Copy Paste from Assignment 1 switch items)
//                when you leave shop
//
//            if player leaves shop and has fancy book (inventory find item from assignment 1)
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
			enemy.attack(role.health);
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
					cout << "You hit " <<
					break;
				case 2:
			

					break;
				case 3:
			
					break;
			}

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
//check backpack function
//{
//    (Copy inventory system from Assignment 1)
//    use item option
//    discard item option
//}
//
//fight sequencing
//    roll initiative
//    turn based combat
//    afterwards loot random+gold between parameters per fight
//
//    thief need to roll 15 or higher to go first
//    brute needs a 10 
//    learned needs a 7
//
//
//merchant inventory
//		pain meds
//		fancy book
//		dagger
//		smokebomb (skip fight ie set enemy healkth = 0)
//		boots
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