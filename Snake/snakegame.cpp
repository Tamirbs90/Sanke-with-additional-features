#include "stdafx.h"
#include "snakeGame.h"
#include "Direction.h"
#include "taskmanager.h"
#include "shot.h"
#include "fly.h"

bool SnakesGame::willIntersect(Snake& current) {

	for (size_t i = 0; i < snakes.size(); i++) {
		const Point next = current.nextPoint();
		if (snakes[i].intersect(next)) {
			return true;
		}
	}
	return false;
}


void SnakesGame::moveShots() {
	std::vector<Shot> shots_to_remove = {};
	std::vector<Fly> lineFliesToRemove = {};
	std::vector<Fly> colFliesToRemove = {};

	for (size_t i = 0; i < active_shots.size(); i++) {
		active_shots[i].move();
		int num = board.getNumber(active_shots[i]);
		if (num > 0) {
			board.removeNumber(num);
			shots_to_remove.push_back(active_shots[i]);
		}

		for (size_t k = 0; k < snakes.size(); k++) {
			if (snakes[k].intersect(active_shots[i])) {
				shots_to_remove.push_back(active_shots[i]);
				snakes[k].hide();
				snakes[k == 0 ? 1 : 0].increaseShotsCount();
			}
		}

		for (size_t k = 0; k < lineFlies.size(); k++) {
			if (active_shots[i].getX() == lineFlies[k].getX() &&
				active_shots[i].getY() == lineFlies[k].getY()) {
				shots_to_remove.push_back(active_shots[i]);
				lineFliesToRemove.push_back(lineFlies[k]);
			}
		}

		for (size_t k = 0; k < columnFlies.size(); k++) {
			if (active_shots[i].getX() == columnFlies[k].getX() &&
				active_shots[i].getY() == columnFlies[k].getY()) {
				shots_to_remove.push_back(active_shots[i]);
				colFliesToRemove.push_back(columnFlies[k]);
			}
		}

	}

	for (size_t i = 0; i < shots_to_remove.size(); i++) {
		active_shots.erase(std::remove(active_shots.begin(), active_shots.end(), shots_to_remove[i]),
			active_shots.end());
	}

	for (size_t i = 0; i < lineFliesToRemove.size(); i++) {
		lineFlies.erase(std::remove(lineFlies.begin(), lineFlies.end(), lineFliesToRemove[i]),
			lineFlies.end());
	}

	for (size_t i = 0; i < colFliesToRemove.size(); i++) {
		columnFlies.erase(std::remove(columnFlies.begin(), columnFlies.end(), lineFliesToRemove[i]),
			columnFlies.end());
	}
}

char getKey() {
	char keyPressed = 0;
	if (_kbhit()) {
		keyPressed = _getch();
		return keyPressed;
	}
	return 0;
}


void SnakesGame::onTaskFinidhed() {
	gotoxy(0, 1);
	cout << "Task finished unseecssfully";

	std::vector<int> positions = board.findPositions(task_manager);
	if (positions[0] == -1) {
		cout << " Number was not shown";
	}
	else {
		cout << " Number found at " << positions[0] << " , " << positions[1];
	}

	board.removeNumbers(30);

	task_manager.task_accomplished();
}

bool SnakesGame::isTaskTimedOut() {
	return board.getNumbersCount() >= 60;
}

void SnakesGame::changeCurrentTask(Snake* winner) {
	task_manager.task_accomplished();
	board.removeNumbers(board.getNumbersCount() / 2);
	board.display();
	if (winner != NULL) {
		cout << "Snake: " << winner->getChar() << " Won the task                          ";
		winner->increase(1);
	}
}

void SnakesGame::addShot(Snake &snake, Point& pos, Direction dir) {
	if (snake.hasShots()) {
		snake.decreaseShotsCount();
		Shot new_shot = { dir, pos.getX(), pos.getY() };
		active_shots.push_back(new_shot);
		replayShots.push_back(new_shot);
	}
	
}


void SnakesGame::printInfo(Snake &snake, Point &pos, int currentNumber, size_t i) {
	gotoxy(0, 2 + i);
	cout << snakes[i].getChar() << "size = " << snakes[i].getSize()
		<< " x = " << pos.getX() - Board::padding_left
		<< ", y = " << pos.getY() - Board::padding_top
		<< ", num = " << currentNumber << "                      ";
}

