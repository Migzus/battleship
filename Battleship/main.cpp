#include "battleship.h"

using namespace Battleship;

int main()
{
	bool yes{ true };

	srand(static_cast<unsigned int>(time(nullptr)));
	HideCursor();

	do {
		BattleShip* game = new BattleShip;

		ClearScreen();

		game->PlaceBoats();
		game->InGame();
		
		// wait 3 seconds
		Sleep(3000);

		//ClearScreen();

		gotoxy(5, 22);
		std::cout << WHITE << "\nPress " << MAGENTA << 'y' << WHITE << " to play again to play again. Otherwise, the application " << RED << "quits" << WHITE << ".\n";

		switch (_getch()) {
		case 'y':
		case 'Y':
			delete game;
			yes = true;
			break;
		default:
			yes = false;
			break;
		}
	} while (yes);

	return 0;
}
