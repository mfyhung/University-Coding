#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
Name: Hung Fan Yan
Student ID: 1155083147
Course: CSCI1120
Assignment: 2
*/

void displayGrid(long long grid);
bool isFilled(long long grid, int pos);
int playerScore(long long grid, int p);
void updataGrid(long long &grid, int pos, int p);
int gamestate(long long grid);
long long power(long long num);
void get_the_pos(int &pos, int p, long long a);
//The function prototype
int main() {
	long long num = 000000000000000000;//the code of the grid without any input
	int player = 1, position;//the variable
	displayGrid(num);//call out the empty grid
	int player1_check = 0, player2_check = 0;//the variable use to give the player any other chance
	do {
		get_the_pos(position, player, num);//input the position of the player
		updataGrid(num, position, player);//call out the score updata function
		if ((num % 10) > player2_check) {// check the score increase , if which is increasing then back to the top of the do-while loop
			cout << "Player 2 scores! Gets an extra turn." << endl;
			player2_check++;//updata the checking
			displayGrid(num);//call out the grid again
			continue;
		}
		else if ((num % 100) / 10 > player1_check) {
			cout << "Player 1 scores! Gets an extra turn." << endl;
			player1_check++;//updata the checking
			displayGrid(num);//call out the grid again
			continue;
		}
		displayGrid(num);//normal situation if no one scored to call out the grid

		if (player == 1) {//change the player to player2
			player++;
		}
		else {
			player--;//back to the player1
		}
	} while (gamestate(num) == 3);//if the gamestate is not 1/2 keep looping
	return 0;
}
void displayGrid(long long grid) {//print the grid
	if (grid / 100000000000000000 == 0) {
		cout << "   o  o" << endl;
	}
	else {
		cout << "   o--o" << endl;
	}//The if statement to output the first line of the grid.
	cout << "  ";
	for (int i = 2; i <= 3; i++) {
		cout << " ";
		if ((grid % power(i)) / power(i + 1) == 0) {
			cout << "  ";
		}
		else {
			cout << "| ";
		}
	}//Print the 2th line of the grid.
	cout << endl;
	for (int i = 4; i <= 6; i++) {
		cout << "o";
		if ((grid % power(i)) / power(i + 1) == 0) {
			cout << "  ";
		}
		else {
			cout << "--";
		}
		if (i == 6)
			cout << "o";
	}//Print the 3th line.
	cout << playerScore(grid, 1);
	cout << endl;
	for (int i = 7; i <= 10; i++) {
		if ((grid % power(i)) / power(i + 1) == 0) {
			cout << "   ";
		}
		else {
			cout << "|  ";
		}
	}//Print the 4th line
	cout << endl;
	for (int i = 11; i <= 13; i++) {
		cout << "o";
		if ((grid % power(i)) / power(i + 1) == 0) {
			cout << "  ";
		}
		else {
			cout << "--";
		}
		if (i == 13)
			cout << "o";
	}//Print the 5th line.
	cout << playerScore(grid, 2);
	cout << endl;
	cout << "  ";
	for (int i = 14; i <= 15; i++) {
		cout << " ";
		if ((grid % power(i)) / power(i + 1) == 0) {
			cout << "  ";
		}
		else {
			cout << "| ";
		}
	}//Print the 6th line.
	cout << endl;
	cout << "   o";
	if ((grid % power(16)) / power(17) == 0) {
		cout << "  ";
	}
	else {
		cout << "--";
	}
	cout << "o";
	cout << endl;
}//print the last line of the function

