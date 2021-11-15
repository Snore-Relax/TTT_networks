#include "chap03.h"
#include "methods.h"
#include <ctype.h>
#include <iostream>

using namespace std;

void drawBoard(){ //this draw the tic tac toe board

    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << '\n' << endl;

}


void linkServer(int sockfd)
{
	    char msg[MAX];
        int n;
    
		bzero(msg, sizeof(msg));
		read(sockfd, msg, sizeof(msg));
        n = 0;
        while ((msg[n++] = getchar()) != '\n')
            ;
		
		bzero(msg, sizeof(msg));
		read(sockfd, msg, sizeof(msg));
		printf("Sending to server : %s", msg);
		if ((strncmp(msg, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			//break;
		}
    
	
}



void Game(int sockfd){

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

    int i = 0;

    while(i <= 9){
        i++;

    char msg[10];
    int pos;
    sockfd = atoi(msg);
    sockfd = pos;
         
        if (currentP == 1){
            cout << "It is Player 1's turn. Select a number: ";
            cin >> pos;
            // client function.
            linkServer(pos);
            printf("Player will place a marker on %d.\n", pos);

        }

        else if (currentP == 2) {
            cout << "It is computer's turn. Selecting position: ";
            pos = (rand() % 9) + 1;
            // client function. 
            linkServer(pos);
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
            cout << " * Player 1 has won! * \n\n";
            break;  
        }
        
        else if(scanWin() == 'O' ){
            cout << " * Computer has won! * \n\n";
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


int main(){
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    
    Game(sockfd);
  

    // close the socket
   //close(sockfd);
}
