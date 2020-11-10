#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

void display(char str[])
{
	int i = 0;
	while(str[i]!='\0')
	{
		printf("%c",str[i]);
		i += 1;
	}
	printf("\n");
}

int main()
{
	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	bind(server_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	listen(server_socket,10);
	int client_socket;
	client_socket=accept(server_socket,NULL,NULL);
	char password[40] = {},pass[40] = "Aa@12345678",message1[40];
	int x;
	recv(client_socket,&x,sizeof(x),0);
	recv(client_socket,password,x,0);
	if(strcmp(pass,password)==0)
	{
		printf("Password matched, acknowledgement send!\n");
		int x = 1;
		send(client_socket,&x,sizeof(x),0);
		recv(client_socket,&x,sizeof(x),0);
		recv(client_socket,message1,x,0);
		printf("Client's response: ");
		message1[x] = '\0';
		display(message1);
		strcpy(message1,"Hi,press any key to exit");
		x = 24;
		send(client_socket,&x,sizeof(x),0);
		send(client_socket,message1,x,0);
		char ch;
		recv(client_socket,&ch,sizeof(ch),0);
		printf("Session terminated by the client.\n");
	}
	else
	{
		int x = 0;
		send(client_socket,&x,sizeof(x),0);
	}
	close(server_socket);
	return 0;
}
