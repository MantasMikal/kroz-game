#include "DB.h"
/* Null, because instance will be initialized on demand. */
DB* DB::instance = 0;
//Singleton
DB* DB::getInstance()
{
	if (instance == 0)
	{
		instance = new DB();
	}

	return instance;
}

// Used to initialize DB in Game::init()
int DB::testDBConnection()
{
	try { sqlite::sqlite db("DB.db"); }

	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return 0;
	}
	return 0;
}

bool DB::validateLogin(std::string username, std::string password) {
	//TODO
	//Hashing

	bool isUsernameValid = false;
	bool isPasswordValid = false;

	try {
		sqlite::sqlite db("DB.db");

		auto cur = db.get_statement();
		cur->set_sql("SELECT player_username, player_password FROM Player");
		cur->prepare();
		while (cur->step()) {
			if (cur->get_text(0) == username) {
				isUsernameValid = true;
				//std::cout << "Username: " << cur->get_text(0);
			}
			if (cur->get_text(1) == password) {
				isPasswordValid = true;
				//std::cout << "\nPassword: " << cur->get_text(1);
			}
		}
		if (isPasswordValid && isUsernameValid) {
			//std::cout << "\nLogin Success!\n";
			return true;
		}
		else {
			//std::cout << "Credentials are incorrect!\n";
			return false;
		}
	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}


}

bool DB::loadPlayerInventory(Player &player)
{
	try
	{
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("SELECT slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10 FROM Inventory WHERE playerID = ?;");
		cur->prepare();
		cur->bind(1, player.getID());
		cur->step();

		for (int i = 0; i < player.inv.getCapacity(); ++i)
		{
			int id = cur->get_int(i);
			if (id != 0)
			{
				std::string itemType = DB::getInstance()->getItemType(cur->get_int(i));

				DB::getInstance()->loadSpecificItemData(player, itemType, "i", id);
			}
		}


	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}
}

bool DB::loadPlayerEquipment(Player &player)
{
	try
	{
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("SELECT helmet, chest, legs, lArm, rArm, mainWeapon, sideWeapon FROM Equipment WHERE playerID = ?;");
		cur->prepare();
		cur->bind(1, player.getID());
		cur->step();

		for (size_t i = 0; i < player.equipment.size(); ++i)
		{
			if (cur->get_int(i) != 0)
			{
				DB::getInstance()->loadSpecificItemData(player, "Armor", "e", cur->get_int(i), i);
			}
		}

		if (cur->get_int(5) != 0) {
			DB::getInstance()->loadSpecificItemData(player, "Weapon", "e", cur->get_int(5), 0);
		}

		if (cur->get_int(6) != 0) {
			DB::getInstance()->loadSpecificItemData(player, "Weapon", "e", cur->get_int(6), 1);
		}

	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}
}

