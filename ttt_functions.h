#ifndef TTTBoard_H
#define TTTBoard_H



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


#endif // TTTBoard_HPP