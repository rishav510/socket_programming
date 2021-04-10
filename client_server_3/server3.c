#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 32
#define MAXPENDING 5

/*
1. Create server socket
2. Assign server address and client address using the sockaddr_in struct
3. Bind the socket to the port
4. Listen for requests
5. Accept connections by opening new sockets (using accept())
6. Open connection with client
7. Receive data from client
8. Send data to client

*/
int main()
{
    //1. create a socket
    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket < 0)
    {
        printf("Could not create server side socket");
        exit(1);
    }
    printf("Server socket created\n");

    //2.assign server address and client address  using sockaddr_in struct

    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    printf("Server address is assigned\n");

    //bind server socket to the port
    int temp = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(temp < 0)
    {
        printf("Error while binding\n");
        exit(1);
    }   
    printf("Binding successful...\n");
    int temp1 = listen(serverSocket, MAXPENDING);
    if(temp1 < 0)
    {
        printf("Error in listening...\n");
        exit(1);
    }
    printf("Now listening...\n");
    char msg[BUFFERSIZE];
    struct sockaddr_in clientAddr[3];
    
    int clientLength = sizeof(clientAddr[0]);
    int i = 3;
    int clientSocket[3];
    while(i --)
    {
        clientSocket[i] = accept(serverSocket, (struct sockAddr *)&clientAddr, &clientLength);
    
        if(clientSocket[i] < 0)
        {
            printf("Error in client socket");
            exit(1);
            
        }
        printf("Handling client %s\n", inet_ntoa(clientAddr[i].sin_addr));
    }
    i = 0;
    while(i < 3)
    {
        
        int temp2 = recv(clientSocket[i], msg, BUFFERSIZE, 0);
        if(temp2 < 0)
        {
            printf("Error in receiving message");
            exit(1);
        }
        printf("%s\n",msg);
        printf("Enter message for the client\n");
        gets(msg);
        int bytesSent = send(clientSocket[i], msg, strlen(msg),0);
        if(bytesSent != strlen(msg)){
            printf("Error sending message");
            exit(1);
        }
        i++;
    }

    close(serverSocket);
    close(clientSocket);
    return 0;
}