void SnakesGame::moveSnake(size_t i, char keyPressed) {
	
	if (snakes[i].isHidden()) {
		if (!snakes[i].shouldBeHidden()) {
			Point randomPoint = board.getRandomPoint();
			snakes[i].unhide(3, randomPoint);
			if (i == 0) {
				unhideSnake1.push_back(randomPoint);
			}
			if (i==1) {
				unhideSnake2.push_back(randomPoint);
			}
		}
		return;
	}

	// Move the snake one step
	Point pos = snakes[i].move(keyPressed);

	if ((keyPressed == 'z' && i == 0) || (keyPressed == 'n' && i == 1)) {
		addShot(snakes[i], pos, snakes[i].getDirection());
		isShooting.push_back(true);
	}
	else {
		isShooting.push_back(false);
	}
	

	// Checks if the snake collected a number and validate if tasks completed
	int num = board.getNumber(pos);

	printInfo(snakes[i], pos, num, i);

	if (num == -1) {
		return;
	}

	board.removeNumber(num);
	gotoxy(0, 1);
	bool test_result = task_manager.check(num);
	winner = test_result ? &snakes[i] : &snakes[i == 1 ? 0 : 1];
	if (test_result)
	{
		cout << "You are right                                    ";
	}
	else
	{
		cout << "Got the wrong Number " << num << "               ";
	}



	Sleep(3000);
	board.display();
	force_changing_task = true;
}

bool SnakesGame:: solutionFound() {
	
	vector<int> positions = board.findPositions(task_manager);
	if (positions[0] != -1)
		return true;
	return false;
}

void SnakesGame::moveEater(Fly &eater) {

	eater.move();

	board.clearPosition(eater);

	for (int i = 0; i < 2; i++) {
		if (snakes[i].intersect(eater)) {
			force_changing_task = true;
			board.clearPosition(eater);
			winner = &snakes[i == 0 ? 1 : 0];
			if (eater.getX() == 10 && eater.getY() == 19)
			{
				if (snakes[i].getDirection() == Direction::UP) {
					snakes[i].unhide(snakes[i].getSize(), (19 - snakes[i].getSize(), 10));
				}
				else if (snakes[i].getDirection() == Direction::DOWN) {
					snakes[i].unhide(snakes[i].getSize(), (19 + snakes[i].getSize(), 10));
				}
				else if (snakes[i].getDirection() == Direction::RIGHT) {
					snakes[i].unhide(snakes[i].getSize(), (19, 10 + snakes[i].getSize()));
				}
				else {
					snakes[i].unhide(snakes[i].getSize(), (19, 10 - snakes[i].getSize()));
				}
			}
		}
	}
}


void SnakesGame::fastWay() {

	int i;
	vector<int> positions = board.findPositions(task_manager);
	
	if (numEater.getX() > 20 && numEater.getX() < 60){
		for (int i = 0; i < abs(positions[0] - numEater.getX()); i++) {
			if (positions[0] > numEater.getX()) {
				eaterDir.push_back(Direction::RIGHT);
			}
			else {
				eaterDir.push_back(Direction::LEFT);
			}
		}
	}

	if (numEater.getX() < 20) {
		
		if (positions[0] > 20 && positions[0] < 60) {
			for (i = 0; i < positions[0] - numEater.getX(); i++) {
				eaterDir.push_back(Direction::RIGHT);
			}
		}

		if (positions[0] >= 60) {
			for (i = 0; i < 80 - numEater.getX() - positions[0]; i++) {
				eaterDir.push_back(Direction::LEFT);
			}
		}

		if (positions[0]<20 && numEater.getX()>positions[0]){
			for (i = 0; i < numEater.getX() - positions[0]; i++) {
				eaterDir.push_back(Direction::LEFT);
			}
		}

		if (positions[0]<20 && positions[0] > numEater.getX()) {
			for (i = 0; i <positions[0]-numEater.getX(); i++) {
				eaterDir.push_back(Direction::RIGHT);
			}
		}
	}
	
	if (numEater.getX()> 60) {

		if (positions[0] <= 20) {
			for (i = 0; i < (80 - numEater.getX() - positions[0]); i++) {
				eaterDir.push_back(Direction::RIGHT);
			}
		}
		if ((positions[0] > 20 && positions[0] <= 60) || (positions[0] > 60 && numEater.getX() > positions[0])) {
			for (i = 0; i < numEater.getX() - positions[0]; i++) {
				eaterDir.push_back(Direction::LEFT);
			}
		}

		if (positions[0] > 60 && positions[0] > numEater.getX()) {
			for (i = 0; i < positions[0] - numEater.getX(); i++) {
				eaterDir.push_back(Direction::RIGHT);
			}
		}
	}
	
	if (positions[1] < numEater.getY()) {
		for (i = 0; i < numEater.getY() - positions[1]; i++) {
			eaterDir.push_back(Direction::DOWN);
		}
	}
	if (positions[1]>numEater.getY()) {
		for (i = 0; i < positions[1] - numEater.getY(); i++) {
			eaterDir.push_back(Direction::UP);
		}
	}

}

