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

struct employee 
{
	int id;
	int tot,bal,ext;
};

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
	int client_socket,choice;
	client_socket=accept(server_socket,NULL,NULL);
	struct employee e1[10];
	int i;
	for(i=0;i<10;++i)
	{
		e1[i].id = i;
		e1[i].tot = 0;
		e1[i].bal = 10;
		e1[i].ext = 0;
	}	
	while(1)
	{
		
		char ch1;
		recv(client_socket,&ch1,sizeof(ch1),0);
		if(ch1=='n' || ch1=='N')
		{
			break;
		}
	}
	printf("Session terminated by client\n");
	close(server_socket);
	return 0;
}
