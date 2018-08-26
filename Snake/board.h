#pragma once
#ifndef _BAORD_H_
#define _BOARD_H_

#include "stdafx.h"
#include "point.h"
#include "snake.h"
#include "taskmanager.h"

class Board {

public:
	enum { rows = 19, cols = 80, padding_top = 5, padding_left = 0 };
private:
	
	char screen[rows][cols];
	int numbersCount = 0;
	int numberGroup = 0;

	std::unordered_map<int, std::vector<int>> numberToCell;
	std::vector<int> allNumbers;

	void _removeNumber(int num);

public:
	Board() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				screen[i][j] = ' ';
			}
		}

	}

	Point getRandomPoint();

	int getDigit(int x, int y);

	int getNumber(const Point& pos);

	void display();

	void addNumber(std::vector<Snake>& snakes, size_t snakes_count);

	int getNumbersCount() {
		return allNumbers.size();
	}

	void removeNumbers(size_t numsToRemove);
	void removeNumber(int num);

	void clearPosition(Point &pos);

	void clear();

	std::vector<int> findPositions(TaskManager);

};

#endif