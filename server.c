#include<stdio.h>
#include<string.h>
#include <unistd.h>>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
    int port=8080, socket_fd;
    struct sockaddr_in cli, svr;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd<0)
    {
        printf("error in socket creation \n");
        return 0;
    }
    svr.sin_family=AF_INET;
    svr.sin_port=htons(port);
    svr.sin_addr.s_addr= INADDR_ANY;

    if(bind(socket_fd,  (struct sockaddr *) &svr, sizeof(svr))<0)
    {
        printf("error in socket creation \n");
        return 0;
    }
    listen(socket_fd, 5);
    int clilen=sizeof(cli);
    int newsocket= accept(socket_fd, (struct sockaddr*) & cli,&clilen );
    if(newsocket<0){
    printf("error in socket creation \n");
        return 0;
    }
    send(newsocket, "hello hello", 13,0);
    char buffer[2560];
    bzero(buffer,256);

    int n= read(newsocket, buffer , 255);
    if(n<0)
    {
        printf("error in socket creation \n");
        return 0;
    }

    
}
