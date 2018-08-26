#pragma once
#ifndef _TASK_H_
#define _TASK_H_

#include "stdafx.h"
#include <string>
using namespace std;

class task {

	string text;
	int x, y;
	int formula;

public:

	task() {}
	task(string _text, int _x, int _y, int _formula) :text(_text), x(_x), y(_y), formula(_formula) {}
	
	string getText() { return text; }
	int getX() { return x; }
	int getY() { return y; }
	int getFormula() { return formula; }
	void setText(string str) { text=str; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void setFormula(int _formula) { formula = _formula; }

	void print() {
		cout << text << endl;
	}

};

#endif




