#include <iostream>
#include <iomanip>
using namespace std;

void print_table(int x[][13]) {
	for (int i = 0; i < 13; i++) {//the loop that use to print out the english character row
		if (i == 0)
			cout << setw(4) << "A";
		else if (i == 1)
			cout << " B";
		else if (i == 2)
			cout << " C";
		else if (i == 3)
			cout << " D";
		else if (i == 4)
			cout << " E";
		else if (i == 5)
			cout << " F";
		else if (i == 6)
			cout << " G";
		else if (i == 7)
			cout << " H";
		else if (i == 8)
			cout << " I";
		else if (i == 9)
			cout << " J";
		else if (i == 10)
			cout << " K";
		else if (i == 11)
			cout << " L";
		else if (i == 12)
			cout << " M";
	}
	cout << endl;
	for (int i = 0; i < 13; i++) {
		cout << setw(2) << i;//print out the row number
		for (int j = 0; j < 13; j++) {//print out the board game.
			if (x[i][j] == 0) {//the inital value is 0, so when the block is 0 then print out the '.'
				cout << " .";
			}
			else if (x[i][j] == 1) {//when the player O input the block then the value will adding one then if check the block is one then output the 'o'
				cout << " O";
			}
			else if (x[i][j] == 2) {//when the player X input the block then the value will adding two then if check the block is two then output the 'x'
				cout << " X";
			}
		}
		cout << endl;
	}
}
int check_player(int p) {
	if (p == 1) {//change the player everytime before the next loop compile
		p++;
	}
	else {
		p--;
	}
	return p;
}
void input_value(int &t, int &n, int p, int x[][13]) {
	char eng;
	int number;
	do {//the loop that ask for the user input the location.
		cout << "player ";
		if (p == 1) {
			cout << "O";
		}
		else {
			cout << "X";
		}
		cout << ", make a move: ";
		cin >> eng;//input the location 
		cin >> number;
		if (eng == 'A')//change the character to different number
			t = 0;
		else if (eng == 'B')
			t = 1;
		else if (eng == 'C')
			t = 2;
		else if (eng == 'D')
			t = 3;
		else if (eng == 'E')
			t = 4;
		else if (eng == 'F')
			t = 5;
		else if (eng == 'G')
			t = 6;
		else if (eng == 'H')
			t = 7;
		else if (eng == 'I')
			t = 8;
		else if (eng == 'J')
			t = 9;
		else if (eng == 'K')
			t = 10;
		else if (eng == 'L')
			t = 11;
		else if (eng == 'M')
			t = 12;
		if (!(eng >= 'A'&&eng <= 'M') || !(number >= 0 && number <= 12) || x[number][t] != 0) {//when the input wrong, output the statement to ask anouther input and loop again.
			cout << "Invaid input, Try again!" << endl;
			continue;
		}
		else {//if no problem then this input loop is break and jump to the next statement 
			break;
		}
	} while (1);//Because it will break as well so the do-while loop is no any requirement 
	n = number;
}
int main() {
	const int num = 13;//the number for constant the array row and column value
	char check_e;//for the user input the column 
	int R[num][num] = { 0 }, check_n, player = 1, buger = 0, transfer, playerO_win = 0, playerX_win = 0, draw = 0, check_draw;//the variable that for user input or checking the game statment
	do {//launch the loop for the user input again and again
		check_draw = 0;//reset the checking of draw
		print_table(R);
		input_value(transfer, check_n, player, R);
		R[check_n][transfer] += player;//change the value according the player's input and the player name.
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (i <= 8 && R[j][i] != 0 && (R[j][i] == R[j][i + 1] && R[j][i] == R[j][i + +2] && R[j][i] == R[j][i + 3] && R[j][i] == R[j][i + 4])) {//the checking for the row bingo
					if (R[j][i] == 1) {
						playerO_win++;
						break;
					}
					else {
						playerX_win++;
						break;
					}
				}
				else if (j <= 8 && R[j][i] != 0 && (R[j][i] == R[j + 1][i] && R[j][i] == R[j + 2][i] && R[j][i] == R[j + 3][i] && R[j][i] == R[j + 4][i])) {//the checking for the column bingo
					if (R[j][i] == 1) {
						playerO_win++;
						break;
					}
					else {
						playerX_win++;
						break;
					}
				}
				else if (j <= 8 && i <= 8 && R[j][i] != 0 && (R[j][i] == R[j + 1][i + 1] && R[j][i] == R[j + 2][i + 2] && R[j][i] == R[j + 3][i + 3] && R[j][i] == R[j + 4][i + 4])) {//the checking for the \ situation.
					if (R[j][i] == 1) {
						playerO_win++;
						break;
					}
					else {
						playerX_win++;
						break;
					}
				}
				else if ((j >= 4 || i >= 4 || i <= 8) && R[j][i] != 0 && (R[j][i] == R[j - 1][i + 1] && R[j][i] == R[j - 2][i + 2] && R[j][i] == R[j - 3][i + 3] && R[j][i] == R[j - 4][i + 4])) {//the checking for the / situation
					if (R[j][i] == 1) {
						playerO_win++;
						break;
					}
					else {
						playerX_win++;
						break;
					}
				}
				for (int i = 0; i < num; i++) {//the loop for checking the draw
					for (int j = 0; j < num; j++) {//this loop will check for every time compilation.
						if (R[j][i] == 0)//when there are any empty block then the check_draw will adding, the draw situation is the check_draw be 0
							check_draw++;
					}
				}
				if (check_draw == 0) {//when the check_draw equal to 0 which mean the situation is no empty block
					draw++;
					break;
				}

			}
			if (playerO_win != 0 || playerX_win != 0 || draw == 1)//break the second loop
				break;
		}
		if (playerO_win == 1 && playerX_win == 0) {// when the player win print the block game again and print out the win statement
			print_table(R);
			cout << "player O wins!" << endl;
			break;
		}
		else if (playerX_win == 1 && playerO_win == 0) {//the other player win the game
			print_table(R);
			cout << "player X wins!" << endl;
			break;
		}
		else if (draw == 1) {//the draw block game print
			print_table(R);
			cout << "Draw game!" << endl;
			break;
		}
		player = check_player(player);

	} while (1);//in fact it is no need for the loop statement, because most of the situation will have a break statement for out of the loop
	return 0;
}