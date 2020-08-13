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
	printf("\n");
}

int main()
{
	int network_socket;
	// create socket(domain,type,protocol);
	
	network_socket=socket(AF_INET,SOCK_STREAM,0);
	// Specifying address of socket to which client wants to connect
	
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10001);
	server_address.sin_addr.s_addr=INADDR_ANY;
	
	// connect
	int status=connect(network_socket,(struct sockaddr *)&server_address,sizeof(struct
	sockaddr_in));
	if(status==-1)
	{
	printf("\n connection error.....");
	}
	
	//sending data to server
	while(1)
	{
		char ch1;
		char message[39] = {},reply[39] = {};
		printf("Enter the IP address: ");
		scanf("%s",message);
		int x = strlen(message);
		send(network_socket,&x,sizeof(x),0);
		send(network_socket,message,strlen(message),0);
		recv(network_socket,reply,39,0);
		printf("Server's response: ");
		display(reply);
		printf("Do you want to continue?: ");
		ch1 = getchar();
		scanf("%c",&ch1);
		send(network_socket,&ch1,sizeof(ch1),0);
		if(ch1=='n' || ch1=='N')
		{
			break;
		}
		printf("\n");
	}
	//closing
	close(network_socket);
	return 0;
}
