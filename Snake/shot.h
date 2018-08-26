#pragma once
#ifndef _SHOT_H_
#define _SHOT_H_
#include "stdafx.h"
#include "Direction.h"
#include "point.h"

class Shot: public Point
{

	Direction dir;

public:
	Shot(Direction _direction, int x, int y);
	~Shot();
	void move();
	bool operator==(const Shot& rhs);
};

#endif

