#pragma once
#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_
#include "Equation.h"
#include <fstream>
#include <string>
#include "task.h"


class TaskManager {
	
	task curr_task;
	vector<task> tasks_bank;
	int x, y;
	Equation task7;


public:
	bool check(int number);

	void create_tasks_bank();

	void new_task();


	void print() {
		cout << curr_task.getText();
	}

	void task_accomplished();
};

#endif