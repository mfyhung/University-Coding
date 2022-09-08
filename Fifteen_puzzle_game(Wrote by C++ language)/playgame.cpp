#include <iostream>
#include "FifteenPuzzle.h"
using namespace std;

int main() {
	int seed, step = 0;
	char move_char = 'a';
	bool move = true;
	while (1) {
		cout << "Enter Seed: ";
		cin >> seed;
		if (seed < 0) {
			cout << "Invalid. Try again!" << endl;
			continue;
		}
		else
			break;
	}
	FifteenPuzzle game(seed);
	while (game.getSteps()<200) {
		game.print();
		cout << "Steps: " << game.getSteps() << endl;
		while (1) {
			cout << "Move[IMJK]: ";
			cin >> move_char;
			move = game.move(move_char);
			if (!move&&!(move_char == 'I' || move_char == 'i' || move_char == 'J' || move_char == 'j' || move_char == 'K' || move_char == 'k' || move_char == 'M' || move_char == 'm')) {
				cout << "Invalid. Try again!" << endl;
				continue;
			}
			else
				break;
		}
		if (game.isSolved()) {
			game.print();
			cout << "Steps: " << game.getSteps() << endl;
			cout << "You finished in " << game.getSteps() << " steps.";
			return 0;
		}
	}
	game.print();
	cout << "Steps: " << game.getSteps() << endl;
	cout << "¡§You cannot finish in 200 steps" << endl;
	return 0;
}