#ifndef GAMES_ULTIMATEXO_H
#define GAMES_ULTIMATEXO_H
#include "BoardGame_Classes.h"
#include <vector>
#include <set>
template<typename T>
class ultimate_board : public Board<T>{
private:
    T** status;
    set<int>played;
    bool end;
public:
    ultimate_board();
    bool is_win() override;
    bool is_draw() override;
    bool update_board(int, int, T) override;
    void display_board() override;
    bool game_is_over() override;
    void display_status();
    int board_finder(int&,int&);
    bool check_win(int&,int&);
    bool check_draw(int&,int&);
    ~ultimate_board();
};

template<typename T>
class ultimate_Player: public Player<T>{
public:
    ultimate_Player(const string&,T);
    void getmove(int&,int&) override;
};

template<typename T>
class ultimate_Random: public RandomPlayer<T>{
public:
    ultimate_Random(T symbol);
    void getmove(int&,int&) override;
};


//---------------- IMPLEMENTATION----------------\\
#include <string>
template<typename T>
ultimate_board<T>::ultimate_board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->status = new char*[3];
    for (int i = 0; i < 3; i++) {
        this->status[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            this->status[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->end = false;
}

template<typename T>
bool ultimate_board<T>::update_board(int x, int y, T symbol) {
    if (x == y && x == -1){
        this->end = true;
        return true;
    }
    --x;--y;
    int b = board_finder(x,y);
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0) && !played.count(b)) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        if(check_win(x,y)){
            status[x/3][y/3] = toupper(symbol);
            played.insert(b);
        }
        else if(check_draw(x,y)){
            status[x/3][y/3] = 'd';
            played.insert(b);
        }
        cout << "\x1b[24A";
    }
    else return false;
    return true;
}

template<typename T>
void ultimate_board<T>::display_board() {
    cout << "  || ";
    for(int i = 0;i < 9;++i){
        cout << i+1 << " | ";
        if((i+1)%3 == 0 && i != 8) cout << "   " << "| ";
    }
    cout << '\n' << string(55,'-') << '\n';
    for(int i = 0; i < this->rows;++i){
        cout << i + 1 << " || ";
        for(int j = 0; j < this->columns;++j){
            cout << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " | ";
            if((j+1)%3 == 0 && j != 8)cout << "   " << "| ";
        }
        cout << '\n';
        if((i+1)%3 == 0) cout << string(55,'-') << '\n';
    }
    this->display_status();
}

template<typename T>
void ultimate_board<T>::display_status() {
    cout << "\n=== STATUS BOARD ===\n";
    cout << string(9,'-') << '\n';
    for(int i = 0; i < 3;++i){
        cout << '|';
        for(int j = 0; j < 3;++j){
            cout << (this->status[i][j] == 0 ? ' ' : this->status[i][j]) << '|';
        }
        cout <<'\n' <<string(9,'-') <<'\n';

    }
    cout << "=====================\n";
}

template<typename T>
int ultimate_board<T>::board_finder(int& x, int& y) {
    int xb = x/3;
    int yb = y/3;
    return (xb*3+yb+1);
}

template<typename T>
bool ultimate_board<T>::is_win() {
    // Check rows and columns of status board
    for (int i = 0; i < 3; i++) {
        if ((this->status[i][0] == this->status[i][1] && this->status[i][1] == this->status[i][2] && this->status[i][0] != 0) ||
            (this->status[0][i] == this->status[1][i] && this->status[1][i] == this->status[2][i] && this->status[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals of status board
    if ((this->status[0][0] == this->status[1][1] && this->status[1][1] == this->status[2][2] && this->status[0][0] != 0) ||
        (this->status[0][2] == this->status[1][1] && this->status[1][1] == this->status[2][0] && this->status[0][2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool ultimate_board<T>::is_draw() {
    //if all moves in the main board is played
    //and there's no win in the status board
    //game is a draw
    return (this->played.size() == 9 && !is_win());
}

template<typename T>
bool ultimate_board<T>::game_is_over() {
    return (is_win() || is_draw() || this->end);
}

template<typename T>
bool ultimate_board<T>::check_win(int& x, int& y) {
    //Adjust x and y to be on the top left corner of the sub board
    int xc = (x / 3) * 3;
    int yc = (y / 3) * 3;
    //check rows and colums of the given subboard index for a win
    for (int i = 0; i < 3; i++) {
        if ((this->board[xc + i][yc] == this->board[xc + i][yc + 1] && this->board[xc + i][yc + 1] == this->board[xc + i][yc + 2] && this->board[xc + i][yc] != 0) ||
            (this->board[xc][yc + i] == this->board[xc + 1][yc + i] && this->board[xc + 1][yc + i] == this->board[xc + 2][yc + i] && this->board[xc][yc + i] != 0)) {

            return true;
        }
    }

    //check diagonals of the given subboard index for a win
    if ((this->board[xc][yc] == this->board[xc + 1][yc + 1] && this->board[xc + 1][yc + 1] == this->board[xc + 2][yc + 2] && this->board[xc][yc] != 0) ||
        (this->board[xc][yc + 2] == this->board[xc + 1][yc + 1] && this->board[xc + 1][yc + 1] == this->board[xc + 2][yc] && this->board[xc][yc + 2] != 0)) {

        return true;
    }

    return false;
}

template<typename T>
bool ultimate_board<T>::check_draw(int& x, int& y) {
    //Adjust x and y to be on the top left corner of the sub board
    int xc = (x / 3) * 3;
    int yc = (y / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[xc + i][yc + j] == 0) {
                return false;
            }
        }
    }
    
    return !check_win(x, y);
}

template<typename T>
ultimate_board<T>::~ultimate_board() {
    for (int i = 0; i < this->rows; ++i) {
        delete [] this->board[i];
    }
    delete [] this->board;
    for (int i = 0; i < 3; ++i) {
        delete [] this->status[i];
    }
    delete[] this->status;
}
//---------------------------------------------
template<typename T>
ultimate_Player<T>::ultimate_Player(const string& name , T symbol) : Player<T>(name,symbol){}

template<typename T>
void ultimate_Player<T>::getmove(int& x, int& y) {
    if(this->boardPtr->game_is_over()) return;
    string choice;
    while (choice.size() != 3 || !isdigit(choice[0]) || !isdigit(choice[2])|| isdigit(choice[1])) {
        cout << "enter 'return' to return to menu\n";
        cout << "Enter your move as two numbers \"row column\", separated by a space: ";
        getline(cin, choice);
        cout << "\x1b[1A";
        cout << "\x1b[K";
        cout << "\x1b[1A";
        cout << "\x1b[K";
        if(choice == "return"){
            x = -1;
            y = -1;
            return;
        }
    }
    x = static_cast<int>(choice[0]) - '0';
    y = static_cast<int>(choice[2]) - '0';
}
//---------------------------------------------
template<typename T>
ultimate_Random<T>::ultimate_Random(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(NULL)));
}

template<typename T>
void ultimate_Random<T>::getmove(int &x, int &y) {
    if(this->boardPtr->game_is_over()) return;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif
