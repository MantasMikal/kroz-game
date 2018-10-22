#include <iostream>
#include "Game.h"

#include <array>
int main() {

	///SETUP///
	Game game = Game();

	//WEAPONS ------------ Attack -- Strength -- Defence -- Luck -- WeaponType -- LvlReq -- Name -- Rarity -- Value
	//  ARMOR ------------ ArmorType -- lvlReq -- Defence -- Attack -- Strength -- Luck -- Name -- Rarity -- Value
	//CONSUME ------------ HealthBoost -- DamageBoost -- DefenceBoost -- Name -- Rarity -- Value

	//equiping items to the player
	//[-1] = empty
	//[0] = helmet
	//[1] = chestpiece
	//[2] = legs
	//[3] = leftArm
	//[4] = rightArm

	//GAMELOOP

	while (game.isRunning) {
		if (game.getLoggedInStatus()) {
			if (game.mainMenu() == 100) {
				return 0;
			}

		}else game.loginScreen();
		

	}


	return 0;
}