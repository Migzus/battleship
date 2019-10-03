#include "gamemaster.h"

void gotoxy(short x, short y) {
    static HANDLE _h = nullptr;

    if (!_h) {
        _h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    COORD _c = { x, y };
    SetConsoleCursorPosition(_h, _c);
}

void ClearScreen() {
#ifdef _WIN32
    // Run this code, only on Windows
    std::system("cls");
#else
    // Otherwise I assume it is a Linux/UNIX based system
    std::system("clear");
#endif
}
