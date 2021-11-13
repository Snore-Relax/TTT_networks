#include "chap03.h"
#include "ttt_functions.h"


int main() {

#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif


    // This part listens on port 8080. If you want to listen for connections on IPv6, then just change AF_INET to AF_INET6.

    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);


    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    //bind() our socket to the local address and have it enter a listening state

    printf("Binding socket to local address...\n");
    if (bind(socket_listen,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    // define an fd_set structure that stores all of the active sockets. For now, we add only our listening socket to the set. Because it's the only socket, it must also be the largest, so we set max_socket = socket_listen too.

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    // set up our call to select()

    printf("Waiting for connections...\n");

    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        // This works by first copying our fd_set master into reads. Recall that select() modifies the set given to it. If we didn't copy master, we would lose its data.

        // We now loop through each possible socket and see whether it was flagged by select() as being ready. If a socket, X, was flagged by select(), then FD_ISSET(X, &reads) is true. Socket descriptors are positive integers, so we can try every possible socket descriptor up to max_socket. The basic structure of our loop is as follows

        SOCKET i;
        for(i = 1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {
                //handle socket

        //Remember, FD_ISSET() is only true for sockets that are ready to be read. In the case of socket_listen, this means that a new connection is ready to be established with accept(). For all other sockets, it means that data is ready to be read with recv(). We should first determine whether the current socket is the listening one or not. If it is, we call accept().

                if (i == socket_listen) {
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(socket_listen,
                            (struct sockaddr*) &client_address,
                            &client_len);

                    if (!ISVALIDSOCKET(socket_client)) {
                        fprintf(stderr, "accept() failed. (%d)\n",
                                GETSOCKETERRNO());
                        return 1;
                    }

                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;

                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_address,
                            client_len,
                            address_buffer, sizeof(address_buffer), 0, 0,
                            NI_NUMERICHOST);
                    printf("New connection from %s\n", address_buffer);

                } 
                // If the socket i is not socket_listen, then it is instead a request for an established connection. In this case, we need to read it with recv(), convert it into uppercase using the built-in toupper() function

                 else {
                    char read[1024];
                    int bytes_received = recv(i, read, 1024, 0);
                    if (bytes_received < 1) {
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;
                    }

                    printf("Receiving from client\n%.1024s\n", read);
                    memset(read, 0, 1024);
                    
                    
                }
               

            } //if FD_ISSET
        } //for i to max_socket
    } //while(1)



    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

#if defined(_WIN32)
    WSACleanup();
#endif


    printf("Finished.\n");

    return 0;
}

//gcc tcp_client.c -o tcp_client
// tcp_client 127.0.0.1 8080
/*
GET / HTTP/1.1 Host: example.com
*/