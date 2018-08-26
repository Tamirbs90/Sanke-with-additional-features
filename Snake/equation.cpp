#include "stdafx.h"
#include "Equation.h"

int Equation::solve()
{
	switch (op1)
	{
	default:
	case '+':
	{
		if (op2 == '+')
			return num1 + num2 + num3;
		if (op2 == '-')
			return num1 + num2 - num3;
		if (op2 == '*')
			return num1 + num2 * num3;
		if (op2 == '/')
			return num1 + num2 / num3;
		break;
	}

	case '-':
	{
		if (op2 == '+')
			return num1 - num2 + num3;
		if (op2 == '-')
			return num1 - num2 - num3;
		if (op2 == '*')
			return num1 - num2 * num3;
		if (op2 == '/')
			return num1 - num2 / num3;
		break;
	}

	case '*':
	{
		if (op2 == '+')
			return num1 * num2 + num3;
		if (op2 == '-')
			return num1 * num2 - num3;
		if (op2 == '*')
			return num1 * num2 * num3;
		if (op2 == '/')
			return num1 * num2 / num3;
		break;
	}

	case '/':
	{
		if (op2 == '+')
			return num1 / num2 + num3;
		if (op2 == '-')
			return num1 / num2 - num3;
		if (op2 == '*')
			return num1 / num2 * num3;
		if (op2 == '/')
			return num1 / num2 / num3;
		break;
	}
	}

	return 0;
}

int rand_in_range2(const int start, const int end) {// draws number in a given range. 
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(start, end);

	return uni(rng);

}

void Equation::setMissingPlace() { missingPlace = rand_in_range2(1, 4); }// draws a missing num. 

int findDividors(int numToDivide)// in case that the opertaor is '/', finds a dividor the the input
//so the result will be an integer.  
{
	vector<int> dividors;
	for (int i = 1; i <=169; i++)
	{
		if (numToDivide%i == 0)
			dividors.push_back(i);
	}
	return dividors[rand_in_range2(0, dividors.size() - 1)];//draws a number among the input's dividors. 
}

void Equation::drawNums() // draws the numbers of ghe equation. 
{
	
	num1 = rand_in_range2(0, 169);// draws num1. 
	
	if (op1 == '/')
	{
		num2 = findDividors(num1);// in case that the first op is '/', find a dividor. 
	}
	else {
		num2 = rand_in_range2(0, 169); //if not, draw num2. 
	}
	
	if (op2 == '/')
	{
		if (op1 == '/')
		{
			num3 = findDividors(num1/num2);// in case the first op and the seconf op are '/'.
		}
		else if (op1 == '*')
		{
			num3 = findDividors(num1*num2); // in case that the first op is '*' and the second is '/',
		}
		else 
		{
			num3 = findDividors(num2);// in case that the first op is + or -
		}
	}
	else 
	{
		num3 = rand_in_range2(0, 169);// if op2 is not '/'
	}
	
	num4 = solve(); // calculate num4. 
}

void Equation::setNumbers() 
{
	bool goodEquation = false;
	while (goodEquation == false)
	{
		drawNums();
		if (num4 >= 0 && num4 <= 169)
		{
			goodEquation = true;
		}
	}
}


bool Equation::solveEquation(int num) {
	
	switch (missingPlace)
	{
	case 1:
	{
		if ( (op1 == '*' && num2 == 0) || (op1=='*' && op2=='*' && num3==0) )
			return true;
		else if (num == num1)
			return true;
		break;
	}

	case 2:
	{
		if ( (num1 == 0 && (op1 == '*' || op1 == '/')) || (num3 == 0 && op2 == '*') )
			return true;
		else if (num == num2)
			return true;
		break;
	}

	case 3:
	{
		if ((num2 == 0 && op2 == '*') || (num1 == 0 && op1 == '*' && op2 == '*'))
			return true;
		else if (num == num3)
			return true;
		break;
	}

	case 4:
	{
		if (num == num4)
			return true;
		break;
	}

	}
	
	return false;
}

void Equation::setOperators() {
	char operators[4] = { '+', '-', '/', '*' };
	op1 = operators[rand_in_range2(0, 3)];
	op2 = operators[rand_in_range2(0, 3)];
}


void Equation::print()
{
	switch (missingPlace)
	{
	case 1:
	{
		cout << "Solve the next equation: __ " << op1 << num2 << op2 << num3 << " = " << num4;
		break;
	}
	case 2:
	{
		cout << "Solve the next equation: " << num1 << op1 << " __ " << op2 << num3 << "=" << num4;
		break;
	}
	case 3:
	{
		cout << "Solve the next equation: " << num1 << op1 << num2 << op2 << " __ = " << num4;
		break;
	}
	case 4:
	{
		cout << "Solve the next equation: " << num1 << op1 << num2 << op2 << num3 << " = __";
		break;
	}
	}
}