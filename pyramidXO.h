#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>
#include <iomanip>
#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H
using namespace std;

template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    char** getBoard();
    bool check_move(int x, int y);
};

template <typename T>
class Pyramid_X_O_Player : public Player<T> {
public:
    Pyramid_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class Pyramid_X_O_Random_Player : public RandomPlayer<T> {
private:
    PyramidBoard<T>& board;
public:
    Pyramid_X_O_Random_Player(T symbol, PyramidBoard<T>& board);
    void getmove(int& x, int& y) override;
};


//============== IMPLEMENTATION ==============//

//===========Start of Pyramid Board===========//

template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char* [this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns] {0};
    }

    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (this->board[x][y] != 0) {
        cout << "Please select a valid empty slot" << endl;
    }

    if (!(x < 0 || x >= this->rows || y < 0 || y > this->columns)
        && (this->board[x][y] == 0 || symbol == 0) && check_move(x, y)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        return true;
    }

    return false;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {

        if (i == 0) {
            cout << setw(18) << ' ' << '|';
            cout << "(" << i << ',' << 0 << ')';
            cout << setw(2) << right << (this->board[i][0] != 0 ? this->board[i][0] : ' ') << " |";
            cout << endl;
        }

        else if (i == 1) {
            cout << setw(9) << ' ' << '|';

            for (int j = 0; j < 3; j++) {
                cout << "(" << i << ',' << j << ')';
                cout << setw(2) << right << (this->board[i][j] != 0 ? this->board[i][j] : ' ') << " |";
            }
            cout << endl;
        }

        else {
            cout << '|';
            for (int j = 0; j < 5; j++) {
                cout << "(" << i << ',' << j << ')';
                cout << setw(2) << right << (this->board[i][j] != 0 ? this->board[i][j] : ' ') << " |";
            }
            cout << endl;
        }
    }
}

template <typename T>
bool PyramidBoard<T>::is_win() {
    //Check rows and columns for winners
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2] && this->board[1][0] != 0) ||
        (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != 0) ||
        (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0) ||
        (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0)) {
        return true;
    }

    //Check diagonals for winners
    if ((this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
char** PyramidBoard<T>::getBoard() {
    return this->board;
}

template <typename T>
bool PyramidBoard<T>::check_move(int x, int y) {
    if ((x == 0 && y == 0) || (x == 1 && y >= 0 && y <= 2) || (x == 2 && y >= 0 && y <= 4)) {
        return true;
    }

    return false;
}

//=========== Implementation of Pyramid_X_O_Player ===========

template <typename T>
Pyramid_X_O_Player<T>::Pyramid_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_X_O_Player<T>::getmove(int& x, int& y) {
    string choicex, choicey;

    do {
        cout << "Player '" << Player<T>::getname() << "' enter move (x y) between (0-2, 0-4) separated by spaces: ";
        cin >> choicex >> choicey;

        if (choicex.length() == 1 && choicey.length() == 1 && isdigit(choicex[0]) && isdigit(choicey[0])) {
            x = choicex[0] - '0';
            y = choicey[0] - '0';

            if ((x == 0 && y == 0) || (x == 1 && y >= 0 && y <= 2) || (x == 2 && y >= 0 && y <= 4)) {
                break;
            }
            else {
                cout << "Invalid move. Please try again." << endl;
            }
        }
        else {
            cout << "Invalid input format. Please enter two digits separated by a space." << endl;
        }
    } while (true);
}


//=========== Implementation of Pyramid_X_O_Random_Player ===========

template <typename T>
Pyramid_X_O_Random_Player<T>::Pyramid_X_O_Random_Player(T symbol, PyramidBoard<T>& board) : RandomPlayer<T>(symbol), board(board) {}

template <typename T>
void Pyramid_X_O_Random_Player<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 3;
        if (x == 0) {
            y = 0;
        }
        else if (x == 1) {
            y = rand() % 3;
        }
        else {
            y = rand() % 5;
        }
    } while (board.getBoard()[x][y] != 0);
}

#endif