void SnakesGame::moveFly(Fly &fly, bool isReplay) {

	fly.move();

	board.clearPosition(fly);

	if (!isReplay) {
		for (size_t i = 0; i < snakes.size(); i++) {
			if (snakes[i].intersect(fly)) {
				snakes[i].hide();
			}
		}
	}
	else {
		for (size_t i = 2; i < 4; i++) {
			if (snakes[i].intersect(fly)) {
				if (i == 2) {
					snakes[2].unhide(3, unhideSnake1[unhide1]);
					unhide1++;
					if (unhide1 == unhideSnake1.size()) {
						unhide1 = 0;
					}
				}
				else {
					snakes[3].unhide(3, unhideSnake2[unhide2]);
					unhide2++;
					if (unhide2 == unhideSnake2.size()) {
						unhide2 = 0;
					}
				}
			}
		}
	}
}

void SnakesGame::reset() {
	direction1.clear();
	direction2.clear();
	eaterDir.clear();
	eaterReplayDir.clear();
	unhideSnake1.clear();
	unhideSnake2.clear();
}


void SnakesGame::run() {

	bool stop = false;
	int max_size = 15;
	int ticker = 0;
	int eaterInd = 0;
	board.addNumber(snakes, snakes.size());
	addBoard(board);
	board.display();
	task_manager.create_tasks_bank();
	
	while (!stop)
	{
		
	
		gotoxy(0, 1);
		task_manager.print();
		if (eaterDir.empty() && solutionFound()) {// if eater didnt move
			fastWay();
		}
		char keyPressed = getKey();
		if (keyPressed == KEYS::ESC) {
			gotoxy(0, 10);
			secondaryMenu();
			break;
		}
		Sleep(100);

		if (force_changing_task) {
			changeCurrentTask(winner);
			eaterDir.clear();
			eaterInd = 0;
			numEater.setLocation(10, 19);
			numEater.changeDir(Direction::STAY);
			eaterReplayDir.clear();
			force_changing_task = false;
			setReplaySizes(snakes[0].getSize(), snakes[1].getSize());
			setReplaySnakesLocation();
			snakes[2].setDirection(snakes[0].getDirection());
			snakes[3].setDirection(snakes[1].getDirection());
			direction1.clear();
			direction2.clear();
		}
		
		for (size_t i = 0; i < 2; ++i) {

			if (snakes[i].getSize() >= max_size) {
				gotoxy(10, 0);
				cout << "Winning snake: " << snakes[i].getChar() << "                       ";
				stop = true;
				break;
			}

			// Checks if snake is intersecting with other snake or himself
			if (willIntersect(snakes[i])) {
				return;
			}

			moveSnake(i, keyPressed);
		}


		gotoxy(0, 4);
		cout << "Numbers on the board: " << board.getNumbersCount() << "   ";

		if (isTaskTimedOut())
		{
			onTaskFinidhed();
			eaterInd = 0;
			eaterDir.clear();
			numEater.setLocation(10, 19);
			numEater.changeDir(Direction::STAY);
		}

		for (size_t i = 0; i < 2; i++) {
			if (!eaterDir.empty()) {
				numEater.changeDir(eaterDir[eaterInd]);
				eaterReplayDir.push_back(eaterDir[eaterInd]);
				moveEater(numEater);
				eaterInd++;
				if (eaterInd == eaterDir.size()) {
					eaterInd = 0;
					eaterDir.clear();
					numEater.changeDir(Direction::STAY);
				}
			}
			else if (!solutionFound()) {
				moveEater(numEater);
				eaterReplayDir.push_back(Direction::STAY);
			}
		}
		
		
		for (size_t j = 0; j < 2; j++) {
			moveShots();

			for (size_t i = 0; i < lineFlies.size(); i++) {
				moveFly(lineFlies[i],false);
			}
		}
		
		
		for (size_t i = 0; i < columnFlies.size(); i++) {
			moveFly(columnFlies[i],false);
		}
		

		if (ticker > 5) {
			board.addNumber(snakes,2);
			addBoard(board);
			board.display();
			ticker = 0;
		}
		else {
			ticker++;
		}
		addDirection(snakes[0].getDirection(), snakes[1].getDirection());
	}
}

