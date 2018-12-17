#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
    ssize_t sent_value = 0;
    ssize_t read1_count, read2_count, read3_count = 0;
    int sock;
    int close(int fd);
    int n;
    int counter = 0;
    char send[2048];
    char receive[2048];
	char receiveB[2048];
    char receiveA[2048];
char receiveC[2048];
    struct sockaddr_in servaddr;
    int count=1;
    if(argc==1)
        printf("No Extra Command Line Argument Passed Other Than Program Name\n");
    if(argc>=2)
    {
        int tp = argc-1;
        //printf("%d\n",tp);
        //printf("Following Are The Command Line Arguments Passed-\n");
        for(counter=1;counter<argc;counter++)
            printf("%s\n",argv[counter]);
          
    }
 
    sock=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(25811);
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 
    connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr));
    printf("The client is up and running\n");

    while(1) {

    if(strncmp(argv[1],"search",5) == 0)
    {

	int read1Cnt, read2Cnt, read3Cnt = 0;        
	bzero(send, 2048);
        bzero(receive, 2048);
        bzero(receiveA, 2048);
	bzero(receiveB, 2048);
	bzero(receiveC, 2048);
        strcpy(send,argv[1]);
	strcat(send," ");
	strcat(send,argv[2]);
	
        //while (write(sock,send,strlen(send)+1) <= 0);
	write(sock, send, strlen(send));
        //read(sock,receive,2048);
        //printf("%s\n",receive);
        printf("The client sent %s to the AWS\n",send);
	//printf("%d\n",strlen(receiveA));
        sleep(5);
        while(strlen(receiveA) <= 0){
          read(sock,receiveA,2048);
        }
	//printf("%s\n", receiveA);
	//read(sock,receiveB,2048);
        //printf("%d %s\n",read2Cnt, receiveB);
	//read(sock,receiveC,2048);
        //printf("%d %s\n",read3Cnt, receiveC);
        

        //count--;
     }
     else if(strncmp(argv[1],"prefix",6) == 0) {

        bzero(send, 2048);
        bzero(receive, 2048);
        bzero(receiveA, 2048);
	bzero(receiveB, 2048);
	bzero(receiveC, 2048);
        strcpy(send,argv[1]);
	strcat(send," ");
	strcat(send,argv[2]);
        write(sock,send,strlen(send)+1);
        printf("The client sent %s to the AWS\n",send);
        sleep(20);
        read(sock,receive,2048);
        printf("The client received %s\n from the AWS",receive);
     } else {
       printf("\n Unexpected argument %s received", argv[1]);
    }
   }
    //close(sock);
 //return 0;
}