bool DB::savePlayerInventory(Player &player)
{
	try {
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("UPDATE Inventory SET slot1 = ?, slot2 = ?, slot3 = ?, slot4 = ?, slot5 = ?, slot6 = ?, slot7 = ?, slot8 = ?, slot9 = ?, slot10 = ? WHERE playerID = ?;");
		cur->prepare();

		for (int i = 0; i < player.inv.getCapacity(); ++i) {
			if (player.inv.getItem(i) != nullptr) {
				cur->bind(i + 1, player.inv.getItem(i)->getID());
			}
			else {
				cur->bind(i + 1, 0);
			}
		}

		cur->bind(11, player.getID());
		cur->step();
	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DB::savePlayerEquipment(Player &player)
{
	try {
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("UPDATE Equipment SET helmet = ?, chest = ?, legs = ?, lArm = ?, rArm = ?, mainWeapon = ?, sideWeapon = ? WHERE playerID = ?;");
		cur->prepare();

		cur->bind(1, player.equipment[0].getID());
		cur->bind(2, player.equipment[1].getID());
		cur->bind(3, player.equipment[2].getID());
		cur->bind(4, player.equipment[3].getID());
		cur->bind(5, player.equipment[4].getID());
		cur->bind(6, player.mainWeapon.getID());
		cur->bind(7, player.sideWeapon.getID());

		cur->bind(8, player.getID());
		cur->step();
	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DB::loadShopRandomWeaponData(Shop &shop, Player &player) {
	sqlite::sqlite db("DB.db");
	auto cur = db.get_statement();

	try
	{
		cur->set_sql("SELECT attackValue, strengthvalue, defenceValue, luckValue, weaponType, levelReq, itemName, itemRarity, itemValue, itemID FROM Items WHERE levelReq<=? AND weaponType IS NOT NULL ORDER BY RANDOM() LIMIT 10;");
		cur->prepare();
		cur->bind(1, player.getLVL());

		while (cur->step()) {
			shop.addWeapon(Weapon(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));

		}
	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return false;

	}
}

bool DB::loadShopRandomArmorData(Shop &shop, Player &player) {
	sqlite::sqlite db("DB.db");
	auto cur = db.get_statement();

	try
	{
		cur->set_sql("SELECT armorType, levelReq, defenceValue, attackValue, strengthvalue, luckValue, itemName, itemRarity, itemValue, itemID FROM Items WHERE levelReq<=? AND armorType IS NOT NULL ORDER BY RANDOM() LIMIT 10;");
		cur->prepare();
		cur->bind(1, player.getLVL());

		while (cur->step()) {
			shop.addArmor(Armor(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));
		}
	}

	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return false;

	}
}

bool DB::loadShopRandomConsumableData(Shop &shop, Player &player)
{ //for monster loot mainly, maybe shops aswell?   
	sqlite::sqlite db("DB.db");
	auto cur = db.get_statement();

	try
	{
		cur->set_sql("SELECT healthBoost, damageBoost, defenceBoost, itemName, itemRarity, itemValue, itemID FROM Items WHERE healthBoost IS NOT NULL OR damageBoost IS NOT NULL OR defenceBoost IS NOT NULL ORDER BY RANDOM() LIMIT 10;");
		cur->prepare();

		while (cur->step()) {
			shop.addConsumable(Consumable(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_text(3), cur->get_text(4), cur->get_int(5), cur->get_int(6)));

		}

		return true;
	}

	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return false;

	}


	return false;

}

std::string DB::getItemType(int index) {
	try
	{
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("SELECT weaponType, armorType FROM Items WHERE itemID = ? ");
		cur->prepare();
		cur->bind(1, index);

		cur->step();

		if (cur->get_int(0) != 0) {
			return "Weapon";
		}
		else if (cur->get_int(1) != 0) {
			return "Armor";
		}
		else {
			return "Consumable";
		}


	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;

	}

	return "";
}

bool DB::loadSpecificItemData(Player &player, std::string itemType, std::string iore, int id, int index)
{
	if (itemType == "Weapon")
	{
		try
		{
			sqlite::sqlite db("DB.db");
			auto cur = db.get_statement();

			cur->set_sql("SELECT attackValue, strengthvalue, defenceValue, luckValue, weaponType, levelReq, itemName, itemRarity, itemValue, itemID FROM Items WHERE itemID = ?;");
			cur->prepare();
			cur->bind(1, id);
			cur->step();

			if (iore == "i")
			{
				player.inv.addItem(Weapon(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));
			}
			else if (iore == "e")
			{
				if (index == 0)
				{
					player.mainWeapon = Weapon(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9));
				}
				else if (index == 1) {
					player.sideWeapon = Weapon(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9));
				}
			}

			return true;
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << endl;
			return false;
		}

	}
	else if (itemType == "Armor")
	{
		try
		{
			sqlite::sqlite db("DB.db");
			auto cur = db.get_statement();
			std::cout << id << endl;
			cur->set_sql("SELECT armorType, levelReq, defenceValue, attackValue, strengthvalue, luckValue, itemName, itemRarity, itemValue, itemID FROM Items WHERE itemID = ?;");
			cur->prepare();
			cur->bind(1, id);
			cur->step();

			if (iore == "i")
			{
				player.inv.addItem(Armor(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));
			}
			else if (iore == "e")
			{
				player.equipment[index] = Armor(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9));
			}
			return true;
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << endl;
			return false;
		}
	}
	else if (itemType == "Consumable")
	{
		try
		{
			sqlite::sqlite db("DB.db");
			auto cur = db.get_statement();

			cur->set_sql("SELECT healthBoost, damageBoost, defenceBoost, itemName, itemRarity, itemValue, itemID FROM Items WHERE itemID = ?;");
			cur->prepare();
			cur->bind(1, id);
			cur->step();

			player.inv.addItem(Consumable(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_text(3), cur->get_text(4), cur->get_int(5), cur->get_int(6)));
			return true;
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << endl;
			return false;
		}
	}
}

