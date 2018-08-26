#include "stdafx.h"
#include "snake.h"

Snake::Snake(const Point& head, int _size, char c1, Direction dir) {
	c = c1;
	size = _size;
	direction = dir;

	body[0].setX(head.getX());
	body[0].setY(head.getY());
	body[0].setSymbol(c1);

	body[0].draw();
	for (size_t i = 1; i < size; ++i) {
		body[i] = body[i - 1];
		body[0].setSymbol(c1);
		body[i].draw();
	}
}
void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown) {
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
}


void Snake::changeDir(char keyPressed) {
	for (const auto& key : dirKeys) {
		if (key == keyPressed) {
			direction = (Direction)(&key - dirKeys);
		}
	}
	return;
}


Point Snake::move(char keyPressed) {
	body[size-1].clear();
	for (int i = size -1; i > 0; --i) {
		body[i] = body[i - 1];
	}

	changeDir(keyPressed);
	body[0].move(direction);
	
	
	for (int j = 0; j < size; j++)
	{
		body[j].draw();
	}
	
	return body[0];
}

void Snake::increase(int num) {
	setSize(size + num);
}

bool Snake::intersect(Point p) {

	for (size_t i = 0; i < size; i++) {
		if (body[i].getX() == p.getX() && body[i].getY() == p.getY()) {
			return true;
		}
	}

	return false;

}

Point Snake::nextPoint(){
	Point p = {c, body[0].nextX(), body[0].nextY() };
	return p;
}


void Snake::setSize(size_t _size) {
	if (_size > 12) {
		_size = 12;
	}
	size = _size;

	for (size_t i = 1; i < _size; ++i) {
		body[i].draw();
	}
}

void Snake::hide() {
	hidden = true;
	hiddenCounter = 0;
	setSize(0);
}

void Snake::unhide(size_t size, const Point& location) {
	hidden = false;
	hiddenCounter = 0;
	setSize(size);
	body[0].setX(location.getX());
	body[0].setY(location.getY());
}

bool Snake::isHidden() {
	return hidden;
}

bool Snake::shouldBeHidden() {
	if (hiddenCounter>=5) {
		hiddenCounter = 0;
		return false;
	}

	hiddenCounter++;
	return true;
}