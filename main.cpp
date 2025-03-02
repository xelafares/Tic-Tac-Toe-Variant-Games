#include <iostream>
#include <string>
#include "pyramidXO.h"
#include "wordXO.h"
#include "ultimateXO.h"

void getNameAndType(std::string& player1, std::string& player2, int& type1 , int& type2)
{
    std::string type1String, type2String;
    std::cout << "Choose Player 1 Name: ";
    std::cin >> player1;

    do {
        std::cout << "Choose Player 1 type: \n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        std::getline(std::cin >> std::ws, type1String);
    } while(type1String.length() > 1 || type1String[0] > '2' || type1String[0] < '1');
    type1 = type1String[0] - '0';

    std::cout << "Choose Player 2 Name: ";
    std::cin >> player2;

    do {
        std::cout << "Choose Player 2 type: \n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        std::getline(std::cin >> std::ws, type2String);
    } while(type2String.length() > 1 || type2String[0] > '2' || type2String[0] < '1');
    type2 = type2String[0] - '0';
}

void ultimateXO(){
    Player<char>* players[2];
    Board<char>* B = new ultimate_board<char>();
    string player1Name, player2Name;
    int type1,type2;
    std::cout << "---------------------------------\n";
    std::cout << "|    Welcome to Ultimate XO     |\n";
    std::cout << "---------------------------------\n";
    getNameAndType(player1Name,player2Name, type1, type2);
    switch(type1) {
        case 1:
            players[0] = new ultimate_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new ultimate_Random<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }
    switch(type2) {
        case 1:
            players[1] = new ultimate_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new ultimate_Random<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }
    players[0]->setBoard(B);
    players[1]->setBoard(B);
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    delete B;
    for (auto & player : players) {
        delete player;
    }
}

void pyramidtTicTacToe() {
    Player<char>* players[2];
    PyramidBoard<char>* B = new PyramidBoard<char>();
    string player1Name, player2Name;
    int type1, type2;
    std::cout << "-------------------------------------\n";
    std::cout << "|  Welcome to Pyramid Tic Tac Toe   |\n";
    std::cout << "-------------------------------------\n";

    getNameAndType(player1Name, player2Name, type1, type2);

    switch (type1) {
    case 1:
        players[0] = new Pyramid_X_O_Player<char>(player1Name, 'X');
        break;
    case 2:
        players[0] = new Pyramid_X_O_Random_Player<char>('X', *B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }
    switch (type2) {
    case 1:
        players[1] = new Pyramid_X_O_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Pyramid_X_O_Random_Player<char>('O', *B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    GameManager<char> game(B, players);
    game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void WordTicTacToe() {
    Player<char>* players[2];
    Word_Board<char>* B = new Word_Board<char>();
    string player1Name, player2Name;
    int type1, type2;

    std::cout << "------------------------------------\n";
    std::cout << "|    Welcome to Word Tic TacToe    |\n";
    std::cout << "------------------------------------\n";
    getNameAndType(player1Name, player2Name, type1, type2);

    switch (type1) {
    case 1:
        players[0] = new Word_Tic_Tac_Toe_Player<char>(player1Name, 'X');
        break;
    case 2:
        players[0] = new Word_Tic_Tac_Toe_Random_Player<char>('X', *B);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    switch (type2) {
    case 1:
        players[1] = new Word_Tic_Tac_Toe_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Word_Tic_Tac_Toe_Random_Player<char>('O', *B);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    GameManager<char> game(B, players);
    game.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

int main() {
    std::cout << "-------------------------\n";
    std::cout << "| Welcome to Mini Games |\n";
    std::cout << "-------------------------\n";
    std::string choiceString;
    int choice;
    while (true)
    {
        std::cout << "Choose one of the following games to start playing or exit the program\n";
        std::cout << "1. Pyramid Tic Tac Toe\n";
        std::cout << "2. Word Tic Tac Toe\n";
        std::cout << "3. Ultimate Tic Tac Toe\n";
        std::cout << "0. Exit\n";

        while (true)
        {
            std::cout << "Enter Your choice: ";
            std::getline(std::cin >> std::ws, choiceString);
            if(choiceString.length() != 1 || choiceString[0] > '3' || choiceString[0] < '0')
            {
                std::cout << "Invalid choice\n";
                continue;
            }
            break;
        }

        choice = choiceString[0] - '0';

        switch (choice) {
            case 0:
                return 0;
            case 1:
                pyramidtTicTacToe();
                break;
            case 2:
                WordTicTacToe();
                break;
            case 3:
                ultimateXO();
                break;
            default:
                return 0;
        }
    }
}
