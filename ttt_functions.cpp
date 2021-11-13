#include "chap03.h"
#include "ttt_functions.h"
#include <iostream>

using namespace std;



void drawBoard(){ //this draw the tic tac toe board

    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << '\n' << endl;

}

void switchSymbol(){
    //changes the symbol
    if(XO == 'X'){
        XO = 'O';
    } else 
        XO = 'X';

    //changes player
    if(currentP == 1) {
        currentP = computer;
    }
    else currentP = 1;

}

bool userInput(int pos){
 int row = pos/3;
 int column; 

 if(pos % 3 == 0){
     row = row - 1;
     column = 2;
 }

 else column = (pos % 3) - 1;
    
    if(board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = XO;
        return true;
    }
    else return false;
}

int scanWin(){

    //X marker

    // row
    if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
        return 'X';

    if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
        return 'X';

    if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
        return 'X';

    // column
    if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
        return 'X';
    
    if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
        return 'X';

    if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
        return 'X';

    //diagonal 
    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
        return 'X';

    if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')
        return 'X';

/*
00 01 02 
10 11 12
20 21 22
*/


    /**************-- Hard code win scan --**************/

    //O marker 

     // row
    if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
        return 'O';

    if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
        return 'O';

    if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
        return 'O';

    // column
    if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
        return 'O';
    
    if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
        return 'O';

    if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
        return 'O';

    //diagonal 
    if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
        return 'O';

    if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O')
        return 'O';


/*
00 01 02 
10 11 12
20 21 22
*/

    return 0;
}

//client
void Game(){
    cout << "Tic tac toe ver2. \n";
    cout <<"Directions: Select a number to place your marker on the board.\n\n";

    cout << "Player 1 choose your symbol(X/O): ";
    cin >> player;

    currentP = 1;
    XO = player; 

    if (player != 'X' && player != 'O'){

        printf("Invalid symbol try again. You can only use X or O: ");
        cin >> XO;

    }
         
    cout << "\n";

    drawBoard();

    int pos;

    int i = 0;

    while(i <= 9){
        i++;

        if (currentP == 1){
            cout << "It is Player 1's turn. Select a number: ";
            cin >> pos;
            printf("Player will place a marker on %d.\n", pos);

        }

        else if (currentP == 2) {
            cout << "It is computer's turn. Selecting position: ";
            pos = (rand() % 9) + 1;
            printf("Computer will place a marker on %d.\n", pos);
    
        }

        if(pos < 1 || pos > 9){ 
            cout << "\nUser input is invalid; Try again.\n";
            i--;
            continue;
        }

        if(!userInput(pos)){
            cout << "\nPosition is currently in use, Select a different slot\n";
            i--;
            continue;
        }
            cout << "\n";
            drawBoard();


        if(scanWin() == 'X' ){
            cout << " *** Player 1 has won! *** \n\n";
            break;  
        }
        
        else if(scanWin() == 'O' ){
            cout << " *** Computer has won! *** \n\n";
            break;
        }

        else if (scanWin() == 0 && i == 9){ 
            printf(" --- It is a draw! ---\n\n");
            break;
        }   

        cout << "\n";
        switchSymbol();

    }   

}
