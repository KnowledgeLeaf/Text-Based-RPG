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
	string mName = "";
	int value = 0;
};

class Consumable : public Item
{
public:
	int uses;
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
	item.mName = name;
	item.value = value;
	qty = quantity;
}

class Role
{
public:
	string name = "";
	int health = 0;
	int maxHealth = 0;
	int damage = 0;
	int initiative_bonus = 0;
};

class Player
{
public:
	string name = "";
	int age = 0;
	int pGold = 100;
	Role role;
	Wearable equippedWearable;
	Wearable defaultWearable;
	Weapon equippedWeapon;
	Weapon defaultWeapon;
	vector<ItemSlot> inventory;
	bool likesWater = true;
	bool win = false;
};

class Enemy
{
	int mDamage = 0;
public:
	Enemy(string name = "Enemy", int initiative = 0, int damage = 0, int health = 0, int armor = 0);
	string mName;
	int mHealth;
	int mInitiative;
	int mArmor;
	void virtual attack(int& health, string enemyName) const;
};

Enemy::Enemy(string name, int initiative, int damage, int health, int armor) :
	mName(name),
	mInitiative(initiative),
	mDamage(damage),
	mHealth(health),
	mArmor(armor)
{}

void Enemy::attack(int& health, string enemyName) const
{
	std::cout << enemyName << " hits you for " << mDamage << " damage." << endl;
	(health) -= mDamage;
}

class Thief : public Enemy
{
public:
	Thief(string name, int health, int initiative, int damage, int armor);
};

Thief::Thief(string name, int initiative, int damage, int health, int armor) :
	Enemy(name, initiative, damage, health, armor)
{}

class Learned : public Enemy
{
public:
	Learned(string name, int health, int initiative, int damage, int armor);
};

Learned::Learned(string name, int initiative, int damage, int health, int armor) :
	Enemy(name, initiative, damage, health, armor)
{}

class Brute : public Enemy
{
public:
	Brute(string name, int health, int initiative, int damage, int armor);
};

Brute::Brute(string name, int initiative, int damage, int health, int armor) :
	Enemy(name, initiative, damage, health, armor)
{}

class Merchant
{
public:
	int mGold = 300;
	vector<ItemSlot> inventory;
};

