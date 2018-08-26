#pragma once
#ifndef _FLY_H_
#define _FLY_H_
#include "stdafx.h"
#include "point.h"

class Fly :
	public Point
{
	Direction dir;
	

public:
	Fly(char c, int x1, int y1, Direction _dir, bool _crossScreen) {
		symbol = c;
		x = x1;
		y = y1;
		crossScreen = _crossScreen;
		dir = _dir;
		changeDir(dir);
	}
	~Fly() {};

	void move();

	Direction getDir() {
		return dir;
	}

	void setLocation(int _x, int _y);

	bool operator==(const Fly& rhs);

};
#endif