int gamestate(long long grid) {
	if ((grid - grid % 100) == 111111111111111100) {//when all block is fulled
		if (grid % 10 > ((grid % 100) / 10)) {//check the 17,18th number of the long long num
			cout << "Player 2 wins!" << endl;
			return 2;
		}
		else {
			cout << "Player 1 wins!" << endl;
			return 1;
		}
	}
	else {//if there are empty block
		return 3;
	}
}//use to check the condition, if which is fulfil and then break the loop
long long power(long long num) {
	long long power_num = 19 - num;
	long long sum = 10;
	for (int i = 1; i < power_num; i++) {
		sum *= 10;
	}
	return sum;
}//just a program that doing the pow()function work, but using the long long data type
int playerScore(long long grid, int p) {
	cout << "   ";
	int score;
	if (p == 1) {
		score = ((grid % 100 / 10));//check the position of the long long num of player1
	}
	else {
		score = (grid % 10);//check the position of the long long num of player1
	}
	cout << "Player " << p << " score: ";
	return score;
}//To return the player make back to the displaygrid function
bool isFilled(long long grid, int pos) {
	long long check;
	if (pos > 16 || pos < 1) {//to check the position is include in 1 to 16 or not
		cout << "Invalid move! Try again." << endl;
		return true;
	}
	check = (grid%power(pos)) / power(pos + 1);//to check the position is empty or not
	if (check == 1) {
		cout << "Invalid move! Try again." << endl;
		return true;
	}
	else if (check == 0) {//which is a empty box of the long long num
		return false;
	}
	return false;
}//use to check a valid position 
void updataGrid(long long &grid, int pos, int p) {
	grid = grid + power(pos + 1);//updata the num form the empty box to 1
	//to check the the box is filled 
	if (((grid%power(1)) / power(2)) == 1 && ((grid%power(2)) / power(3)) == 1 && ((grid%power(3)) / power(4)) == 1 && ((grid%power(5)) / power(6)) == 1 && (pos == 1 || pos == 2 || pos == 3 || pos == 5)) {//check the box situation 1,when the position is input is the box situation in the same time
		//the condition of the player to check who should scored
		if (p == 1) {
			grid = grid + 10;
		}
		else {
			grid = grid + 1;
		}
	}
	if (((grid%power(4)) / power(5)) == 1 && ((grid%power(7)) / power(8)) == 1 && ((grid%power(8)) / power(9)) == 1 && ((grid%power(11)) / power(12)) == 1 && (pos == 4 || pos == 7 || pos == 8 || pos == 11)) {//box 2 situation
		if (p == 1) {
			grid = grid + 10;
		}
		else {
			grid = grid + 1;
		}
	}
	if (((grid%power(5)) / power(6)) == 1 && ((grid%power(8)) / power(9)) == 1 && ((grid%power(9)) / power(10)) == 1 && ((grid%power(12)) / power(13)) == 1 && (pos == 5 || pos == 8 || pos == 9 || pos == 12)) {//box 3 situation
		if (p == 1) {
			grid = grid + 10;
		}
		else {
			grid = grid + 1;
		}
	}
	if (((grid%power(6)) / power(7)) == 1 && ((grid%power(9)) / power(10)) == 1 && ((grid%power(10)) / power(11)) == 1 && ((grid%power(13)) / power(14)) == 1 && (pos == 6 || pos == 9 || pos == 10 || pos == 13)) {//box 4 situation
		if (p == 1) {
			grid = grid + 10;
		}
		else {
			grid = grid + 1;
		}
	}
	if (((grid%power(12)) / power(13)) == 1 && ((grid%power(14)) / power(15)) == 1 && ((grid%power(15)) / power(16)) == 1 && ((grid%power(16)) / power(17)) == 1 && (pos == 12 || pos == 14 || pos == 15 || pos == 16)) {//bos 5 situation
		if (p == 1) {
			grid = grid + 10;
		}
		else {
			grid = grid + 1;
		}
	}
}//use to updata the scores.
void get_the_pos(int &pos, int p, long long a) {
	do {
		cout << "Player " << p << ", make your move <1-16>: ";
		cin >> pos;
	} while (isFilled(a, pos));//check the position, if which is return false, if it not fulfil therequirement than request forthe another position. 
}//a function that getting the position input by the user