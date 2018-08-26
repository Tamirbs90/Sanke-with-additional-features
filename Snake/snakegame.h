#pragma once
#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "Snake.h"
#include "taskmanager.h"
#include "board.h"
#include "shot.h"
#include "fly.h"


using namespace std;

enum KEYS { ESC = 27 };

class SnakesGame {

protected:
	
	std::vector<Snake> snakes = { { { 10, 9 }, 3, '@' },
	{ { 70, 9 }, 3, '#' },{ { 10, 9 }, 3, '@' },
	{ { 70, 9 }, 3, '#' }
	};

	std::vector<Shot> active_shots;
	std::vector<Shot> replayShots;
	std::vector<bool> isShooting;

	std::vector<Fly> lineFlies = {
		{ '!', 30, 23, Direction::RIGHT, true },
		{ '!', 50, 15, Direction::LEFT, false }
	};

	std::vector<Fly> replayLineFlies = {
		{ '!', 30, 23, Direction::RIGHT, true },
		{ '!', 50, 15, Direction::LEFT, false }
	};

	std::vector<Fly> columnFlies= {
		{ '$', 55, 15, Direction::DOWN, true },
		{ '$', 45, 23, Direction::UP, false }
	};

	std::vector<Fly> replayColumnFlies = {
		{ '$', 55, 15, Direction::DOWN, true },
		{ '$', 45, 23, Direction::UP, false }
	};


	Fly numEater = {'%', 10, 19 ,Direction::STAY, true };
	Fly numEaterReplay= { '%', 10, 19 ,Direction::STAY, true };
	std::vector<Direction> eaterDir;
	std::vector<Direction> eaterReplayDir;

	std::vector<Point> unhideSnake1;
	size_t unhide1=0;
	std::vector<Point> unhideSnake2;
	size_t unhide2=0;
	


	Board board;
	TaskManager task_manager;
	
	vector<Board> saveBoards;
	vector<Direction> direction1;
	vector<Direction> direction2;


	Snake * winner = NULL;
	bool force_changing_task = false;

	void moveSnake(size_t i, char keyPressed);

	void moveFly(Fly &fly, bool isReplay);

	bool willIntersect(Snake& current);

	bool intersectWithShot(Point &obj);
	bool intersectWithShot(Snake &snake);
	void addShot(Snake &snake, Point& pos, Direction dir);
	void moveShots();
	void moveEater(Fly& eater);
	bool solutionFound();

	void changeCurrentTask(Snake* winner);
	bool isTaskTimedOut();
	void onTaskFinidhed();

	void printInfo(Snake &snake, Point &pos, int currentNumber, size_t i);

public:
	SnakesGame() {
		snakes[0].setKeys('a', 'd', 'w', 'x');
		snakes[1].setKeys('j', 'l', 'i', ',');
	}

	void addDirection(Direction d1, Direction d2);
		
	void addBoard(Board _board);

	void setReplaySizes(size_t size1, size_t size2);

	void setReplaySnakesLocation();

	void reset();
	void fastWay();
	void run();
	void replay();
	void MainMenu();
	void secondaryMenu();
	void instructions();
};

#endif