bool DB::loadRandomItemData(Player &player, string itemType)
{ //for monster loot mainly, maybe shops aswell?   
	sqlite::sqlite db("DB.db");
	auto cur = db.get_statement();

	if (itemType == "Weapon")
	{
		try
		{
			cur->set_sql("SELECT attackValue, strengthvalue, defenceValue, luckValue, weaponType, levelReq, itemName, itemRarity, itemValue, itemID FROM Items WHERE levelReq<=? AND weaponType IS NOT NULL ORDER BY RANDOM() LIMIT 1;");
			cur->prepare();
			cur->bind(1, player.getLVL());

			cur->step();

			player.inv.addItem(Weapon(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));
			std::cout << cur->get_text(6) << " added to your inventory." << endl;
			return true;
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}

	}
	else if (itemType == "Armor")
	{
		try
		{
			cur->set_sql("SELECT armorType, levelReq, defenceValue, attackValue, strengthvalue, luckValue, itemName, itemRarity, itemValue, itemID FROM Items WHERE levelReq<=? AND armorType IS NOT NULL ORDER BY RANDOM() LIMIT 1;");
			cur->prepare();
			cur->bind(1, player.getLVL());

			cur->step();

			player.inv.addItem(Armor(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_text(6), cur->get_text(7), cur->get_int(8), cur->get_int(9)));
			std::cout << cur->get_text(6) << " added to your inventory!\n\n";
			return true;
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}
	}
	else if (itemType == "Consumable")
	{
		try
		{
			cur->set_sql("SELECT healthBoost, damageBoost, defenceBoost, itemName, itemRarity, itemValue, itemID FROM Items WHERE healthBoost IS NOT NULL OR damageBoost IS NOT NULL OR defenceBoost IS NOT NULL ORDER BY RANDOM() LIMIT 1;");
			cur->prepare();

			cur->step();

			player.inv.addItem(Consumable(cur->get_int(0), cur->get_int(1), cur->get_int(2), cur->get_text(3), cur->get_text(4), cur->get_int(5), cur->get_int(6)));
			std::cout << cur->get_text(3) << " added to your inventory!\n\n";
		}
		catch (sqlite::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return false;

		}
	}
	return false;
}

