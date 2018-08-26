#include "stdafx.h"
#include "point.h"

void Point::draw() {
	gotoxy(x, y);
	cout << symbol << endl;
}

void Point::clear() {
	gotoxy(x, y);
	cout << " " << endl;
}

int Point::nextX(){
	if (crossScreen) {
		return (-min_x + x + dir_x + (max_x - min_x + 1)) % (max_x - min_x + 1) + min_x;
	}
	
	int next = x + dir_x;

	if (next >= max_x) {
		changeDir(Direction::LEFT);
	}

	if (next <= min_x) {
		changeDir(Direction::RIGHT);
	}

	return  x + dir_x;
}

int Point::nextY(){

	if (crossScreen) {
		return (-min_y + y + dir_y + (max_y - min_y + 1)) % (max_y - min_y + 1) + min_y;
	}

	int next = y + dir_y;

	if (next >= max_y) {
		changeDir(Direction::UP);
	}

	if (next <= min_y) {
		changeDir(Direction::DOWN);
	}

	return y + dir_y;

}

void Point::moveImpl() {
	x = nextX();
	y = nextY();
}

void Point::move(Direction dir) {
	changeDir(dir);
	moveImpl();
}


void Point::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	case Direction::STAY:
		dir_x = 0;
		dir_y = 0;
	}
}