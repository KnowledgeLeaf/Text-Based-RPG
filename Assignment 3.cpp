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
	Role role;
	Wearable equippedWearable;
	Weapon equippedWeapon;
	vector<ItemSlot> inventory;
};
class Role
{
public:
	int health;
	int damage;
	int initiative_bonus;
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
class Item
{
public:
	string name;
	int value;
};

class Enemy
{
	int mDamage;
public:
	Enemy(string name = "Enemy", int initiative = 0, int damage = 0);
    string name;
    int initiative;
	void virtual attack() const;
};
Enemy::Enemy(string name, int initiative, int damage) :

	mDamage(damage)
{}
void Enemy::attack() const
{
	cout << "Enemy hits you for " << mDamage << "damage." << endl;
}

class Thief : public Enemy
{
	int hp;
	Thief(string name, int health, int initiative, int damage);
	void attack() const;
};
Thief::Thief(string name, int initiative, int damage, int health) :
	hp(health)
{
	Enemy(name, initiative, damage);
}
void Thief::attack() const
{
	Enemy::attack();
}
//enemy::thief
//{
//    name "Thief"
//    health 18
//    damage 4-6 (randomly generated)
//    initiative 15
//}
//enemy::learned
//{
//    name "Learned"
//    health 20
//    damage 6-8 (randomly generated)
//    initiative 12
//}
//enemy::brute
//{
//    name "Brute"
//    health 20
//    damage 8-10 (randomly generated)
//    initiative 10
//	  1 damage reduction (armor)
//}
//
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

int diceInitiative();
void attack();
void fight(Enemy enemy, Player player, Role role, Wearable wearable);
void use();
void discard();

int main()
{
	srand(static_cast<unsigned int>(time(0)));

//intro: 
//
//    cin name
//    cout list of classes
//        rogue
//        wizard
//        fighter
//    cin role (royal training extra beefy enemies sorta)
//    cin age
//
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
//                switch choices for buying/selling/making money (Copy Paste from Assignment 1 switch items)
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
			player.role.health -= enemy.damage;
			cout << "Enemy hits you for " << enemy.damage << "damage." << endl;
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
//    pain meds
//    fancy book
//    dagger
//    smokebomb (skip fight ie set enemy healkth = 0)