bool DB::loadMonsterData(Monster &monster) {
	int health, ATT, xp;
	std::string name;

	try {
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();

		cur->set_sql("SELECT * FROM monsters ORDER BY RANDOM() LIMIT 1"); //select ONE random row
		cur->prepare();
		cur->step();

		name = cur->get_text(1);
		health = cur->get_int(2);
		ATT = cur->get_int(3);
		xp = cur->get_int(4);
	}

	catch (sqlite::exception e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	//set values
	monster.setName(name);
	monster.setMaxHealth(health);
	monster.setATT(ATT);
	monster.setXP(xp);

	return true;
}

bool DB::loadPlayerData(Player &player, std::string username, std::string password) {
	int Level, XP, STR, ATT, LCK, Gold, maxHealth, currentHealth, ID;
	std::string name, uName, pWord;

	try {
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();
		cur->set_sql("SELECT player_id, player_name, player_username, player_password, player_level, player_xp, player_str, player_att, player_lck, player_gold, player_maxHealth, player_currentHealth FROM Player");
		//TODO:
		//Optimization with WHERE
		cur->prepare();

		while (cur->step()) {
			ID = cur->get_int(0);
			name = cur->get_text(1);
			uName = cur->get_text(2);
			pWord = cur->get_text(3);
			Level = cur->get_int(4);
			XP = cur->get_int(5);
			STR = cur->get_int(6);
			ATT = cur->get_int(7);
			LCK = cur->get_int(8);
			Gold = cur->get_int(9);
			maxHealth = cur->get_int(10);
			currentHealth = cur->get_int(11);
			if (uName == username && pWord == password) break;
		}
	}

	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	//Set values
	player.setID(ID);
	player.setName(name);
	player.setUsername(uName);
	player.setPassword(pWord);
	player.setLVL(Level);
	player.setXP(XP);
	player.setSTR(STR);
	player.setATT(ATT);
	player.setLCK(LCK);
	player.setGP(Gold);
	player.setMaxHealth(maxHealth);
	player.setCurrentHealth(currentHealth);

	player.inv.clearInventory();
	DB::getInstance()->loadPlayerInventory(player);
	DB::getInstance()->loadPlayerEquipment(player);


	return true;
}

bool DB::createPlayerInventoryInstance(Player &player) {
	try
	{
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();
		//set starter items here
		cur->set_sql("INSERT INTO Inventory(playerID, slot1) VALUES(?, ?);");
		cur->prepare();
		cur->bind(1, player.getID());
		cur->bind(2, 8); //health potion id = 8;


		cur->step();

	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}

}

bool DB::createPlayerEquipmentInstance(Player &player) {
	try
	{
		sqlite::sqlite db("DB.db");
		auto cur = db.get_statement();
		//set starting equipment here, player starts with sword and shield...
		cur->set_sql("INSERT INTO Equipment(playerID, mainWeapon, sideWeapon) VALUES(?, ?, ?);");
		cur->prepare();
		cur->bind(1, player.getID());
		cur->bind(2, 1); // main sword id = 1;
		cur->bind(3, 2); // shield id = 2;


		cur->step();

	}
	catch (sqlite::exception &e)
	{
		std::cerr << e.what() << endl;
		return false;
	}
}

bool DB::createPlayer(Player &player, std::string username, std::string password, std::string name) {
	//need to change db so intead of equipmentID and inventoryID the tables store the playerID;

	int Level = player.getLVL();
	int XP = player.getXP();
	int STR = player.getSTR();
	int ATT = player.getATT();
	int LCK = player.getLCK();
	int Gold = player.getGP();
	int maxHealth = player.getMaxHealth();
	int currentHealth = player.getCurrentHealth();
	int ID = player.getID();

	try {
		sqlite::sqlite db("DB.db");

		auto cur = db.get_statement();

		//cur->set_sql( "INSERT OR REPLACE INTO Player(ID, Name, Username, Password, Level, XP, STR, ATT, LCK, Gold, maxHealth, currentHealth ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);" );
		//cur->set_sql("UPDATE Player SET player_id = ?, player_name = ?, player_username = ?, player_password = ?, player_level = ?, player_xp = ?, player_str = ?, player_att = ?, player_lck = ?, player_gold = ?, player_maxHealth = ?, player_currentHealth = ? WHERE ID = ?;");
		cur->set_sql("INSERT INTO Player (player_id, player_name, player_username, player_password, player_level, player_xp, player_str, player_att, player_lck, player_gold, player_maxHealth, player_currentHealth) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
		cur->prepare();
		cur->bind(1, ID);
		cur->bind(2, name);
		cur->bind(3, username);
		cur->bind(4, password);
		cur->bind(5, Level);
		cur->bind(6, XP);
		cur->bind(7, STR);
		cur->bind(8, ATT);
		cur->bind(9, LCK);
		cur->bind(10, Gold);
		cur->bind(11, maxHealth);
		cur->bind(12, currentHealth);
		cur->step();
	}

	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	player.setUsername(username);
	player.setPassword(password);

	//creat an instance in the equipment and inventory tables for this user.
	DB::getInstance()->createPlayerInventoryInstance(player);
	DB::getInstance()->createPlayerEquipmentInstance(player);

    DB::getInstance()->loadPlayerEquipment(player);
    DB::getInstance()->loadPlayerInventory(player);
    
	return true;

}

bool DB::savePlayerData(Player &player, std::string username, std::string password) {

	int Level = player.getLVL();
	int XP = player.getXP();
	int STR = player.getSTR();
	int ATT = player.getATT();
	int LCK = player.getLCK();
	int Gold = player.getGP();
	int maxHealth = player.getMaxHealth();
	int currentHealth = player.getCurrentHealth();
	int ID = player.getID();
	std::string name = player.getName();
	std::string pWord = player.getPassword();
	std::string uName = player.getUsername();

	try {
		sqlite::sqlite db("DB.db");

		auto cur = db.get_statement();
		cur->set_sql("UPDATE Player SET player_id = ?, player_name = ?, player_username = ?, player_password = ?, player_level = ?, player_xp = ?, player_str = ?, player_att = ?, player_lck = ?, player_gold = ?, player_maxHealth = ?, player_currentHealth = ? WHERE player_id = ?");
		cur->prepare();
		cur->bind(1, ID);
		cur->bind(2, name);
		cur->bind(3, uName);
		cur->bind(4, pWord);
		cur->bind(5, Level);
		cur->bind(6, XP);
		cur->bind(7, STR);
		cur->bind(8, ATT);
		cur->bind(9, LCK);
		cur->bind(10, Gold);
		cur->bind(11, maxHealth);
		cur->bind(12, currentHealth);
		cur->bind(13, ID);
		cur->step();



	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	DB::getInstance()->savePlayerInventory(player);
	DB::getInstance()->savePlayerEquipment(player);

}

std::vector<entry> DB::getLeaderboardData(){ // Dominic Egginton
	// getLeaderboardData takes no peramiters and returns a vector of type entry.
	// The method will pull player name, level, xp and gold for the top 10 plays and put 
	// each player into a entry and store all entryies in a vector that it will return.
	std::vector<entry> returnData; // define the return vector of type entry
	try{
		sqlite::sqlite db("DB.db"); // connect to the DB
		auto cur = db.get_statement();
		cur->set_sql("SELECT player_username, player_level, player_xp, player_gold FROM Player ORDER BY player_level DESC LIMIT 10"); // SQL query 
		cur->prepare();
		while (cur->step()) { // loop over each record
			entry tempEntry = entry(cur->get_text(0), cur->get_int(1), cur->get_int(2), cur->get_int(3)); // create new instance of entry and pass the records data into it
			returnData.push_back(tempEntry); // important to add the entry to the vector at the end as it will be in order
		}
	}
	catch (sqlite::exception e){ // catch all sqlite errors
		std::cerr << e.what() << std::endl;
	}
	return returnData;
}

DB::DB()
{

}
