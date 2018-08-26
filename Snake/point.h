#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "stdafx.h"
#include "Gotoxy.h"
#include "Direction.h"

using namespace std;

class Point
{

protected:
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;
	char symbol;
	bool crossScreen;
	
	void moveImpl();

public:
	// consider moving this enum to a more suitable place
	enum { min_x = 0, max_x = 80, min_y = 5, max_y = 23 };

	Point(int x1 = 1, int y1 = 1) {
		x = x1;
		y = y1;
		symbol = ' ';
	};

	Point(char _symbol, int x1, int y1, bool _crossScreen = true) {
		Point(x1, y1);
		symbol = _symbol;
		crossScreen = _crossScreen;
	}

	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void setSymbol(char c) { symbol = c; }
	int getX() const { return x; }
	int getY() const { return y; }
	int nextY();
	int nextX();
	void draw();
	void changeDir(Direction dir);
	void clear();
	void move(Direction dir);
};


#endif
