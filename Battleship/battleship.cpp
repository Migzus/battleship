#include "battleship.h"

void BattleShip::Tutorial(short p_offset) {
    gotoxy(p_offset, 0);
    printf("How to Move");
    gotoxy(p_offset, 1);
    printf("‾‾‾‾‾‾‾‾‾‾‾");
    gotoxy(p_offset + 4, 2);
    printf("W");
    gotoxy(p_offset + 2, 3);
    printf("A S D");
    gotoxy(p_offset, 5);
    printf("Rotate  → r");
    gotoxy(p_offset, 6);
    printf("Switch  → SHIFT + a / d");
    gotoxy(p_offset, 7);
    printf("Place   → SPACE");
    gotoxy(p_offset, 8);
    printf("Restart → SHIFT + r");
}

void BattleShip::ResetGrid() {
    m_players[0].ClearGrid();

    m_boatTypes[0].Reset();
    m_boatTypes[1].Reset();
    m_boatTypes[2].Reset();
    m_boatTypes[3].Reset();

    m_placePosition.Zero();
    m_isVertical = false;
    m_boatTypeIndex = 0;
}

void BattleShip::DrawBoatStack(const Boat* boat, const int* index) {
    std::cout << "\n\n";

    for (int i{ 0 }; i < 4; i++) {
        std::cout << (boat[i].amount <= 0 ? RED : GREEN);

        std::cout << " " << boat[i].amount << " -";

        for (int h{ 0 }; h < boat[i].get_Length(); h++) {
            std::cout << ' ' << boat[i].get_Icon();
        }

        if (*index == i) {
            printf("\t←");
        }

        std::cout << '\n';
    }

    std::cout << WHITE;
}

void BattleShip::PlaceBoats() {
    do {
        m_players[0].PlayerBounds(&m_placePosition, &m_boatTypes[m_boatTypeIndex], &m_isVertical, m_boatTypes[m_boatTypeIndex].amount > 0);
        std::cout << BLUE;
        m_canPlace = m_players[0].DrawGrid(&m_placePosition, &m_boatTypes[m_boatTypeIndex], &m_isVertical);

        DrawBoatStack(m_boatTypes, &m_boatTypeIndex);

        m_boatAmountLeft = 0;
        for (int i{ 0 }; i < 4; i++) {
            m_boatAmountLeft += m_boatTypes[i].amount;
        }

        if (m_boatAmountLeft <= 0) {
            std::cout << LIGHT_YELLOW << "\nPress y to start the game!" << WHITE;
        }

        Tutorial(26);

        switch (_getch()) {
        case 'a':
            // move left
            m_placePosition.x--;
            break;
        case 'd':
            // move right
            m_placePosition.x++;
            break;
        case 'w':
            //move up
            m_placePosition.y--;
            break;
        case 's':
            // move down
            m_placePosition.y++;
            break;
        case 'r':
            // rotate
            m_isVertical = !m_isVertical;
            break;
        case 'W':
            // change boatType UP
            m_boatTypeIndex--;
            min(&m_boatTypeIndex, 0);
            break;
        case 'S':
            // change boatType DOWN
            m_boatTypeIndex++;
            max(&m_boatTypeIndex, int(sizeof(m_boatTypes) / sizeof(Boat)) - 1);
            break;
        case 'R':
            // reset the entire grid
            ResetGrid();
            break;
        case ' ':
            // place down the boat
            if (m_boatTypes[m_boatTypeIndex].amount > 0 && m_canPlace) {
                m_players[0].InsertBoat(&m_placePosition, &m_boatTypes[m_boatTypeIndex], &m_isVertical);
                m_boatTypes[m_boatTypeIndex].amount--;
            }
            break;
        case 'y':
            // finish up this boat placement session
            if (m_boatAmountLeft <= 0) {
                m_endPlacement = true;
            }
            break;
        default:
            break;
        }

        ClearScreen();
    } while (!m_endPlacement);
}
