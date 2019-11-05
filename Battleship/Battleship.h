#pragma once

#include "Grid.h"

namespace Battleship {
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

			m_boatTypesLength = 4;

			winScore = get_BoatAmount();
		}

		void Tutorial(short);
		void ResetGrid();
		void DrawBoatStack(const Boat*, const int*);
		const int get_BoatAmount();

		// runtime functions
		void PlaceBoats();
		void InGame();

	private:
		Boat m_boatTypes[4];
		Player player;
		AI enemy;

		int m_boatTypeIndex{ 0 }, m_boatAmountLeft{ 0 }, m_boatTypesLength{ 0 }, winScore{ 0 };
		bool m_isVertical{ false }, m_canPlace{ true }, m_endPlacement{ false };
	};
}
