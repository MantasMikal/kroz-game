#include "Game.h"
#include <typeinfo>

//Dom
#include <vector>

//Jack
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h> // open group library - general terminal interface --> Jack - 14/03/2018 - 00:55 (password protecton)
#include <unistd.h> // give acccess to POSIX operating system API --> Jack - 14/03/2018 - 00:55
#endif

// for hahing and openssl
#include <sstream>
#include "openssl/sha.h"


//TODO

//from week 6 codio exercises -- lab_adaptive.cpp 
Game::Game()
{
	system("clear"); //clears the screen
	this->isRunning = true;
}


Game::~Game()
{

}

void Game::init()
{

}

int Game::mainMenu()
{

	//TODO:
	//
	int userInput;

	//condition ? result_if_true : result_if_false
	//if(x) y else z
	std::cout << "\n= MAIN MENU =\n";
	std::cout << "1. Explore\n";
	std::cout << "2. Character\n";
	std::cout << "3. Options\n";
    std::cout << "4. EXIT\n";
	userInput = input<int>(true);
	system("clear");
	this->showLogo();
	switch (userInput)
	{
	default:
		break;
	case 1:
		this->eventHandler.generateRandomEvent(player);
		break;
	case 2:
		this->displayCharacterOptions();
		break;
	case 3:
		this->displayOptions();
		break;
    case 4: 
        return 100; //Exits
        break;
	} //switch end;
	return false;
}

void Game::displayCharacterOptions()
{
	int userInput;

	std::cout << "\n= CHARACTER OPTIONS =\n";
	std::cout << "1. Display Stats\n";
	std::cout << "2. Display Items\n";
	std::cout << "3. Display Equipment\n";
	std::cout << "4. Level UP " << (player.isLevelUpAvailable() ? "(Available)\n" : "(Not available)\n");

	userInput = input<int>(true);
	this->showLogo();

	switch (userInput)
	{
	default:
		break;
	case 1:
		this->player.printStats();
		break;
	case 2:
		this->player.displayItems();
		break;
	case 3:
		this->player.displayEquipment();
		break;
	case 4:
		this->player.levelUp();
		break;
	} //switch end;
}

void Game::displayOptions()
{
	int userInput;

	std::cout << "\n= OPTIONS =\n";
	std::cout << "1. Save Game\n";
	std::cout << "2. Logout\n";

	userInput = input<int>();

	switch (userInput)
	{
	default:
		break;
	case 1:
		DB::getInstance()->savePlayerData(player, player.getUsername(), player.getPassword());
		system("clear");
		this->showLogo();
		break;
	case 2:
		this->setLoggedInStatus(false);
		DB::getInstance()->savePlayerData(player, player.getUsername(), player.getPassword()); //data also saved when you logout...
		system("clear");
		break;
	}
}

 //login hide password --> Jack 13/03/2018 
 //would just use getch, but care about portability
 //SetStdinEcho function disbales echo when false;
void SetStdinEcho(bool enable = true) // defualt set to true so echo can be turned back on 
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;
    SetConsoleMode(hStdin, mode );
#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

// hashing functions --> Jack 14/03/2018 
//convert sha256 to hex before output 
std::string to_hex(unsigned char s) 
{
    std::stringstream ss;
    ss << std::hex << (int) s;
    return ss.str();
}   

//slighty hard to read as didn't want to obscure code with return value checks
//to switch between different sha hashing, simply change values from SHA256 to:
//SHA224, SHA384, SHA512, SHA512/224, SHA512/256  or see return values --> https://www.openssl.org/docs/man1.0.2/crypto/sha.html

std::string sha256Hash(std::string line) 
{    
    unsigned char hash[SHA256_DIGEST_LENGTH];  
    SHA256_CTX sha256; 
    SHA256_Init(&sha256);  //initializes the SHA_CTX structure from previous line
    
    SHA256_Update(&sha256, line.c_str(), line.length());
    SHA256_Final(hash, &sha256); // places message digest in md

    //sending to hex function before output  
    std::string outputHash = "";    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) 
    {
        outputHash += to_hex(hash[i]);
    }
    return outputHash;
}
// end hashing funnction


