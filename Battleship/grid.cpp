#include "Grid.h"

namespace Battleship {
	void Grid::PlayerBounds() {
		clamp(&cursorPosition.x, 0, size.x - 1);
		clamp(&cursorPosition.y, 0, size.y - 1);
	}

	void Grid::PlayerBounds(const Boat* boatType, bool* vertical, bool holdingBoat) {
		clamp(&cursorPosition.x, 0, size.x - (holdingBoat ? *vertical ? boatType->get_Length() : 1 : 1));
		clamp(&cursorPosition.y, 0, size.y - (holdingBoat ? *vertical ? 1 : boatType->get_Length() : 1));
	}

	void Grid::InsertBoat(const Boat* p_boatType, bool* p_vertical) {
		for (int i{ 0 }; i < p_boatType->get_Length(); i++) {
			m_xy[size_t(cursorPosition.x + (*p_vertical ? i : 0))][size_t(cursorPosition.y + (*p_vertical ? 0 : i))] = p_boatType->get_Icon();
		}
	}

	void Grid::CreateGrids(int width, int height) {
		std::vector<std::string> _currentList;

		m_xy.clear();

		size.y = height;
		size.x = width;

		for (int y{ 0 }; y < size.y; y++) {
			_currentList.push_back(" ");
		}

		for (int x{ 0 }; x < size.x; x++) {
			m_xy.push_back(_currentList);
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
		}
		else {
			_gridPos = "x";
		}

		return _gridPos;
	}

	std::vector<std::vector<std::string>>* Grid::get_gridChars() {
		return &m_xy;
	}

	void Player::CreateGrids(int width, int height) {
		std::vector<std::string> _currentList;

		m_xy.clear();
		m_enemyGrid.clear();

		size.y = height;
		size.x = width;

		for (int y{ 0 }; y < size.y; y++) {
			_currentList.push_back(" ");
		}

		for (int x{ 0 }; x < size.x; x++) {
			m_xy.push_back(_currentList);
			m_enemyGrid.push_back(_currentList);
		}
	}

	void Player::ClearGrid() {
		for (unsigned short x{ 0 }; x < size.x; x++) {
			for (unsigned short y{ 0 }; y < size.y; y++) {
				m_xy[x][y] = m_enemyGrid[x][y] = " ";
			}
		}
	}

	void Player::wDrawGrid(short posX, short posY, std::vector<std::vector<std::string>> gridContent, const Vector2* currentPos) const {
		std::cout << CYAN;

		for (int x{ 0 }; x < size.x; x++) {
			gotoxy(posX + 4 + short(x) * 2, posY);
			std::cout << x;
		}

		gotoxy(posX + 2, posY + 1);
		std::cout << "┏";

		for (unsigned short x{ 0 }; x < size.x; x++) {
			std::cout << "━━";
		}

		for (unsigned short y{ 0 }; y < size.y; y++) {
			char _char = char(65 + y);

			gotoxy(posX, posY + y + 2);
			std::cout << _char << " ┃";
		}

		std::cout << WHITE;

		for (unsigned short y{ 0 }; y < size.y; y++) {
			gotoxy(posX + 3, posY + short(y) + 2);

			for (unsigned short x{ 0 }; x < size.x; x++) {
				if (gridContent[x][y] == "≈") {
					std::cout << BLUE;
				}
				else if (gridContent[x][y] == "x") {
					std::cout << RED;
				}

				if (currentPos) {
					if (currentPos->x == x && currentPos->y == y) {
						std::cout << " +" << WHITE;

						continue;
					}
				}

				std::cout << ' ' << gridContent[x][y] << WHITE;
			}
		}
	}

	bool Player::DrawGrid(const Boat* p_boat, bool* p_vertical) const {
		bool _retVal{ true };
		int _count{ 0 };

		std::cout << CYAN;

		for (int x{ 0 }; x < size.x; x++) {
			gotoxy(4 + short(x) * 2, 0);
			std::cout << x;
		}

		std::cout << "\n  ┏";

		for (unsigned short x{ 0 }; x < size.x; x++) {
			std::cout << (cursorPosition.x == x ? "━┷" : "━━");
		}

		for (unsigned short y{ 0 }; y < size.y; y++) {
			char _char = char(65 + y);

			std::cout << '\n' << _char << (cursorPosition.y == y ? "╶┨" : " ┃");
		}

		std::cout << WHITE;

		for (unsigned short y{ 0 }; y < size.y; y++) {
			gotoxy(3, short(y) + 2);

			for (unsigned short x{ 0 }; x < size.x; x++) {
				// print the player (As a "layer" on top of the grid)
				if (cursorPosition.x == x && cursorPosition.y == y) {
					if (p_boat->amount <= 0) {
						std::cout << " +";
					}
					else {
						if (m_xy[x][y] != " ") {
							std::cout << RED << " X" << WHITE;
							_retVal = false;
						}
						else {
							std::cout << ' ' << p_boat->get_Icon();
						}
						_count++;
					}
				}
				else if (cursorPosition.y == y && _count > 0 && _count < p_boat->get_Length() && *p_vertical) {
					if (m_xy[x][y] != " ") {
						std::cout << RED << " X" << WHITE;
						_retVal = false;
					}
					else {
						std::cout << ' ' << p_boat->get_Icon();
					}
					_count++;
				}
				else if (cursorPosition.x == x && _count > 0 && _count < p_boat->get_Length() && !*p_vertical) {
					if (m_xy[x][y] != " ") {
						std::cout << RED << " X" << WHITE;
						_retVal = false;
					}
					else {
						std::cout << ' ' << p_boat->get_Icon();
					}
					_count++;
				}
				else {
					std::cout << ' ' << m_xy[x][y];
				}
			}
		}

		return _retVal;
	}

	void AI::RandomGuess(int clampedX, int clampedY) {
		cursorPosition.x = rand() % clampedX;
		cursorPosition.y = rand() % clampedY;
	}

	bool AI::InsertBoat(const Boat* p_boatType, bool* p_vertical) {
		for (int i{ 0 }; i < p_boatType->get_Length(); i++) {
			if (m_xy[size_t(cursorPosition.x + (*p_vertical ? i : 0))][size_t(cursorPosition.y + (*p_vertical ? 0 : i))] != " ") {
				return true;
			}
		}

		for (int i{ 0 }; i < p_boatType->get_Length(); i++) {
			m_xy[size_t(cursorPosition.x + (*p_vertical ? i : 0))][size_t(cursorPosition.y + (*p_vertical ? 0 : i))] = p_boatType->get_Icon();
		}

		return false;
	}
}