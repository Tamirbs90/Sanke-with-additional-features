#include "stdafx.h"
#include "shot.h"


Shot::Shot(Direction _dir, int x1, int y1)
{
	symbol = '*';
	x = x1;
	y = y1;
	dir = _dir;
}


Shot::~Shot()
{
}

void Shot::move() {
	clear();
	Point::move(dir);
	draw();
}

bool Shot::operator== (const Shot& rhs) {
	return getX() == rhs.getX() && getY() == rhs.getY() && dir==rhs.dir;
}


