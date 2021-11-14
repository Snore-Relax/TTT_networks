#include "chap03.h"
#include "methods.h"
#define SA struct sockaddr
   
// Function designed for chat between client and server.
void linkClient(int sockfd)
{
    char msg[MAX];
    int n;
    // infinite loop for chat
    while(true) {
        bzero(msg, MAX);
   
        // read the message from client and copy it in buffer
        read(sockfd, msg, sizeof(msg));
        // print buffer which contains the client contents
        //printf("From client: %s\t To client : ", msg);
        printf("From client: %s\t", msg);
        bzero(msg, MAX);
        n = 0;
        // copy server message in the buffer
        while ((msg[n++] = getchar()) != '\n')
        ;
   
        // and send that buffer to client
        //write(sockfd, msg, sizeof(msg));
   
        // if msg contains "Exit" then server exit and chat ended.
        
    }
}
   
// Driver function

int main()
{
    unsigned int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    linkClient(connfd);
   
    // After chatting close the socket
    //close(sockfd);
}
