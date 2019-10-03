#pragma once

#include "grid.h"

class BattleShip {
public:
    BattleShip() {
        std::cout << WHITE;
        ClearScreen();

        // pre create the boat assets
        m_boatTypes[0].CreateNewBoat(5, "■", 1);
        m_boatTypes[1].CreateNewBoat(4, "□", 2);
        m_boatTypes[2].CreateNewBoat(3, "▪", 3);
        m_boatTypes[3].CreateNewBoat(2, "▫", 2);

        m_placePosition.Zero();
    }

    void Tutorial(short p_offset);
    void ResetGrid();
    void DrawBoatStack(const Boat* boat, const int* index);
    void PlaceBoats();

private:
    Grid m_players[2];
    Boat m_boatTypes[4];

    Vector2 m_placePosition;

    int m_boatTypeIndex{ 0 }, m_boatAmountLeft{ 0 };
    bool m_isVertical{ false }, m_canPlace{ true }, m_endPlacement{ false };
};