void pAttack(Enemy* enemy, Player* player);
void askNumber(int choice, int low, int high);
void backpack(vector<ItemSlot>* inventory, Player* player,Enemy *current);
void classSelect(Player* player);
int diceInitiative();
void discardItem(int choice, Player &player);
void displayInventory(vector<ItemSlot>* inventory);
void fight(Enemy& enemy, Player& player, Role& role, Wearable& wearable, Enemy *current);
void fillHealth(Player* player);
void invTransaction(vector<ItemSlot>* inventory, vector<ItemSlot>* inventory2, int choice);
void printName(string playerFirstName, string playerLastName);
void waterBucketCheck(Player& player);
void useItem(Item item, Player& player, Enemy *enemy);
void useItem(Item item, Player& player);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	unsigned int business = 0;
	string pFN;
	string pLN;
	int age;
	char yesno = 'n';
	bool fighting = false;
	

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
	Item pea;
	Enemy *currentEnemy = 0;

	pain_meds.mName = "Pain Meds";
	pain_meds.value = 100;
	fancy_book.mName = "Fancy book";
	fancy_book.value = 100;
	dagger.mName = "Dagger";
	dagger.value = 100;
	smokebomb.mName = "Smokebomb";
	smokebomb.value = 100;
	boots.mName = "Boots";
	boots.value = 100;
	water_bucket.mName = "Water Bucket";
	water_bucket.value = 100;
	pea.mName = "Pea";
	pea.value = 1;

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
	ItemSlot slot;

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
	player.equippedWeapon = Fist;
	player.equippedWearable = Crocks;

	Thief TheThief("Thief", 15, 4, 18, 0);
	Learned TheLearned("Learned", 12, 6, 20, 0);
	Brute TheBrute("Brute", 10, 8, 20, 1);

	std::cout << "What is your first name?" << std::endl;
	std::cin >> pFN;
	std::cout << "\nWhat is your last name?" << std::endl;
	std::cin >> pLN;
	classSelect(&player);
	for(;;)
	{	
		std::cout << "\nLastly, how old are you?\n" << flush;
		std::cin >> age;
		if (std::cin.fail())
		{
			cerr << "\n That choice is invalid.\n" << endl;
			std::cin.clear();
			std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}

	player.age = age;

	// main game loop
	//sanitized
	do
	{
		for (;;)
		{
		std::cout << "\nFirst Name: " << pFN << "\nLast Name: " << pLN << "\nRole: " << player.role.name << "\nAge: " << age << std::endl;
		fillHealth(&player);

		std::cout << "\n--------------------------------------------\nYou are a princess sleeping in bed." << std::endl;
		std::cout << "You wake up uncomfortable and decide it might be best to do something about it.\n--------------------------------------------" << endl;

		std::cout << "You can either:\n"
			"\t1. Go to the Well\n"
			"\t2. Go to the Store\n"
			"\t3. Check under your mattress\n"
			"\t4. Open Backpack\n" << std::endl;
		std::cout << "Choice: " <<flush;
		std::cin >> choice;
		std::cout << std::endl;
		
			if (std::cin.fail())
			{
				cerr << "\n That choice is invalid.\n" << endl;
				std::cin.clear();
				std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			if (choice < 1 || choice > 4)

			{
				cerr << "\n That choice is invalid.\n" << endl;
				continue;
			}
			break;
		}

		switch (choice)
		{
		case 1:
			//go to well
			//sanitized
			for (;;)
			{
				std::cout << "You go to the well and remember that you have an empty bucket that you could fill with water.\n"
					"Also, while strolling you realize that the scenery around here is very pretty.\nIt might serve you well to look around for a bit.\n"
					"However, you also do still feel tired and might consider just going back to bed.\n"
					"Lastly as always you can open your back pack to check what inside\n\n"
					"\n\t1.Get water.\n\t2.Look around and admire the scenery.\n\t3.You're tired so you go back to bed\n\t4.Open Backpack.\nChoice:" << flush;
				std::cin >> action;
				if (std::cin.fail())
				{
					cerr << "\n That choice is invalid.\n" << endl;
					std::cin.clear();
					std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (action < 1 || action > 4)

				{
					cerr << "\n That choice is invalid.\n" << endl;
					continue;
				}
				break;
			}
			switch (action)
			{


			case 1://get water
				waterBucketCheck(player);

				std::cout << "\nYou fill your bucket with water, feel tired and head back to bed with your water bucket now full.";
				break;
			case 2://coin fight
				std::cout << "\nAs you look around you find a coin on the ground, as you go to pick it up you feel a dagger being pressed up against your back.\n'that coin is MINE and so is all of the rest of your money.'\n\n";
				fight(TheThief, player, player.role, player.equippedWearable,currentEnemy);
				break;
			case 3://tbtb
				std::cout << "\nYou feel tiredness start to take you over and decide that your bed is the most comfortable spot";
				break;
			case 4://Open Backpack
				std::cout << "\nYou decide to open your backpack to check what is inside.";
				backpack(&player.inventory, &player,currentEnemy);
				break;
			default:
				std::cout << "\nuhh ohh we messed up ohh well damn";
				break;
			}
			break;
		case 2: 
			//go to store
			//sanitized
				for (;;)
				{
					std::cout << "On the way to the store you check your pockets and realize you have " << player.pGold << "g in your pocket."
						"\nWith this in mind do you want to enter the front door or sneak around back.\n\t"
						"\n\t1: Go inside\n\t2: Go around back\n\nChoice:" << flush;
					std::cin >> action;
					if (std::cin.fail())
					{
						cerr << "\n That choice is invalid.\n" << endl;
						std::cin.clear();
						std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					if (action < 1 || action > 2)

					{
						cerr << "\n That choice is invalid.\n" << endl;
						continue;
					}
					break;
				}

			switch (action)
			{

			case 1://SHOPPING

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

							std::cout << "\nWould you like to buy the " << merchant.inventory[choice].item.mName << "?" << endl;
							std::cout << "Your current gold: " << player.pGold << " $" << endl;
							std::cout << "This " << merchant.inventory[choice].item.mName << " costs " << merchant.inventory[choice].item.value << "$" << endl;

							if (player.pGold < merchant.inventory[choice].item.value)
							{
								std::cout << "Sorry it looks like you don't have enough gold for that.\n\nCan I help you with something else?\n";
								break;
							}

							std::cout << "Will you buy this " << merchant.inventory[choice].item.mName << "? (y/n)\n" << endl;
							std::cin >> yesno;

							if (yesno == 'y')
							{
								std::cout << "\nYou bought the " << merchant.inventory[choice].item.mName << "!" << endl;
								player.pGold -= merchant.inventory[choice].item.value;
								merchant.inventory[choice].qty -= 1;
								invTransaction(&player.inventory, &merchant.inventory, choice);
								std::cout << "your remaining gold balance is : " << player.pGold << "$" << endl;
							}
							else
							{
								std::cout << "You did not buy the " << merchant.inventory[choice].item.mName << "." << endl;
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
							std::cout << "\nWould you like to sell the " << player.inventory[choice].item.mName << "?" << std::endl;
							std::cout << "This " << player.inventory[choice].item.mName << " will pay " << player.inventory[choice].item.value / 2 << "$" << std::endl;
							std::cout << "Merchant gold: " << merchant.mGold << "$" << std::endl;
							std::cout << "Will you sell this " << player.inventory[choice].item.mName << "? (y/n)" << std::endl;
							std::cin >> yesno;

							if (yesno == 'y')
							{
								std::cout << "You sold the " << player.inventory[choice].item.mName << "!" << std::endl;
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
								std::cout << "You did not sell the " << player.inventory[choice].item.mName << "." << std::endl;
							}
						}

						std::cout << "\nIs there anything else I can help you with?\n\n";
						break;

					case 2:
						std::cout << "\nShopkeep: Well, if you change your mind, you know where to find me.\n";
						break;

					default:
						break;
					}
				} while (business != 2);//shop mechanic is hidden here <--
				break; // end of CASE 1

			case 2://go around back
				std::cout << "As you make your way around to the back of the store to go and rob it, you run in to someone who is reading a book, and bump the book out of there hand causing them to loose there page.\n'I was in the middle of a really good part'.\n\n";
				fight(TheLearned, player, player.role, player.equippedWearable,currentEnemy);
				break;

			case 3://go back to bed
				std::cout << "You decide that its probably time to go back to bed and rest up some more.";
				break;

			default:
				break;
			};
			break;

		case 3://check under mattress
			//sanitized
			for (;;)
			{
			std::cout << "Under your matress you find a pea, and wonder 'how did that get there anyway?'\nIt seems that you would have a couple of options to do with that pea.\n1.take it\n2.eat it\n3.ignore it.\n\nchoice:" << flush;;
			std::cin >> action;
				if (std::cin.fail())
				{
					cerr << "\n That choice is invalid.\n" << endl;
					std::cin.clear();
					std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (action < 1 || action > 3)

				{
					cerr << "\n That choice is invalid.\n" << endl;
					continue;
				}
				break;
			}
			switch (action)
			{
			case 1://take the pea
				std::cout << "\nYou decide to take the pea with you and put it into your backpack then go back to bed\n";
				slot.item = pea;
				slot.qty = 1;
				player.inventory.push_back(slot);
				break;

			case 2://eat the pea
				std::cout << "\nYou decide to eat the pea.\n";
				useItem(pea, player);
				break;

			case 3://ignore the pea
				std::cout << "\nYou decide to ignore the pea and try to go back to sleep, uncomfortable and still tired you start to fall into your nightmares.\n A Brute appears\n\n";
				fight(TheBrute, player, player.role, player.equippedWearable,currentEnemy);
				break;

			default://uhh ohh
				std::cout << "\nuhh ohh\n";
				break;
			}
			break;

		case 4://check backpack
			backpack(&player.inventory, &player,currentEnemy);
			break;

		default: std::cout << "\nLooks like thats not an option you can choose\n";
		} // end switch choice
	} while ((player.role.health > 0) && (player.win == false));
	if (player.win = true) {
		std::cout << "\nGame Over.\n\n";
	}
	else {
		std::cout << "\nYou Died.\n\nGame Over.\n\n";
	}
	return 0;
}

void pAttack(Enemy* enemy, Player* player)
{
	int damage;
	damage = (*player).role.damage + (*player).equippedWeapon.damage_bonus - (*enemy).mArmor;

	std::cout << "You hit " << (*enemy).mName << " for " << damage << endl;
	(*enemy).mHealth -= damage;
}

void askNumber(int choice, int low, int high)
{
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
		if (choice < low || choice > high)
		{
			cerr << "\nShopkeep: What? I couldn't hear you.\n" << endl;
			continue;
		}
		break;
	}
}

void backpack(vector<ItemSlot> *inventory, Player *player, Enemy *current)
{
	int pick;
	int select;
	bool fighting;

	do
	{

		for (int i = 0; i < inventory->size(); i++)
		{
			std::cout << (i + 1) << ": " << (*inventory)[i].item.mName << endl;
			std::cout << "\tValue: " << (*inventory)[i].item.value << endl;
			std::cout << "\tQuantity: " << (*inventory)[i].qty << endl << endl;
		}
		for (;;)
		{
		std::cout << "Which item do you want to use?\n";
		std::cout << "(0 to Exit) Choice: "<<flush;
		std::cin >> pick;
			if (std::cin.fail())
			{
				cerr << "\n That choice is invalid.\n" << endl;
				std::cin.clear();
				std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			break;
		}
		if (pick > 0 && pick <= (*inventory).size())
		{
			pick--;
			for (;;)
			{
			std::cout << "\n\t" << (*inventory)[pick].item.mName << endl;
			std::cout << "\tValue: " << (*inventory)[pick].item.value << endl;
			std::cout << "\tQuantity: " << (*inventory)[pick].qty << endl << endl;

			std::cout << "1. Equip/Unequip\n2. Use\n3. Discard\n" << endl;
			std::cout << "(0 to Exit) Choice: "<<flush;;
			std::cin >> select;;
				
				if (std::cin.fail())
				{
					cerr << "\n That choice is invalid.\n" << endl;
					std::cin.clear();
					std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (select < 0 || select > 3)

				{
					cerr << "\n That choice is invalid.\n" << endl;
					continue;
				}
				break;
			}
			switch (select)
			{
			case 1:
				if ((*inventory)[pick].item.mName == "Dagger" && (*player).equippedWeapon.mName == "Dagger")
				{
					std::cout << "You put the dagger back into your backpack" << endl;
					(*player).equippedWeapon = player->defaultWeapon;
				}
				else if ((*inventory)[pick].item.mName == "Boots" && (*player).equippedWearable.mName == "Boots")
				{
					std::cout << "You put the boots back into your backpack" << endl;
					(*player).equippedWearable = player->defaultWearable;
				}
				else if ((*inventory)[pick].item.mName == "Dagger")
				{
					std::cout << "You wield the Dagger in your hand like an experienced rogue.(damage+3)\n\n";
						(*player).equippedWeapon.mName = "Dagger";
					(*player).equippedWeapon.damage_bonus = 3;
				}
				else if ((*inventory)[pick].item.mName == "Boots")
				{
					std::cout << "You put the boots on your hands and think 'Nooo not here.' \nSlidding them then onto your feet, you hop and realize they were almost made for you.(initiative bonus +5)\n";
					(*player).equippedWearable.mName = "Boots";
					(*player).equippedWearable.initiative_bonus = 5;
				}
				else
				{
					std::cout << "You cannot equip this";
				}
				break;
			case 2:
				if (fighting = true) 
				{
					useItem((*inventory)[pick].item, *player, current);
				}
				else
				{
					useItem((*inventory)[pick].item, *player);
				}
				break;

			case 3:
				discardItem(pick, *player);
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

void classSelect(Player *player)
{
	string role;

	for (;;)
	{
		std::cout << "\nWhat class would you like to be?\nList of classes:\n\n\tRogue\n\tWizard\n\tFighter\n" << endl << flush;
		std::cin >> role;
		if (std::cin.fail())
		{
			cerr << "\nPlease select an available Role\n" << endl;
			std::cin.clear();
			std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
	string Fighter = "Fighter";
	string Wizard = "Wizard";
	(*player).role.name = role;

	if (role == "Rogue") {
		(*player).role.name = Rogue;
		(*player).role.maxHealth = 25;
		(*player).role.health = 25;
		(*player).role.damage = 5;
		(*player).role.initiative_bonus = 5;
	}
	else if (role == "Fighter") {
		(*player).role.name = Fighter;
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

int diceInitiative()
{
	int randomNumber;
	int dieRoll;

	randomNumber = rand();
	dieRoll = (randomNumber % 20) + 1;

	return dieRoll;
}

void displayInventory(vector<ItemSlot> *inventory)
{
	for (int i = 0; i < inventory->size(); i++)
	{
		std::cout << (i + 1) << ": " << (*inventory)[i].item.mName << endl;
		std::cout << "\tValue: " << (*inventory)[i].item.value << endl;

		if ((*inventory)[i].qty == 0)
		{
			std::cout << "\tQuantity: Out Of Stock" << endl << endl;
		}
		else
		{
			std::cout << "\tQuantity: " << (*inventory)[i].qty << endl << endl;
		}
	}
}

void discardItem(int choice, Player &player)
{
	vector<ItemSlot>::iterator eraser;
	eraser = player.inventory.begin() + choice;
	player.inventory.erase(eraser);
}

void fight(Enemy &enemy, Player &player, Role &role, Wearable &wearable, Enemy *current)
{
	int dice;
	int diceInitiative();
	int playerInitiative;
	bool playerTurnHad;
	int playerChoice;
	playerTurnHad = false;
	dice = diceInitiative();
	current = &enemy;
	

	playerInitiative = (dice + role.initiative_bonus + wearable.initiative_bonus);

	do
	{
		if ((enemy.mInitiative > playerInitiative) || (playerTurnHad == true) && (enemy.mHealth > 0))
		{
			enemy.attack(role.health, enemy.mName);
			playerTurnHad = false;
		}

		if (playerTurnHad == false && player.role.health > 0)
		{
			//do player turn

			for (;;) {

				std::cout << "Player Health: " << player.role.health << "\t Enemy Health: " << enemy.mHealth << endl;
				std::cout << "\t1. Attack\n\t2. Use Item\n\t3. Run Away!\n\nChoice:"<<flush;
				std::cin >> playerChoice; 
				
				if (std::cin.fail())
				{
					cerr << "\n That choice is invalid.\n" << endl;
					std::cin.clear();
					std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (playerChoice < 1 || playerChoice > 3)

				{
					cerr << "\n That choice is invalid.\n" << endl;
					continue;
				}
				break;
			}

				switch (playerChoice)
				{
				case 1:
					pAttack(&enemy, &player);
					std::cout << "\nTurn change!\n" << endl;
					break;
				case 2:
					std::cout << "\nYou riffle through your backpack for something useful.\n";
					backpack(&player.inventory, &player,current);
					std::cout << "Turn change!" << endl;
					continue;
				case 3:
					std::cout << "\nYou run away back to bed\n";
					break;
				default:
					break;
				}
			
			
			playerTurnHad = true;
			
		}
		if (enemy.mHealth < 0)
			player.pGold += 50;
	} while (player.role.health > 0 && enemy.mHealth > 0 && playerChoice != 3);
	current = 0;
}

void fillHealth(Player *player)
{
	(*player).role.health = (*player).role.maxHealth;
}

void invTransaction(vector<ItemSlot> *inventory, vector<ItemSlot> *inventory2, int choice)
{
	vector<ItemSlot>::iterator iter;
	bool itemFound = false;

	for (iter = (*inventory).begin(); iter != (*inventory).end(); iter++)
	{
		if (iter->item.mName == (*inventory2)[choice].item.mName)
		{
			(*inventory)[distance((*inventory).begin(), iter)].qty++;
			itemFound = true;
		}
	}

	if (!itemFound)
	{
		ItemSlot slot;
		slot.item.mName = (*inventory2)[choice].item.mName;
		slot.item.value = (*inventory2)[choice].item.value;
		slot.qty = 1;
		inventory->push_back(slot);
	}
}

void printName(string playerFirstName, string playerLastName)
{
	std::cout << playerFirstName;
	std::cout << " ";
	std::cout << playerLastName;
}

void waterBucketCheck(Player &player)
{
	vector<ItemSlot>::iterator iter;
	bool itemFound = false;
	
	if (player.likesWater = true)
	{
		for (iter = (player.inventory).begin(); iter != (player.inventory).end(); iter++)
		{
			if (iter->item.mName == "Water Bucket")
			{
				(player.inventory)[distance((player.inventory).begin(), iter)].qty += 1;
				itemFound = true;
			}
		}
	}
	else {
		std::cout << "It seems when you threw out your water bucket earlier you managed to punch a hole in the bottom and now it doesn't work.\n\nTLDR: NO WATTAH FOR U.";
	}

}

void useItem(Item item, Player& player, Enemy *enemy)
{
	if (item.mName == "Pea") {

		std::cout << "Having eaten the pea you suddenly feel yourself grow in size.\nYou look at the mirror on the wall and indeed you have grown,\n"
			"grown more powerful than even the prince himself that was fated to save you from this dastardly castle.\n\nCongratz player you have just won the never ending life of a princess\n\n";
		player.win = true;
	}

	if (item.mName == "Pain Meds") {
		std::cout << "You take the pain meds and feel much better(health restored to full)";
		player.role.health = player.role.maxHealth;
		
	}

	else if (item.mName == "Smokebomb") {
		
		std::cout << "You throw the smokebomb and managed to choke out your foe with it's gas. They die and you manage to steal their coin and get away back to bed.";
		enemy->mHealth = 0;
	}

	else {
		std::cout << "\nSorry you can't use this item the way you want... No eating boots or biting daggers here, you are a refined princess after all.\n\n";
	}
}

void useItem(Item item, Player& player)
{
	if (item.mName == "Pea") {

		std::cout << "\nHaving eaten the pea you suddenly feel yourself grow in size.\nYou look at the mirror on the wall and indeed you have grown,\n"
			"grown more powerful than even the prince himself that was fated to save you from this dastardly castle.\n\nCongratz player you have just won the never ending life of a princess\n\n";
		player.win = true;
	}

	else if (item.mName == "Pain Meds") {
		std::cout << "\nYou take the pain meds and feel much better(health restored to full)";
		player.role.health = player.role.maxHealth;
	}

	else {
		std::cout << "\nSorry you can't use this item the way you want... No eating boots or biting daggers here, you are a refined princess after all.";
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
// 
// //short story about the game
//intro sequence
//action scenario
//    turn-based combat?
//quest or purpose
//    stereotyipical non typical rescue the prince who fell down the well....Idiot.....
// 
// three customization options
//    personally thinking class, race,and age.
// 
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
// 
//import merchant assets
//    all the buying and selling stuff
//    display inventory of both the merchant and the player seperately
//    LITTERALLY ADD THE MERCHANT INVENTORY PROGRAM
// 
//three options that impact the story
//    skip combat through riddle for learned
//    get new items from merchant for free
//    loose all gold to win one combat.
// 
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
// 
//general knowhow
//    clear use of if else statements and or switch
// 
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