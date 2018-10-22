
///FOLLOW THIS: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm


/* DateBase class which uses Singleton design pattern, to have only one instance of it
 * and access it from every object we want. */


 /*
  * Usage: Where you want to access database use DB::getInstance()->YourCreatedmethod();
  *
  *
  * */

#include "Player.h"
#include "Monster.h"
#include "Shop.h"
#include "libsqlite.hpp"
#include <iostream>
#include "leaderboard.h"

class DB
{
private:
	/* Here will be the instance stored. */
	static DB* instance;

	/* Private constructor to prevent instancing. */
	DB();

public:
	//sqlite db;
   //static int callback(void *data, int argc, char **argv, char **azColName);

   //char *zErrMsg = 0;
   //int rc;

   /* Static access method. */
	static DB* getInstance();

	//METHODS
	int testDBConnection(); //Initialization function
	int openDatabase();
	bool validateLogin(std::string username, std::string password);
	bool loadPlayerData(Player &player, std::string username, std::string password);
	bool createPlayer(Player & player, std::string username, std::string password, std::string name);
	bool savePlayerData(Player &player, std::string username, std::string password);
	bool loadShopRandomWeaponData(Shop &shop, Player &player);
	bool loadShopRandomArmorData(Shop &shop, Player &player);
	bool loadShopRandomConsumableData(Shop &shop, Player &player);


	//saving - loading - creating player inventory and equipment instances
	std::string getItemType(int index);
	bool createPlayerInventoryInstance(Player &player);
	bool createPlayerEquipmentInstance(Player &player);
	bool loadPlayerInventory(Player &player);
	bool loadPlayerEquipment(Player &player);
	bool savePlayerInventory(Player &player);
	bool savePlayerEquipment(Player &player);

	bool loadSpecificItemData(Player &player, std::string itemType, std::string iore, int id, int index = -1);
	bool loadRandomItemData(Player &player, std::string itemType);

	bool loadMonsterData(Monster &monster);

	std::vector<entry> getLeaderboardData(); // define the getLeaderboardData method that will pull data from the database

};


