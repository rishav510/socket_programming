#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZE 32

/*
1. Create TCP Socket using socket()
2. Establish connection to server using connect()
3. Communicate using send() and recv()
4. Close connection using close()
*/
int main()
{
    // create tcp socket using socket()
    // int socket(protocol_family, socket_type, protocol_type)
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 

    //check if socket has been created, if not it returns -1

    if(sock < 0)
    {
        printf("Error generating socket");
        exit(-1);
    }
    printf("Client socket created ...\n");

    //declare the socket address struct. 
    //we need to declare this here in order to pass to connect() later on
    //Note: only server socket address is required. Client side socket information is not required by either node
    struct sockaddr_in serverAddr;
    
    //set all bytes in the socket address struct to zero

    memset(&serverAddr, 0, sizeof(serverAddr));

    //now set the different fields of the socket in struct i.e. family, port and address
    
}