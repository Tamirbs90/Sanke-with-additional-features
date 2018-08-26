#include "stdafx.h"
#include "fly.h"
#include "board.h"


void Fly::move() {
	clear();
	Point::moveImpl();
	draw();
}

void Fly::setLocation(int _x, int _y)
{
	x = _x;
	y = _y;
}

bool Fly::operator== (const Fly& rhs) {
	return getX() == rhs.getX() && getY() == rhs.getY() && dir == rhs.dir;
}


