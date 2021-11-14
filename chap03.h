#if defined(_WIN32)

#ifndef _WIN32_WINNIT  //windows portion 
#define _WIN32_WINNIT 0x600
#endif

#include <winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else

//required for sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif

#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int 
#define GETSOCKETERRNO() (errno)
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#define SA struct sockaddr

#define MAX 80

#define PORT 8080
