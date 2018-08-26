
#include "stdafx.h"
#include "taskmanager.h"
using namespace std;

bool TaskManager::check(int number) {
	switch (curr_task.getFormula()) {
	case 1:
		return number == pow(curr_task.getX(),2) + pow(curr_task.getY(),2);
	case 2:
		return number % curr_task.getX() == 0;
	case 3:
		return number% curr_task.getX()==0;
	case 4:
		return number % 2 !=0 && number>curr_task.getX();
	case 5:
		return number%curr_task.getX() == 3;
	case 6:
		return task7.solveEquation(number);
	}

	return false;
}

int rand_in_range3(const int start, const int end) {// draws number in a given range. 
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(start, end);

	return uni(rng);

}



void TaskManager::create_tasks_bank()
{

	x = rand_in_range3(1, 10);
	y = rand_in_range3(1, 10);
	int i;
	vector<string> texts = { 
		"solve: " + to_string(x) + " ^ 2 + " + to_string(y) + " ^2 =           " ,
		"Find a number which can be devided by" + to_string(x) + "                  ",
		"Find a number which is multiply of" + to_string(x) + "                    ",
		"Find a number which is odd and greater than " + to_string(x) + "                      ",
		"Find a number which its modulo of " + to_string(x) + " is 3                       " 
	};
	
	ofstream fout("tasks.txt", ios::trunc);
	
	for (i = 0; i < 5; i++) {
		fout << texts[i] << endl;
		fout << x << y << endl;
		fout << i+1 << endl; //formula
	}

	fout.close();

	string _text;
	char endl = '\n';
	int _formula;
	int _x, _y;
	ifstream fin("tasks.txt");
	for (i = 0; i < 5; i++) {
		getline(fin, _text);
		fin >>_x >> _y;
		fin.get(endl);
		fin >> _formula;
		fin.get(endl);
	
		task new_task = { _text, _x, _y, _formula };
		tasks_bank.push_back(new_task);
	}

	fin.clear();
	fout.clear();

	fin.close();

	int draw_ind = rand_in_range3(0, 4);
	curr_task.setText(tasks_bank[draw_ind].getText());
	curr_task.setX(tasks_bank[draw_ind].getX());
	curr_task.setY(tasks_bank[draw_ind].getY());
	curr_task.setFormula(tasks_bank[draw_ind].getFormula());
}

void TaskManager::task_accomplished() {
	
	tasks_bank.clear();
	create_tasks_bank();
}

