#pragma once

#include "gamemaster.h"

class Grid {
public:
    const int defaultGridSize{ 10 };
    Vector2 size;

    Grid() {
        size.x = size.y = defaultGridSize;
        CreateGrids();
    }

    void PlayerBounds(Vector2* position, const Boat* boatType, bool* vertical, bool holdingBoat);
    void InsertBoat(Vector2* position, const Boat* boatType, bool* vertical);

    void CreateGrids();
    // reset the entire grid. Called when player wants a rematch or is not happy with their boat placement
    void ClearGrid();

    // send in the coordinates of the attacked cell, and send back if it was a hit or not
    std::string ReceveAttack(Vector2* p_pos);

    // this function is only for the player "ingame" function call
    void DrawGridInGame(int x, int y) const;

    // this is only for the player before the game starts, this has all the functionallity
    // for drawing the placement of the boats
    bool DrawGrid(const Vector2* p_currentPos, const Boat* p_boat, bool* p_vertical) const;
private:
    //short m_maxHeight{ 25 }, m_maxWidth{ 25 };
    std::vector<std::vector<std::string>> m_xy;
    std::vector<std::vector<std::string>> m_enemyGrid;
};
