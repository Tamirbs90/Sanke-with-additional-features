#pragma once

#ifndef _READTASKS_H_
#define _READTASKS_H_


#include <fstream>
#include "stdafx.h"
#include "task.h"
#include <string>
using namespace std;

class readTasks  {
	task task1, task2, task3, task4, task5;
	int x, y, num;
	string texts[5] = { "solve: " +to_string(x)+ " * " +to_string(y)+ " - "+to_string(y)+ " ^2 =" ,
		"Find a number which can be devided by" + to_string(x),
		"Find a number which is multiply of" + to_string(x),
		"Find a number which is odd and greater than " +to_string(x),
		 "Find a number which its modulo of " + to_string(x) + " is 3" };

	string formulas[5] = { to_string(x) + " * " + to_string(y) + " - " + to_string(y) + " ^ 2 =" + to_string(num),
		to_string(num) + "%" + to_string(x) + "=0",
		to_string(num) + "%" + to_string(x) + "=0",
		to_string(y) + "^" + to_string(x) + "=" + to_string(num),
		to_string(num) + "%" + to_string(x) + "=" + to_string(y) };




public:

	task readToFile();


};


#endif 

