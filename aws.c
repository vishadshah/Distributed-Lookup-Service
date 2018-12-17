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

void die(char  *s )
{
  perror(s);
  exit(1);
}

int count_newlines( char *s)
{
  int count_lines = 0;
  for (int i = 0; i<strlen(s); i++){
     if(s[i] == '\n') count_lines++;
  }
  return count_lines;
 
}

int main()
{
    int count=1;
    char str[200];
    int listener;
    int command;
  char search[2048]="search";
    char prefix[2048]="prefix";
   char *tock;
   char *Word;
    
    struct sockaddr_in servaddr;

//all for udp

    struct sockaddr_in servaddr_udp;
    struct sockaddr_in servaddr_udp1;
    struct sockaddr_in servaddr_udp2;
    struct sockaddr_in servaddr_udp3;
    int count_udp=0;
    int i;
    int sock_udp;
    int slen_udp=sizeof(servaddr_udp);
    char buffer_udp[8192];
    char buffer_udp1[2048];
    char buffer_udp2[2048];
    char buffer_udp3[2048];
    char message_udp[2048];

    char buffer_udp1cpy[2048];
    char buffer_udp2cpy[2048];
    char buffer_udp3cpy[2048];

    bzero(&servaddr,sizeof(servaddr));
    listener = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(25811);
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    bind(listener, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("The AWS is up and running\n");
 
    listen(listener, 10);
 
    command = accept(listener, (struct sockaddr*) NULL, NULL);
 // making all socket for udp


    memset((char *) &servaddr_udp, 0, sizeof(servaddr_udp));
    servaddr_udp.sin_family = AF_INET;
    servaddr_udp.sin_port = htons(24811);
    servaddr_udp.sin_addr.s_addr = INADDR_ANY;

    memset((char *) &servaddr_udp, 0, sizeof(servaddr_udp1));
    servaddr_udp1.sin_family = AF_INET;
    servaddr_udp1.sin_port = htons(21811);
    servaddr_udp1.sin_addr.s_addr = INADDR_ANY;
    
    memset((char *) &servaddr_udp2, 0, sizeof(servaddr_udp2));
    servaddr_udp2.sin_family = AF_INET;
    servaddr_udp2.sin_port = htons(22811);
    servaddr_udp2.sin_addr.s_addr = INADDR_ANY;

    memset((char *) &servaddr_udp3, 0, sizeof(servaddr_udp3));
    servaddr_udp3.sin_family = AF_INET;
    servaddr_udp3.sin_port = htons(23811);
    servaddr_udp3.sin_addr.s_addr = INADDR_ANY;
    //printf("The AWS is up and running\n");
        sock_udp=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        bind(sock_udp, (struct sockaddr *) &servaddr_udp, sizeof(servaddr_udp));
        
    ssize_t recvclient, recv1, recv2, recv3 = 0;

// till here
    while(1)
    {

        bzero( str, 200);
	//printf("\nWaiting for command from client\n");
        recvclient = 0;
	while(recvclient <=  0){
        	recvclient = read(command,str,200);
		if(strlen(str) == 0) sleep(10);	
	}
        //printf("Replying back-%s\n",str);
        ////write(command, str, strlen(str)+1); 
	printf("The AWS received %s from the client\n",str);
        
    	recv1 = 0;
	recv2 = 0;
	recv3 = 0;
    
        count_udp++;
        strcpy(message_udp,str);
        char * Search;
        Search = strtok(str," ");
        //printf("%s\n",Search);
	//Word = strtok(str," ");
	//printf("%s\n",Word);
        
        if(sendto(sock_udp, message_udp, strlen(message_udp) , 0 , (struct sockaddr *) &servaddr_udp1, slen_udp) == -1){
          die("Failed to send to ServerA. Exiting");
        }
	printf("The AWS sent the function of %s to backend-ServerA\n",message_udp);


        if(sendto(sock_udp, message_udp, strlen(message_udp) , 0 , (struct sockaddr *) &servaddr_udp2, slen_udp) == -1){
          die("Failed to send to ServerB. Exiting");
        }
	printf("The AWS sent the function of %s to backend-ServerB\n",message_udp);


        if(sendto(sock_udp, message_udp, strlen(message_udp) , 0 , (struct sockaddr *) &servaddr_udp3, slen_udp) == -1){
          die("Failed to send to ServerC. Exiting");
        }  
	printf("The AWS sent the function of %s to backend-ServerC\n",message_udp);
       
	
 

   
	memset(buffer_udp1,'\0', 2048);
        recv1 = recvfrom(sock_udp, buffer_udp1, 2048, 0, (struct sockaddr *) &servaddr_udp1, &slen_udp);
        if(recv1 == -1){
           die("Failed to receive from Server A");
        }else{
           strcpy(buffer_udp1cpy, buffer_udp1);
           //printf("Received %s from ServerA\n", buffer_udp1);
        }
        memset(buffer_udp2,'\0', 2048);
        recv2 = recvfrom(sock_udp, buffer_udp2, 2048, 0, (struct sockaddr *) &servaddr_udp2, &slen_udp);

        if(recv2 == -1){
           die("Failed to receive from Server B");
        }else{
           strcpy(buffer_udp2cpy, buffer_udp2);
           //printf("Received %s from ServerB\n", buffer_udp2);
        }
	memset(buffer_udp3,'\0', 2048);
        recv3 = recvfrom(sock_udp, buffer_udp3, 2048, 0, (struct sockaddr *) &servaddr_udp3, &slen_udp);

        if(recv3 == -1){
           die("Failed to receive from Server C");
        }else{
           strcpy(buffer_udp3cpy, buffer_udp3);
           //printf("Received %s from ServerC\n\n", buffer_udp3);
        }


       //printf("\n Printing all \n %s %s %s\n\n",buffer_udp1cpy, buffer_udp2cpy, buffer_udp3cpy);        

       if(strncmp(Search,"prefix",6) == 0){
        memset(buffer_udp,'\0', 8192);
	recv1 = strcmp(buffer_udp1cpy,"Nothing Found");
    	if(recv1 != 0){
		//printf("Concat buffer1 %s\n", buffer_udp1cpy);
		strcat(buffer_udp, buffer_udp1cpy);
                printf("The AWS received %d matches from Backend-ServerA using UDP over port 24811\n", count_newlines(buffer_udp1cpy)); 

	} else {
		printf("The AWS received 0 matches from Backend-ServerA using UDP over port 24811\n");
        }
	recv2 = strcmp(buffer_udp2cpy,"Nothing Found");
    	if(recv2 != 0){
		//printf("Concat buffer2 %s\n", buffer_udp2cpy);
		strcat(buffer_udp, buffer_udp2cpy);
                printf("The AWS received %d matches from Backend-ServerB using UDP over port 24811\n", count_newlines(buffer_udp2cpy)); 

	} else {
		printf("The AWS received 0 matches from Backend-ServerB using UDP over port 24811\n");
        }
	//recv3 = strcmp(buffer_udp3,"Nothing Found");
    	if(recv3 != 0){
		//printf("Concat buffer3 %s\n", buffer_udp3cpy);
		strcat(buffer_udp, buffer_udp3cpy);
                printf("The AWS received %d matches from Backend-ServerC using UDP over port 24811\n", count_newlines(buffer_udp3cpy)); 

	} else {
		printf("The AWS received 0 matches from Backend-ServerC using UDP over port 24811\n");
        }
	//printf("\nThe AWS sent \n%s\n matches to Client\n", buffer_udp);
	write(command, buffer_udp, strlen(buffer_udp));
       } else {
        memset(buffer_udp,'\0', 8192);
        recv1 = strcmp(buffer_udp1cpy,"Nothing Found");
        if(recv1 != 0){
		//printf("Concat buffer1 %s\n", buffer_udp1cpy);
		strcpy(buffer_udp, buffer_udp1cpy);
                printf("The AWS received 1 similar words from Backend-ServerA using UDP over port 24811\n"); 
	} else {
                printf("The AWS received 0 similar words from Backend-ServerA using UDP over port 24811\n"); 

        }
        recv2 = strcmp(buffer_udp2cpy,"Nothing Found");
        if(recv2 != 0){
		//printf("Concat buffer1 %s\n", buffer_udp1cpy);
		strcpy(buffer_udp, buffer_udp2cpy);
                printf("The AWS received 1 similar words from Backend-ServerB using UDP over port 24811\n"); 
	} else {
                printf("The AWS received 0 similar words from Backend-ServerB using UDP over port 24811\n"); 

        }
	recv3 = strcmp(buffer_udp3cpy,"Nothing Found");
        if(recv3 != 0){
		//printf("Concat buffer1 %s\n", buffer_udp1cpy);
		strcpy(buffer_udp, buffer_udp3cpy);
                printf("The AWS received 1 similar words from Backend-ServerC using UDP over port 24811\n"); 
	} else {
                printf("The AWS received 0 similar words from Backend-ServerC using UDP over port 24811\n"); 

        }
        write(command, buffer_udp, strlen(buffer_udp));

       }



    
   
count--;
  //close(sock_udp);
  //close(listener);
}

    }

