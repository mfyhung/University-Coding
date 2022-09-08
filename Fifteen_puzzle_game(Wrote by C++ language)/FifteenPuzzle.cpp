#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "FifteenPuzzle.h"
using namespace std;

FifteenPuzzle::FifteenPuzzle(unsigned s) {
	int tem, num = 1;
	int i, j, p, q;
	steps = 0;
	srand(s);
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			board[i][j] = num;
			num++;
		}
	}
	for (int w = 0;w < 200;w++) {
		i = rand() % 4, j = rand() % 4, p = rand() % 4, q = rand() % 4;
		tem = board[i][j];
		board[i][j] = board[p][q];
		board[p][q] = tem;
	}
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == 16) {
				r = i;
				c = j;
			}

		}
	}
}
bool FifteenPuzzle::move(char dir) {
	int tem;
	if (dir == 'k' || dir == 'K') {
		if (c == 3) {
			return false;
		}
		else {
			tem = board[r][c];
			board[r][c] = board[r][c + 1];
			board[r][c + 1] = tem;
			c++;
			steps++;
			return true;
		}
	}
	if (dir == 'j' || dir == 'J') {
		if (c == 0) {
			return false;
		}
		else {
			tem = board[r][c];
			board[r][c] = board[r][c - 1];
			board[r][c - 1] = tem;
			c--;
			steps++;
			return true;
		}
	}
	if (dir == 'i' || dir == 'I') {
		if (r == 0) {
			return false;
		}
		else {
			tem = board[r][c];
			board[r][c] = board[r - 1][c];
			board[r - 1][c] = tem;
			r--;
			steps++;
			return true;
		}
	}
	if (dir == 'm' || dir == 'M') {
		if (r == 3) {
			return false;
		}
		else {
			tem = board[r][c];
			board[r][c] = board[r + 1][c];
			board[r + 1][c] = tem;
			r++;
			steps++;
			return true;
		}
	}
	return false;
}
void FifteenPuzzle::print() const {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == 16) {
				cout << setw(3) << ".";
			}
			else
				cout << setw(3) << board[i][j];
		}
		cout << endl;
	}
}
int FifteenPuzzle::getSteps() const {
	return steps;

}
bool FifteenPuzzle::isSolved() const {
	int check = 1;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (board[i][j] == check) {
				check++;
			}
		}
	}
	if (check == 17) {
		return true;
	}
	else {
		return false;
	}
}