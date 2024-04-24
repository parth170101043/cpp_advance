#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    int socketfd,port,client_fd;
    struct sockaddr_in svr;
    svr.sin_family=AF_INET;
    svr.sin_port=htons(80);
    socketfd=socket(AF_INET,SOCK_STREAM, 0);
    if(inet_ptons(AF_INET, "127.0.0.1", &svr.sin_addr)<=0){
        printf("error in socket creation \n");
        return 0;
    }
       if ((client_fd  
               = connect(socketfd, (struct sockaddr*)&svr,  
                               sizeof(svr)))  
               < 0) {  
               printf("\nConnection Failed \n");  
               return -1;  
       }  
       send(socketfd, "hello", 13, 0);  
       printf("Hello message sent\n");  
       char buffer[1024];
       bzero(buffer,1024);
       int valread = read(socketfd, buffer, 1024);  
       printf("%s\n", buffer);  
  
}