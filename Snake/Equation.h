#pragma once
#ifndef _EQUATION_H_
#define _EQUATION_H_
#include "stdafx.h"
using namespace std;

class Equation {

	int num1, num2, num3, num4;
	char op1, op2;
	int missingPlace;

public:
	Equation() {
		setOperators();
		setNumbers();
		setMissingPlace();
	
	}

	void setNumbers();
	int  solve();
	void setMissingPlace();
	void setOperators();
	bool solveEquation(int num);
	
	void setNewEquation() {
		setOperators();
		setNumbers();
		setMissingPlace();
	}

	void drawNums();
	
	void print();

};


#endif

