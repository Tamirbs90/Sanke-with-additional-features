#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "stdafx.h"
#include "Point.h"

#include "Direction.h"
#include "point.h"

class Snake {
	size_t size;
	Point body[12];
	Direction direction;
	char c;
	char dirKeys[4]; // the keys for the four possible directions
	bool move_enabled = true;
	bool hidden = false;
	size_t hiddenCounter = 0;
	size_t shotsCount = 0;

public:

	Snake(const Point& head, int size, char c1, Direction dir = Direction::DOWN);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	void changeDir(char keyPressed);
	Point move(char keyPressed);
	char getChar() const { return c; }
	int getSize() const { return size; }
	void setSize(size_t size);
	void increase(int num);
	bool intersect(Point p);

	void setDirection(Direction d)
	{
		direction = d;
	}

	void setHead(Point p) {
		body[0].setX (p.getX());
		body[0].setY (p.getY());
	}

	void disable_move() { move_enabled = false; }
	void enable_move() { move_enabled = true; }
	Point nextPoint();
	Point getHead() { return body[0]; }
	Direction getDirection() { return direction; }

	void hide();
	void unhide(size_t size, const Point& location);
	bool isHidden();
	bool shouldBeHidden();

	void decreaseShotsCount() {
		shotsCount += 1;
	}

	void increaseShotsCount() {
		shotsCount += 1;
	}

	bool hasShots() {
		return shotsCount < 5;
	}
};


#endif
