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

int main(void)
{
    struct sockaddr_in saddr, servaddr;
    int flag=0;
    int sock,count;
int cc ;
    int slen = sizeof(servaddr);
    int receive_len;
    char *Search;
    char *Prefix;
    char *copy;
    char *copy1;
    char buffer[2048];
    char ser[2048];
    //char s2=' ';
    char *tomp[2048];
    char *w;
    char *word;
    char *tock;
    char *t;
    int k;
    int i,c = 0;
    char search[2048]="search";
    char prefix[2048]="prefix";
    //FILE *filename=fopen("backendC.txt","r");
    char temp[2048];
    const char s[2] = ":";
    bzero(temp,2048);
    bzero(temp,2048);
    char temp3[2048];
    const char x[2] = ":";
    int p = 0;
    copy = (char *)malloc(sizeof(char)*4096); 
    sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset((char *) &saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(22811);
    inet_pton(AF_INET,"127.0.0.1",&(saddr.sin_addr));
    memset((char *) &servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(24811);
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));


    bind(sock,(struct sockaddr*)&saddr,sizeof(saddr));
    printf("The backendserverB is up and running on port 22811\n");
    while(1)
    {
        //flag=1;
	//printf("\nWaiting to receive Request\n");
        receive_len = 0;
        bzero(buffer,2048);
        receive_len = recvfrom(sock, buffer, 2048, 0, (struct sockaddr *) &servaddr, &slen);
        printf("The backendserverB received %s from the client\n", buffer);

 if(strncmp(buffer,search,6)==0)
   	{       
        	Search = strtok(buffer," ");
        	//printf("%s\n",search);
        	word = strtok(NULL," ");
        	//printf("%s\n",word);
	        char temp1[256];
       		const char s[2] = ":";
       		bzero(temp1,256);
       		FILE *filename=fopen("backendB.txt","r");
		count=0;
                while (filename!=NULL && fgets(temp1, sizeof(temp1),filename) != NULL)
     		{ 
       			tock = strtok(temp1, s);

       			if(strncmp(tock,word,strlen(word))==0)
			{   
			   if(count == 0) {   
			      //printf("%s\n",tock);//word
			      tock = strtok(NULL, s);
			      //printf("%s\n",tock);//meaning
     			      
			      sendto(sock,(void *)tock,strlen(tock),0,(struct sockaddr*) &servaddr,slen);
			      //goto lev1;
			    }  
			    //printf("%s\n",word);
			    count++;
			      
                        }
		
                 }
		printf("The serverB has found %d match\n", count);
                char zerostring[13] = "Nothing Found";
                if(count == 0) sendto(sock,(void *)zerostring,13,0,(struct sockaddr*) &servaddr,slen);
         }
 else if (strncmp(buffer,prefix,6)==0)
	{        
       		Prefix = strtok(buffer," ");
        	//printf("%s\n",search);
        	word = strtok(NULL," ");
        	//printf("%s\n",word);
      		FILE *filename=fopen("backendB.txt","r");
      		bzero(temp3,2048);
		count=0;
      		while (filename!=NULL && fgets(temp3, sizeof(temp3),filename) != NULL)
		
		{
      			w = strtok(temp3, x);
      			if(strstr(w,word))
      			{  

			//w=strtok(w,x);
     			 //printf("%s\n",w);
     			 // = strtok(NULL, x);
      			//printf("%s\n",copy);
      			//w = strtok(NULL, x);
		        //break;
			count=count+1;
			strcat(copy,w);
			strcat(copy,"\n");
			//break;
                 	}
    		}
		sleep(4);
                if(count > 0) sendto(sock,(void *)copy,strlen(copy),0,(struct sockaddr*) &servaddr,slen);



		printf("The ServerB has sent %d matches\n",count);
	}
 else
	{
	printf("error\n");
	}
	
printf("The serverB has finished sending output to AWS\n");
  }
     
    close(sock);
    return 0;
}
