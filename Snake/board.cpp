#include "stdafx.h"
#include "board.h"

int Board::getNumber(const Point& pos) {
	int x = pos.getX() - padding_left;
	int y = pos.getY() - padding_top;
	int num = -1;

	int digit = getDigit(x, y);

	if (digit < 0) {
		return -1;
	}

	int digit_to_left = -1;
	int digit_to_right = -1;
	if (x > 0) {
		digit_to_left = getDigit(x - 1, y);
		if (digit_to_left > -1) {
			if (x > 1) {
				int digit_to_left_left = getDigit(x - 2, y);
				if (digit_to_left_left > 0) {
					return digit_to_left_left * 100 + digit_to_left * 10 + digit;
				}
			}
		}
	}

	if (x < cols) {
		digit_to_right = getDigit(x + 1, y);
		if (digit_to_right > -1) {
			if (x < cols - 1) {
				int digit_to_right_right = getDigit(x + 2, y);
				if (digit_to_right_right >= 0) {
					return digit * 100 + digit_to_right * 10 + digit_to_right_right;
				}
			}

		}
	}

	if (digit_to_left > -1 && digit_to_right > -1) {
		return digit_to_left * 100 + digit * 10 + digit_to_right;
	}
	else if (digit_to_left > -1) {
		return digit_to_left * 10 + digit;
	}
	else if (digit_to_right > -1) {
		return digit * 10 + digit_to_right;
	}

	return digit;
}


int Board::getDigit(int x, int y) {
	if (x > cols || y > rows) { return -1; }
	char c = screen[y][x];

	if (c >= '1' || c <= '9') {
		return c - '0';
	}

	return -1;
}


void Board::display() {
	for (int i = 0; i < rows; ++i) {
		gotoxy(padding_left, padding_top + i);
		for (int j = 0; j < cols; j++) {
			cout << screen[i][j];
		}
		cout << "\n";
	}
}

int rand_in_range(const int start,const int end) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(start, end);

	return uni(rng);
	
}

void Board::addNumber(std::vector<Snake> &snakes, size_t snakes_count) {

	int num = 0;

	switch (numberGroup) {
	default:
	case 0:
		num = rand_in_range(0, 25);
		break;
	case 1:
		num = rand_in_range(26, 81);
		break;
	case 2:
		num = rand_in_range(81, 169);
		break;
	}

	if (numberGroup < 3) {
		numberGroup += 1;
	}
	else {
		numberGroup = 0;
	}

	
	int rand_col = rand_in_range(0, cols);
	int rand_row = rand_in_range(0, rows);

	// check siblings
	if ((screen[rand_row][rand_col] != ' ') ||
		(rand_col == 0 && screen[rand_row][rand_col + 1] != ' ') ||
		(rand_col == cols && screen[rand_row][rand_col - 1] != ' ') ||
		(screen[rand_row][rand_col - 1] != ' ' && screen[rand_row][rand_col + 1] != ' ')) {
		return;
	}

	for (size_t i = 0; i < snakes_count; i++) {
		int snake_x = snakes[i].getHead().getX();
		int snake_y = snakes[i].getHead().getY();
		Direction snake_dir = snakes[i].getDirection();

		if ((snake_dir == Direction::DOWN &&  snake_y + 1 == rand_row && snake_x==rand_col) ||
			(snake_dir == Direction::UP &&  snake_y - 1 == rand_row && snake_x==rand_col) ||
			(snake_dir == Direction::LEFT && snake_x - 1 == rand_col && snake_y==rand_row) ||
			(snake_dir == Direction::RIGHT && snake_x + 1 == rand_col && snake_y==rand_row) ) {
			return;
		}
	}

	if (num < 10) {
		screen[rand_row][rand_col] = num + '0';
		numberToCell.insert({ num, {rand_row,rand_col} });
		allNumbers.push_back(num);
		return;
	}

	if (num > 9 && num < 100) {
		if (rand_col == cols) {
			return;
		}
		else if (rand_col < cols - 1 && screen[rand_row][rand_col + 2] != ' ') {
			return;
		}

		screen[rand_row][rand_col] = num / 10 + '0';
		screen[rand_row][rand_col + 1] = num % 10 + '0';
		numberToCell.insert({ num, {rand_row,rand_col} });
		allNumbers.push_back(num);
		return;
	}

	if (num > 99) {
		if (rand_col >= cols - 1) {
			return;
		}
		else if (rand_col < cols - 2 && screen[rand_row][rand_col + 3] != ' ') {
			return;
		}

		screen[rand_row][rand_col] = num / 100 + '0';
		screen[rand_row][rand_col + 1] = (num - (num / 100) * 100) / 10 + '0';
		screen[rand_row][rand_col + 2] = (num - (num / 100) * 100) % 10 + '0';
		numberToCell.insert({ num, {rand_row,rand_col} });
		allNumbers.push_back(num);
		return;
	}

}

void Board::clear() {
	allNumbers.clear();
	numberToCell.clear();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			screen[i][j] = ' ';
		}
	}
	display();
}

void Board::removeNumbers(size_t numsToRemove)
{
	
	if (allNumbers.size() < numsToRemove) {
		clear();
	}
	else {
		// std::random_shuffle(allNumbers.begin(), allNumbers.end());
		for (size_t i = 0; i < numsToRemove; i++) {
			int num = allNumbers.back();
			allNumbers.pop_back();
			_removeNumber(num);
		}
		display();
	}
	
	
}

void Board::removeNumber(int num) {
	for (size_t i = 0; i < allNumbers.size(); i++) {
		if (allNumbers[i] == num) {
			allNumbers.erase(allNumbers.begin() + i);
			_removeNumber(num);
			break;
		}
	}
	display();
}

void Board::_removeNumber(int num) {
	std::unordered_map<int, std::vector<int>>::const_iterator got = numberToCell.find(num);
	

	if (got == numberToCell.end()) {
		return;
	}

	std::vector<int> pos = got->second;

	int row = pos[0];
	int col = pos[1];
	screen[row][col] = ' ';
	if (num >= 10) {
		screen[row][col + 1] = ' ';
		if (num >= 100) {
			screen[row][col + 2] = ' ';
		}
	}
	numberToCell.erase(num);
}


std::vector<int> Board::findPositions(TaskManager taskManager) {
	for (auto const& num : allNumbers) {
		if (taskManager.check(num)) {
			return numberToCell[num];
		}
	}

	return { -1, -1 };
}

Point Board::getRandomPoint() {
	int x = rand_in_range(0, cols);
	int y = rand_in_range(0, rows);
	return { x, y };
}

void Board::clearPosition(Point& pos) {
	int num = getNumber(pos);
	if (num > 0) {
		removeNumber(num);
	}
}