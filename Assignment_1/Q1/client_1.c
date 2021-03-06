#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>

void display(char str[])
{
	int i = 0;
	while(str[i]!='\0')
	{
		printf("%c",str[i]);
		i += 1;
	}
	//printf("\n");
}

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	int status=connect(network_socket,(struct sockaddr *)&server_address,sizeof(struct
	sockaddr_in));
	if(status==-1)
	{
	printf("\n connection error.....");
	}
	char password[40];
	printf("Enter the password: ");
	scanf("%s",password);
	int x;
	x = strlen(password);
	send(network_socket,&x,sizeof(x),0);
	send(network_socket,password,x,0);
	recv(network_socket,&x,sizeof(x),0);
	if(x==1)
	{
		printf("Authentication Successful\n");
		char str1[30];
		strcpy(str1,"Hi");
		int y = strlen(str1);
		send(network_socket,&y,sizeof(y),0);
		send(network_socket,str1,y,0);
		printf("Sent hi to the server!\n");
		char ch = getchar();
		recv(network_socket,&y,sizeof(y),0);
		recv(network_socket,str1,y,0);
		printf("Server's response: ");
		str1[y] = '\0';
		display(str1);
		ch = getchar();
		send(network_socket,&ch,sizeof(ch),0);
	}
	else
	{
		printf("Authentication Failed\n");
	}
	close(network_socket);
	return 0;
}
