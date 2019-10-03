#include "grid.h"

void Grid::PlayerBounds(Vector2* position, const Boat* boatType, bool* vertical, bool holdingBoat) {
    clamp(&position->x, 0, size.x - (holdingBoat ? *vertical ? boatType->get_Length() : 1 : 1));
    clamp(&position->y, 0, size.y - (holdingBoat ? *vertical ? 1 : boatType->get_Length() : 1));
}

void Grid::InsertBoat(Vector2* position, const Boat* boatType, bool* vertical) {
    for (int i{ 0 }; i < boatType->get_Length(); i++) {
        m_xy[size_t(position->x + (*vertical ? i : 0))][size_t(position->y + (*vertical ? 0 : i))] = boatType->get_Icon();
    }
}

void Grid::CreateGrids() {
    std::vector<std::string> _currentList;

    m_xy.clear();
    m_enemyGrid.clear();

    for (int y{ 0 }; y < size.y; y++) {
        _currentList.push_back(" ");
    }

    for (int x{ 0 }; x < size.x; x++) {
        m_xy.push_back(_currentList);
        m_enemyGrid.push_back(_currentList);
    }
}

void Grid::ClearGrid() {
    for (unsigned short x{ 0 }; x < size.x; x++) {
        for (unsigned short y{ 0 }; y < size.y; y++) {
            m_xy[x][y] = " ";
        }
    }
}

std::string Grid::ReceveAttack(Vector2* p_pos) {
    std::string _gridPos = m_xy[size_t(p_pos->x)][size_t(p_pos->y)];

    if (_gridPos == " ") {
        _gridPos = "≈";
        return "≈";
    }
    else {
        _gridPos = "x";
        return "x";
    }
}

void Grid::DrawGridInGame(int x, int y) const {

}

bool Grid::DrawGrid(const Vector2* p_currentPos, const Boat* p_boat, bool* p_vertical) const {
    bool _retVal{ true };
    int _count{ 0 };

    printf("   %s", CYAN);

    for (unsigned short y{ 0 }; y < size.y; y++) {
        printf(" %i", y);
    }

    printf("\n  ┏");

    for (unsigned short x{ 0 }; x < size.x; x++) {
        std::cout << (p_currentPos->x == x ? "━┷" : "━━");
    }

    for (unsigned short y{ 0 }; y < size.y; y++) {
        char _char = char(65 + y);

        std::cout << '\n' << _char << (p_currentPos->y == y ? "╶┨" : " ┃");
    }

    std::cout << MAGENTA;

    for (unsigned short y{ 0 }; y < size.y; y++) {
        gotoxy(3, short(y) + 2);

        for (unsigned short x{ 0 }; x < size.x; x++) {
            // print the player (As a "layer" on top of the grid)
            if (p_currentPos->x == x && p_currentPos->y == y) {
                if (p_boat->amount <= 0) {
                    printf(" +");
                }
                else {
                    if (m_xy[x][y] != " ") {
                        std::cout << RED << " X" << MAGENTA;
                        _retVal = false;
                    }
                    else {
                        std::cout << ' ' << p_boat->get_Icon();
                    }
                    _count++;
                }
            }
            else if (p_currentPos->y == y && _count > 0 && _count < p_boat->get_Length() && *p_vertical) {
                if (m_xy[x][y] != " ") {
                    std::cout << RED << " X" << MAGENTA;
                    _retVal = false;
                }
                else {
                    std::cout << ' ' << p_boat->get_Icon();
                }
                _count++;
            }
            else if (p_currentPos->x == x && _count > 0 && _count < p_boat->get_Length() && !*p_vertical) {
                if (m_xy[x][y] != " ") {
                    std::cout << RED << " X" << MAGENTA;
                    _retVal = false;
                }
                else {
                    std::cout << ' ' << p_boat->get_Icon();
                }
                _count++;
            }
            else {
                std::cout << " " << m_xy[x][y];
            }
        }
    }

    return _retVal;
}
