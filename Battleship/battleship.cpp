#pragma once

#include "Battleship.h"

namespace Battleship {
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
		m_boatTypes[0].Reset();
		m_boatTypes[1].Reset();
		m_boatTypes[2].Reset();
		m_boatTypes[3].Reset();

		m_isVertical = false;
		m_boatTypeIndex = 0;
	}

	void BattleShip::DrawBoatStack(const Boat* p_boat, const int* p_index) {
		std::cout << "\n\n";

		for (int i{ 0 }; i < 4; i++) {
			std::cout << (p_boat[i].amount <= 0 ? RED : GREEN);

			std::cout << " " << p_boat[i].amount << " -";

			for (int h{ 0 }; h < p_boat[i].get_Length(); h++) {
				std::cout << ' ' << p_boat[i].get_Icon();
			}

			if (*p_index == i) {
				printf("\t←");
			}
			else {
				printf("\t ");
			}

			std::cout << '\n';
		}

		std::cout << WHITE;
	}

	void BattleShip::PlaceBoats() {
		Tutorial(26);

		player.CreateGrids(10, 10);
		enemy.CreateGrids(10, 10);

		do {
			player.PlayerBounds(&m_boatTypes[m_boatTypeIndex], &m_isVertical, m_boatTypes[m_boatTypeIndex].amount > 0);
			m_canPlace = player.DrawGrid(&m_boatTypes[m_boatTypeIndex], &m_isVertical);

			DrawBoatStack(m_boatTypes, &m_boatTypeIndex);

			// prbably need something similar for the AI when placing down boats
			m_boatAmountLeft = 0;
			for (int i{ 0 }; i < m_boatTypesLength; i++) {
				m_boatAmountLeft += m_boatTypes[i].amount;
			}

			if (m_boatAmountLeft <= 0) {
				std::cout << LIGHT_YELLOW << "\nPress y to start the game!" << WHITE;
			}

			switch (_getch()) {
			case 'a':
				// move left
				player.cursorPosition.x--;
				break;
			case 'd':
				// move right
				player.cursorPosition.x++;
				break;
			case 'w':
				//move up
				player.cursorPosition.y--;
				break;
			case 's':
				// move down
				player.cursorPosition.y++;
				break;
			case 'r':
				// rotate
				m_isVertical = !m_isVertical;
				break;
			case 'W':
				// change boatType UP
				m_boatTypeIndex--;
				_min(&m_boatTypeIndex, 0);
				break;
			case 'S':
				// change boatType DOWN
				m_boatTypeIndex++;
				_max(&m_boatTypeIndex, m_boatTypesLength - 1);
				break;
			case 'R':
				// reset the entire grid
				player.ClearGrid();
				ResetGrid();
				break;
			case ' ':
				// place down the boat
				if (m_boatTypes[m_boatTypeIndex].amount > 0 && m_canPlace) {
					player.InsertBoat(&m_boatTypes[m_boatTypeIndex], &m_isVertical);
					m_boatTypes[m_boatTypeIndex].amount--;
				}
				break;
			case 'y':
				// finish up this boat placement session
				if (m_boatAmountLeft <= 0) {
					m_endPlacement = true;
				}
				break;
			}

			//ClearScreen();
		} while (!m_endPlacement);

		ClearScreen();
		std::cout << "Enemy placing down their boats";

		ResetGrid();

		while (m_boatTypeIndex < m_boatTypesLength) {
			int _maxX{ 0 }, _maxY{ 0 };

			m_isVertical = rand() % 2;

			_maxX = int(enemy.m_xy.size() - (m_isVertical ? m_boatTypes[m_boatTypeIndex].get_Length() : 1));
			_maxY = int(enemy.m_xy[0].size() - (m_isVertical ? 1 : m_boatTypes[m_boatTypeIndex].get_Length()));

			enemy.RandomGuess(_maxX, _maxY);

			if (enemy.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y)] != " ") {
				continue;
			}

			if (enemy.InsertBoat(&m_boatTypes[m_boatTypeIndex], &m_isVertical)) {
				continue;
			}

			m_boatTypes[m_boatTypeIndex].amount--;

			if (m_boatTypes[m_boatTypeIndex].amount <= 0) {
				m_boatTypeIndex++;
			}

			std::cout << '.';
			Sleep(rand() % 240);
		}

		ClearScreen();
	}

	void BattleShip::InGame() {
		bool _endGame{ false }, _isPlayerTurn{ true }; //_hit{ false }, _checkedAbove{ false }, _checkedBelow{ false }, _checkedLeft{ false }, _checkedRight{ false }, _guessVertical{ false }, _guessHorizontal{ false };
		GUIText waveText, xText, winnerText;

		player.cursorPosition.Zero();

		player.name.position.x = 8;
		player.name.position.y = 3;

		enemy.name.position.x = 44;
		enemy.name.position.y = 3;

		waveText.text = "≈ = Miss";
		xText.text = "x = Hit";

		waveText.position.x = 7;
		waveText.position.y = 18;

		xText.position.x = 7;
		xText.position.y = 19;

		winnerText.position.x = 35;
		winnerText.position.y = 1;

		waveText.DrawTextW(BLUE);
		xText.DrawTextW(RED);

		// get the grids from the player, draw them and ask the player for input coords
		do {
			player.wDrawGrid(42, 5, player.m_xy);
			player.wDrawGrid(6, 5, player.m_enemyGrid, &player.cursorPosition);

			if (_isPlayerTurn) {
				//std::cout << player.get_gridChars() << '\n';
				player.PlayerBounds();

				enemy.name.DrawTextW(LIGHT_YELLOW);
				player.name.DrawTextW(YELLOW_REVERSED);

				switch (_getch()) {
				case 'a':
					// move left
					player.cursorPosition.x--;
					break;
				case 'd':
					// move right
					player.cursorPosition.x++;
					break;
				case 'w':
					// move up
					player.cursorPosition.y--;
					break;
				case 's':
					// move down
					player.cursorPosition.y++;
					break;
				case ' ':
					// if the guessed position is not already guessed, then we start the loop all over again.
					if (player.m_enemyGrid[size_t(player.cursorPosition.x)][size_t(player.cursorPosition.y)] != " ") {
						continue;
					}

					player.m_enemyGrid[size_t(player.cursorPosition.x)][size_t(player.cursorPosition.y)] = enemy.ReceveAttack(&player.cursorPosition);

					if (player.m_enemyGrid[size_t(player.cursorPosition.x)][size_t(player.cursorPosition.y)] == "≈") {
						_isPlayerTurn = !_isPlayerTurn;
					}
					else {
						player.tilesSunk++;
						_endGame = player.tilesSunk >= winScore;
					}
					break;
				}
			}
			else {
				enemy.name.DrawTextW(YELLOW_REVERSED);
				player.name.DrawTextW(LIGHT_YELLOW);

				enemy.RandomGuess(int(enemy.m_xy.size()), int(enemy.m_xy[0].size()));

				// if the AI hit a boat then guess the adjecent cells
				/*if (_hit)
				{
					bool _retVal{ true };
					int _guessOffset{ 1 };

					do
					{
						// check for possible options
						_checkedAbove = player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y - 1)] != "≈" ||
							player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y - 1)] != "x";
						_checkedBelow = player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y + 1)] != "≈" ||
							player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y + 1)] != "x";
						_checkedLeft = player.m_xy[size_t(enemy.cursorPosition.x - 1)][size_t(enemy.cursorPosition.y)] != "≈" ||
							player.m_xy[size_t(enemy.cursorPosition.x - 1)][size_t(enemy.cursorPosition.y)] != "x";
						_checkedRight = player.m_xy[size_t(enemy.cursorPosition.x + 1)][size_t(enemy.cursorPosition.y)] != "≈" ||
							player.m_xy[size_t(enemy.cursorPosition.x + 1)][size_t(enemy.cursorPosition.y)] != "x";

						int _randVal = rand() % 4;
						
						if (_guessHorizontal || _guessVertical)
						{

						}

						if (_checkedAbove && _randVal == 0)
						{
							_guessOffset--;
							_guessVertical = true;
							_checkedAbove = true;
							_retVal = false;
						}
						else if (_checkedBelow && _randVal == 1)
						{
							_guessOffset++;
							_guessVertical = true;
							_checkedBelow = true;
							_retVal = false;
						}
						else if (_checkedLeft && _randVal == 2)
						{
							_guessOffset--;
							_guessHorizontal = true;
							_checkedLeft = true;
							_retVal = false;
						}
						else if (_checkedRight && _randVal == 3)
						{
							_guessOffset++;
							_guessHorizontal = true;
							_checkedRight = true;
							_retVal = false;
						}
					} while (_retVal);
				}
				else
				{
					enemy.RandomGuess(int(enemy.m_xy.size()), int(enemy.m_xy[0].size()));
				}*/
				
				// if the guessed position is not already guessed, then we start the loop all over again.
				if (player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y)] == "≈" ||
					player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y)] == "x") {
					continue;
				}

				player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y)] = player.ReceveAttack(&enemy.cursorPosition);

				// if we did not hit a boat then change the turn to the player, otherwise add one to the sunken tiles variable
				if (player.m_xy[size_t(enemy.cursorPosition.x)][size_t(enemy.cursorPosition.y)] == "≈") {
					_isPlayerTurn = !_isPlayerTurn;
				}
				else {
					//_hit = true;
					enemy.tilesSunk++;
					_endGame = enemy.tilesSunk >= winScore;
				}

				// sleep, for simulating "thinking"
				//Sleep(rand() % 1000 + 500);
			}
		} while (!_endGame);

		player.wDrawGrid(42, 5, player.m_xy);
		player.wDrawGrid(6, 5, player.m_enemyGrid);

		if (player.tilesSunk >= winScore)
		{
			winnerText.text = "  - Player Wins -  ";
		}
		else
		{
			winnerText.text = "  - Computer Wins -  ";
		}

		winnerText.DrawTextW(YELLOW_REVERSED);
	}

	const int BattleShip::get_BoatAmount() {
		int _retValue{ 0 };

		for (int i{ 0 }; i < m_boatTypesLength; i++) {
			_retValue += m_boatTypes[i].get_Length() * m_boatTypes[i].get_StoreAmount();
		}

		return _retValue;
	}
}