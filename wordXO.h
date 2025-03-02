#ifndef WORD_X_O_H
#define WORD_X_O_H

#include "BoardGame_Classes.h"
#include <cctype>
#include <unordered_set>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class Word_Board : public Board<T> {
private:
	unordered_set<string> wordsSet;
public:
	Word_Board();
	bool update_board(int x, int y, T symbol) override;
	void display_board() override;
	bool is_win() override;
	bool is_draw() override;
	bool game_is_over() override;
	char** getBoard();
};

template <typename T>
class Word_Tic_Tac_Toe_Player : public Player<T> {
public:
	Word_Tic_Tac_Toe_Player(string name, T symbol);
	T getsymbol();
	void getmove(int& x, int& y) override;
	bool is_valid(string text, string player);
};

template <typename T>
class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
private:
	Word_Board<T>& board;
public:
	Word_Tic_Tac_Toe_Random_Player(T symbol, Word_Board<T>& board);
	void getmove(int& x, int& y) override;
	char random_symbol();
};

//============== IMPLEMENTATION ==============//

//=============Start of X O Board=============//

template <typename T>
Word_Board<T>::Word_Board() {
	this->rows = this->columns = 3;
	this->board = new T * [this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->board[i] = new T[this->columns]{ 0 };
	}

	this->n_moves = 0;

	ifstream file("dic.txt");
	if (!file.is_open()) {
		cerr << "Error: Could not open dic.txt" << endl;
		exit(1);
	}

	string word;
	while (file >> word) {
		wordsSet.insert(word);
	}
	file.close();
}

template <typename T>
bool Word_Board<T>::update_board(int x, int y, T symbol) {
	if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
		cout << "Invalid move. Cell already occupied or out of bounds." << endl;
		return false;
	}
	this->board[x][y] = symbol;
	this->n_moves++;
	return true;
}

template <typename T>
void Word_Board<T>::display_board() {
	for (int i = 0; i < this->rows; i++) {
		cout << "\n| ";
		for (int j = 0; j < this->columns; j++) {
			cout << "(" << i << "," << j << ")";
			cout << setw(2) << right << (this->board[i][j] != 0 ? this->board[i][j] : ' ') << " |";
		}
		cout << "\n-----------------------------";
	}
	cout << endl;
}

template <typename T>
bool Word_Board<T>::is_win() {
	//check rows
	string row1 = "", row2 = "", row3 = "";
	bool r1 = false, r2 = false, r3 = false;

	if (this->board[0][0] != 0 && this->board[0][1] != 0 && this->board[0][2] != 0 && !r1) {
		row1 += this->board[0][0];
		row1 += this->board[0][1];
		row1 += this->board[0][2];
		r1 = true;
		if (wordsSet.find(row1) != wordsSet.end()) {
			return true;
		}
	}
	if (this->board[1][0] != 0 && this->board[1][1] != 0 && this->board[1][2] != 0 && !r2) {
		row2 += this->board[1][0];
		row2 += this->board[1][1];
		row2 += this->board[1][2];
		r2 = true;
		if (wordsSet.find(row2) != wordsSet.end()) {
			return true;
		}
	}
	if (this->board[2][0] != 0 && this->board[2][1] != 0 && this->board[2][2] != 0 && !r3) {
		row3 += this->board[2][0];
		row3 += this->board[2][1];
		row3 += this->board[2][2];
		r3 = true;
		if (wordsSet.find(row3) != wordsSet.end()) {
			return true;
		}
	}

	//check columns
	string col1 = "", col2 = "", col3 = "";
	bool c1 = false, c2 = false, c3 = false;

	if (this->board[0][0] != 0 && this->board[1][0] != 0 && this->board[2][0] != 0 && !c1) {
		col1 += this->board[0][0];
		col1 += this->board[1][0];
		col1 += this->board[2][0];
		c1 = true;
		if (wordsSet.find(col1) != wordsSet.end()) {
			return true;
		}
	}
	if (this->board[0][1] != 0 && this->board[1][1] != 0 && this->board[2][1] != 0 && !c2) {
		col2 += this->board[0][1];
		col2 += this->board[1][1];
		col2 += this->board[2][1];
		c2 = true;
		if (wordsSet.find(col2) != wordsSet.end()) {
			return true;
		}
	}
	if (this->board[0][2] != 0 && this->board[1][2] != 0 && this->board[2][2] != 0 && !c3) {
		col3 += this->board[0][2];
		col3 += this->board[1][2];
		col3 += this->board[2][2];
		c3 = true;
		if (wordsSet.find(col3) != wordsSet.end()) {
			return true;
		}
	}

	//check diagonals
	string diag1 = "", diag2 = "";
	bool d1 = false, d2 = false;

	if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 && !d1) {
		diag1 += this->board[0][0];
		diag1 += this->board[1][1];
		diag1 += this->board[2][2];
		d1 = true;
		if (wordsSet.find(diag1) != wordsSet.end()) {
			return true;
		}
	}
	if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0 && !d2) {
		diag2 += this->board[0][2];
		diag2 += this->board[1][1];
		diag2 += this->board[2][0];
		d2 = true;
		if (wordsSet.find(diag2) != wordsSet.end()) {
			return true;
		}
	}

	return false;
}