// Login Screen 
bool Game::loginScreen() {
	if (!this->getLoggedInStatus()) {
		this->showLogo();
		std::cout << "===== A Bug Filled Gambling Adventure =====\n"; // --> Jack - 13/03/2018 - 22:16 (More Accurate Header) 
		std::cout << "1. LOGIN\n";
		std::cout << "2. Create Account\n";
		std::cout << "3. Leaderboard\n";
		std::cout << "4. Exit \n";

		int choice;

		choice = input<int>();

		std::string username;
		std::string password = "";
		std::string name;

		switch (choice) {
		default:
			break;
		case 1:
		{
			std::cout << "Enter username: "; std::cin >> username;
			std::cout << "\nEnter password: ";
			SetStdinEcho(false); //--> Jack
			std::cin >> password;
			SetStdinEcho(true);

            if (DB::getInstance()->validateLogin(username, password = sha256Hash(password+username))) // Jack 15/03/2018 Moved hash function inside sql statement + concatenated to username so rainbow tables won't work
            {
                this->setLoggedInStatus(true);
                DB::getInstance()->loadPlayerData(player, username, password);
                this->showLogo();
                std::cout << "Success!/n";
                return true;
                break;
            }
            else 
            {
                this->setLoggedInStatus(false);
                system("clear");
                return false;
                break;
            }
		}  

		case 2: {
			std::cout << "Name your character: ";
			std::cin >> name;
			std::cout << "\nEnter username: ";
			std::cin >> username;
			std::cout << "\nEnter password (between 6 and 20 characters): ";
			SetStdinEcho(false); //--> Jack
			std::cin >> password;
      
      while(password.length() < 6 || password.length() > 20)
      {
        std::cout << "Just follow the instructions you rebellious swine... \n";
        std::cout << "\nEnter password (between 6 characters 20): ";
        std::cin >> password;
      }
			SetStdinEcho(true);

      if (DB::getInstance()->createPlayer(player, username, password = sha256Hash(password+username), name))  // Jack 15/03/2018 Moved hash function inside sql statement + concatenated to username so rainbow tables won't work
      {
				//this->showLogo();
				std::cout << "\nAccount created successfully!\n";
				this->setLoggedInStatus(true);
				return true;
				break;
			}

		else {
				this->showLogo();
				std::cout << "\n Account creation was unsuccessful!\n";
				this->setLoggedInStatus(false);
				return false;
				break;
			}
		}
		
	case 3: 
		{
leaderboard: //this is a keyword that i can jump back to
			//clear the screen
			system("clear");
			//display the logo again
			this->showLogo();
			//Show the Title of the leaderboard
			std::cout << "\nPlayer Leaderboard\n\n";
			//get leaderboard data from database and display
			leaderboard tempLeaderboard = leaderboard(DB::getInstance()->getLeaderboardData()); // create new leaderboard object by passing the vector of type entry that is returnedd from getLeaderboardData
			if(!tempLeaderboard.displayLeaderboard()){ //display the leadbaord
				std::cout << "error displaying the leaderboard" << std::endl; // only if there is an error
			}
			// ask user if they want to exit leaderboard
			std::cout << "\nExit: 0: ";
			int userInput;
			std::cin >> userInput;
			if(userInput == 0){
				//clear the screen again and return
				this->showLogo();
				return false;
				break;
			}
			else{
				goto leaderboard; // jump to keyword
			}
		}
                
      case 4:
         this->isRunning = false;

		}

	}
	else {
		return true;
	}

}

void Game::setLoggedInStatus(bool val) {
	this->isLoggedIn = val;
}

bool Game::getLoggedInStatus() {
	return this->isLoggedIn;
}

void Game::showLogo() {
	std::cout << R"(
    ██ ▄█▀ ██▀███   ▒█████  ▒███████▒
    ██▄█▒ ▓██ ▒ ██▒▒██▒  ██▒▒ ▒ ▒ ▄▀░
    ▓███▄░ ▓██ ░▄█ ▒▒██░  ██▒░ ▒ ▄▀▒░ 
    ▓██ █▄ ▒██▀▀█▄  ▒██   ██░  ▄▀▒   ░
    ▒██▒ █▄░██▓ ▒██▒░ ████▓▒░▒███████▒
    ▒ ▒▒ ▓▒░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░▒▒ ▓░▒░▒
    ░ ░▒ ▒░  ░▒ ░ ▒░  ░ ▒ ▒░ ░░▒ ▒ ░ ▒
    ░ ░░ ░   ░░   ░ ░ ░ ░ ▒  ░ ░ ░ ░ ░
    ░  ░      ░         ░ ░    ░ ░    
                         ░            
  )" << endl << endl << endl; // --> Jack - 13/03/2018 - 22:36 (Updated ASCII Art) 
}
