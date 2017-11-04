#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>


int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0;
    char key='a';
    int numbytes = 0;
    int rev = 0;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8700);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};

    // To select different command to Send
while(1){


	printf("To press a key to select a different command : p -> POWER_ON, s -> SOURCE_AV, c -> Close Connection \n");
	key = getchar();
	printf("Input key = %c \n", key);

	switch(key){
        case 'p':
            printf("Send Power Key\n");
			if ( (numbytes = send(sockfd, "POWER_ON", strlen("POWER_ON"),0) )== -1 ){
				// perror("send");
				exit(1);
			}
		break;

		case 's':
			if ( (numbytes = send(sockfd, "SOURCE_AV", strlen("SOURCE_AV"),0) )== -1 ){
				// perror("send");
				exit(1);
			}
        break;
        
        case 'c':
        if ( (numbytes = send(sockfd, "CLOSE_CONNECT", strlen("CLOSE_CONNECT"),0) )== -1 ){
            // perror("send");
            exit(1);
        }
        printf("close Socket\n");
        close(sockfd);
        return 0;

        break;

		default:
			if ( (numbytes = send(sockfd, "POWER_ON", strlen("POWER_ON"),0) )== -1 ){
				// perror("send");
				exit(1);
			}
		break;
    }
    
    // send(sockfd,message,sizeof(message),0);
    rev = recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
    printf("Client received message = %s, rev = %d\n",receiveMessage,rev);

    getchar();
}

    printf("close Socket\n");
    close(sockfd);
    return 0;
}