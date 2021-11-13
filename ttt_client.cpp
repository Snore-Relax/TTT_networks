#if defined(_WIN32)
    //#include<conio.h>
#endif

// MAIN FUNCTION
// Driver program

#include "chap03.h"
#include "ttt_functions.h"
#include "ttt_functions.cpp"
#include <cstdio>
#include <iostream>

using namespace std;

/*
void drawBoard(){ //this draw the tic tac toe board

    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---+---+---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << '\n' << endl;

}
*/

int main(int argc, char *argv[]) {
    //initialize Winsock
   #if defined(_WIN32)
       WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) { 
        fprintf(stderr, "Failed to initialize.\n"); 
        return 1;
    } 
    #endif

    //4x6 = 60 by 70 cards index 


    //sudo tcpdump -w githup.pcap host github.com 
    //ifconfig -a 
  

    //Take the hostname and port number of the server it should connect to as command-line arguments. 
    if (argc < 3){

        //Note: argc contains the number of argument values available to us. Because the first argument is always our program's name, we check that there is a total of at least three arguments. The actual values themselves are stored in argv[].

        //dig facebook.com, arp -n -a

        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }

    //use value to configure a remot address for connection
    printf("Configuring remote address...\n");
    struct addrinfo hints; 
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address)){
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    // After getaddrinfo() configures the remote address, it is a good debugging measure. Use getnameinfo() to convert the address back into a string, like this:
    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address-> ai_addrlen,
            address_buffer, sizeof(address_buffer), service_buffer, 
            sizeof(service_buffer), NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);

    //creating sockets
    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family, peer_address->ai_socktype, peer_address->ai_protocol); 
    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1; 
    }

    //connect() establishes a connection to the remote server
    printf("Connecting...\n");
    if(connect(socket_peer, peer_address->ai_addr,
        peer_address->ai_addrlen)){
            fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
    }
    freeaddrinfo(peer_address);

    //Lets the user know a TCP connection has been established to the remote server.
    printf("Connected.\n");
    printf("Game will commence");
    printf("To send data, enter text followed by enter.\n");

    printf("Printing Board\n\n"); 
       // I want to draw the board here. 
            drawBoard();
  
       // game starts here...
            Game();

    // The program should now loop while checking both the terminal and socket for new data. If new data comes from the terminal, It will send it over the socket. If new data is read from the socket, it will print it out to the terminal.

    while(1){

        fd_set reads; 
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
#if !defined(_WIN32)
        FD_SET(0, &reads);
#endif
        
        struct timeval timeout;
        timeout.tv_sec = 0; 
        timeout.tv_usec = 100000;

        if(select(socket_peer+1, &reads, 0, 0, &timeout) < 0){
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        // declare a variable, fd_set reads, to store our socket set. We then zero it with FD_ZERO() and add our only socket, socket_peer.


        //after select returns, the new data is printed on the console
        if(FD_ISSET(socket_peer, &reads)){
            char read[4096];
            int bytes_recieved = recv(socket_peer, read, 4096, 0);
            if(bytes_recieved < 1){
                printf("Connection closed by peer.\n");
                break;
            }
            printf("Recieved (%d bytes): %.*s", bytes_recieved, bytes_recieved, read);

          
        }

        //After checking for new TCP data, we also need to check for terminal input:
        #if defined(_WIN32)
            if(_kbhit()){
      #else
                if(FD_ISSET(0, &reads)){
      #endif
                    char read[4096];
                    if(!fgets(read, 4096, stdin)) break;
                    printf("Sending: %s", read);
                    int bytes_sent = send(socket_peer, read, strlen(read), 0);
                    printf("Sent %d bytes.\n", bytes_sent);

                }
    }
    printf("Closing socket...\n"); 
    CLOSESOCKET(socket_peer);

    #if defined(_WIN32)
       WSACleanup();
    #endif
       printf("Finished.\n");
    return 0;
}