void SnakesGame:: replay()
{
	bool stop = false;
	int ticker = 0;
	int i = 0, j = 0, k = 0, m=0, p=0;
	board = saveBoards[0];
	board.display();
	
	while (!stop)
	{
		
		snakes[2].setDirection(direction1[i]);
		snakes[2].move('j');
		snakes[3].setDirection(direction2[m]);
		snakes[3].move('j');
		Sleep(100);

		for (int l = 0; l < 2; l++) {
			numEaterReplay.changeDir(eaterReplayDir[k]);
			moveEater(numEaterReplay);
			moveFly(replayLineFlies[0], true);
			moveFly(replayLineFlies[1], true);
			k++;
			if (k == eaterReplayDir.size()) {
				k = 0;
			}
		}
		moveFly(replayColumnFlies[0],true);
		moveFly(replayColumnFlies[1],true);
		
		if (ticker > 5) {
			ticker = 0;
			board = saveBoards[j];
			board.display();
			j++;
			if (j==saveBoards.size()){
				j = 0;
			}
		}
		else {
			ticker++;
		}
		i++;
		m++;
		if (i == direction1.size() || m == direction2.size()) {
			i = 0;
			j = 0;
			stop = true;
		}
	}
}

void SnakesGame::setReplaySnakesLocation() {
	snakes[2].setHead(snakes[0].getHead());
	snakes[3].setHead(snakes[1].getHead());
}


void SnakesGame::MainMenu() 
{
	cout << "To game instructions press 1" << endl;
	cout << "To start the game press 2" << endl;
	cout << "To exit the game press 9" << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case'1':
		instructions();
		break;

	case '2':
	{
		snakes[0] = { { 10, 9 }, 3, '@' };
		snakes[1] = { { 70, 9 }, 3, '#' };
		snakes[0].setKeys('a', 'd', 'w', 'x');
		snakes[1].setKeys('j', 'l', 'i', ',');
		board.clear();
		run();
		break;
	}

	case '9':
		cout << "good bye!";
		break;
	}
}


void SnakesGame::secondaryMenu()
{

	cout << "to exit the game press 1" << endl;
	cout << "to the main menu press 2" << endl;
	cout << "to continue the game press 3" << endl;
	cout << "to restart the task press 4" << endl;
	cout << "to start a new task press 5" << endl;
	cout << "to restart game press 6" << endl;
	cout << "to replay task press 7" << endl;
	char option;
	cin >> option;
	switch (option)
	{
	case '1':
		cout << "good bye!";
		break;
	case '2':
		MainMenu();
		break;
	case '3':
		run();
		break;
	case '4':
	{
		board.removeNumbers(board.getNumbersCount() / 2);
		run();
		break;
	}
	case '5':
	{
		task_manager.task_accomplished();
		board.removeNumbers(board.getNumbersCount() / 2);
		run();
		break;
	}
	case '6':
	{
		snakes[0] = { { 10, 9 }, 3, '@' };
		snakes[1] = { { 70, 9 }, 3, '#' };
		snakes[0].setKeys('a', 'd', 'w', 'x');
		snakes[1].setKeys('j', 'l', 'i', ',');
		snakes[2] = { { 10, 9 }, 3, '@' };
		snakes[3] = { { 70, 9 }, 3, '#' };
		reset();
		board.clear();
		run();
	}
	case '7':
	{
		replay();
		gotoxy(0,10);
		secondaryMenu();
	}
	}
	
}

void SnakesGame::instructions()/////////////////////////////////
{
	cout << "Every player has his own snake which is used to collect numbers as required by the given task." << endl;
	cout << "A player wins a point when he collects the right number or" << endl;
	cout << "in case that the rival collects a wrong number." << endl;
	cout << "The first player who gets 12 points is the winner" << endl;
}

void SnakesGame::addDirection(Direction d1, Direction d2) {
	direction1.push_back(d1);
	direction2.push_back(d2);
}

void SnakesGame::addBoard(Board _board) { saveBoards.push_back(_board); }

void SnakesGame::setReplaySizes(size_t size1, size_t size2) {
	snakes[2].setSize(size1);
	snakes[3].setSize(size2);
}
