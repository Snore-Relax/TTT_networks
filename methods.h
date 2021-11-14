

#define computer 2;

char player; // user
int currentP; // current player
char XO; // user marker

char board[3][3]={'1', '2', '3', '4', '5', '6', '7', '8', '9'}; 


    void drawBoard();
    void switchSymbol();
    bool userInput(int pos);
    int scanWin();
    void Game();



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
