#pragma once

#include "GameMaster.h"

namespace Battleship {
	class Grid {
	public:
		int guessedHits{ 0 }, tilesSunk{ 0 };
		const int defaultGridSize{ 10 };
		Vector2 cursorPosition;
		std::vector<std::vector<std::string>> m_xy;
		GUIText name;

		Grid() {
			size.x = size.y = defaultGridSize;
		}

		void PlayerBounds();
		void PlayerBounds(const Boat*, bool*, bool);
		void InsertBoat(const Boat*, bool*);

		// these two methods are virtual due to m_enemyGrid in the Player class
		virtual void CreateGrids(int, int);
		virtual void ClearGrid();

		// send in the coordinates of the attacked cell, and send back if it was a hit or not
		std::string ReceveAttack(Vector2*);
		std::vector<std::vector<std::string>>* get_gridChars();

		virtual ~Grid() {
			// do stuff here when the extended class is deconstructded
		}

	protected:
		Vector2 size;
	private:
		const short m_maxHeight{ 25 }, m_maxWidth{ 25 };
	};

	class Player : public Grid {
	public:
		std::vector<std::vector<std::string>> m_enemyGrid;

		Player() : Grid() {
			size.x = size.y = defaultGridSize;
			name.text = " -Player- ";
		}

		void CreateGrids(int, int) override;
		void ClearGrid() override;

		// this is only for the player before the game starts, this has all the functionallity
		// for drawing the placement of the boats
		bool DrawGrid(const Boat*, bool*) const;
		void wDrawGrid(short, short, std::vector<std::vector<std::string>>, const Vector2* = nullptr) const;
	};

	class AI : public Grid {
	public:
		AI() : Grid() {
			size.x = size.y = defaultGridSize;
			name.text = " -Computer- ";
		}

		void RandomGuess(int, int);
		bool InsertBoat(const Boat*, bool*);
	};
}
