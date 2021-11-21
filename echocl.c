#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int socket_desc,new_socket,c;
struct sockaddr_in server;
char clmsg[20000],sv_reply[20000];

//create socket
socket_desc=socket(AF_INET, SOCK_STREAM, 0);
if(socket_desc==-1)
{
printf("Could not create socket");
}


server.sin_addr.s_addr=inet_addr("192.168.56.101");//Server IP address
server.sin_family=AF_INET;
server.sin_port=htons(8888);//use port 8888

//connect to remote server
if(connect(socket_desc,(struct sockaddr *)&server, sizeof(server))<0)
{
puts("connect error");
return 1;
}
puts("Connected \n");


//message to server
while(1)
{
printf("Enter a message: ");
fgets(clmsg,20000,stdin);
send(socket_desc,clmsg,20000,0);

if(send(socket_desc,clmsg,strlen(clmsg),0)<0)
{
puts("FAILED TO SEND");
return 1;
}

if(recv(socket_desc,sv_reply,20000,0)<0)
{
puts("recv failed");
break;
}

puts("_________________________________________\n");
puts("SERVER REPLY: ");
puts(sv_reply);

}

close(socket_desc);
return 0;
}