template <typename T>
bool Word_Board<T>::is_draw() {
	return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
	return is_win() || is_draw();
}

template <typename T>
char** Word_Board<T>::getBoard() {
	return this->board;
}
//==============End of X O Board==============//


//======Start of Word_Tic_Tac_Toe_Player======//

template <typename T>
Word_Tic_Tac_Toe_Player<T>::Word_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
T Word_Tic_Tac_Toe_Player<T>::getsymbol() {
	//override get symbol function to return new symbol with each turn as to allow
	//player to choose a different character each turn
	string choice = "";
	cout << "Player '" << Player<T>::getname() << "' please enter a character of your choice (a - z): ";
	getline(cin >> ws, choice);

	while (!is_valid(choice, Player<T>::getname())) {
		getline(cin >> ws, choice);
	}

	this->symbol = toupper(choice[0]);
	return this->symbol;
}

template <typename T>
void Word_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
	string inputX, inputY;
	do {
		cout << "Player '" << Player<T>::getname() << "' enter move (x y) between 0 and 2 separated by spaces: ";
		cin >> inputX >> inputY;

		if (inputX[0] < '0' || inputX[0] > '2' || inputY[0] < '0' || inputY[0] > '2') {
			cout << "Invalid move. Try again." << endl;
		}
	} while (inputX[0] < '0' || inputX[0] > '2' || inputY[0] < '0' || inputY[0] > '2');

	x = inputX[0] - '0';
	y = inputY[0] - '0';

	getsymbol();
}

template <typename T>
bool Word_Tic_Tac_Toe_Player<T>::is_valid(string text, string player) {
	if (text.length() != 1) {
		cout << "\nPlayer '" << player << "' Please enter a single character from 'A' to 'Z': ";
		return false;
	}
	string upper_text;
	upper_text = toupper(text[0]);

	if (upper_text[0] < 'A' || upper_text[0] > 'Z') {
		cout << "\nPlease enter a character from 'a' to 'z': ";
		return false;
	}

	return true;
}

//=======End of Word_Tic_Tac_Toe_Player=======//


//===Start of Word_Tic_Tac_Toe_Random_Player===//

template <typename T>
Word_Tic_Tac_Toe_Random_Player<T>::Word_Tic_Tac_Toe_Random_Player(T symbol, Word_Board<T>& board) : RandomPlayer<T>(symbol), board(board) {
	this->symbol = random_symbol();
}

template <typename T>
void Word_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
	do {
		x = rand() % 3;
		y = rand() % 3;
	} while (board.getBoard()[x][y] != 0);

	this->symbol = random_symbol();
}

template <typename T>
char Word_Tic_Tac_Toe_Random_Player<T>::random_symbol() {
	return 'A' + (rand() % 26);
}


//====End of Word_Tic_Tac_Toe_Random_Player====//


#endif
