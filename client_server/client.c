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

    //fill in the fields in the sockaddr_in struct
    serverAddr.sin_addr.s_addr = inet_addr("192.168.29.133");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    
    printf("Address assigned\n");

    //establish connection
    int c = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    printf("%d\n",c);
    if(c)
    {
        printf("Error while establishing connection");
        exit(1);
    }
    
    //send some data
    
    //declare msg buffer variable
    char msg[BUFSIZE];
    //send message using send()
    printf("Enter the message to be sent to the server\n");
    gets(msg);

    int bytesSent = send(sock, msg, sizeof(msg), 0);
    if(bytesSent < 0) // error condition
    {
        printf("Error while sending bytes");
        exit(1);
    }
    printf("Bytes sent\n");

    //receive bytes
    char recvBuffer[BUFSIZE];
    int bytesRecvd = recv(sock, recvBuffer, BUFSIZE -1, 0);
    if(bytesRecvd < 0) // error condition
    {
        printf("Error while receiving bytes");
        exit(1);
    }
    printf("Bytes received from server\n");
    printf("Message from server: %s\n", recvBuffer);

    close(sock);
    return 0;

}