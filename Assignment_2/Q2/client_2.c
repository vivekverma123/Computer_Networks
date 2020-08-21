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
	int status=connect(network_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	if(status==-1)
	{
		printf("\n connection error.....");
	}
	int choice,n,flag;
	char state[30],capital[30],ch,data[30];
	label1:
	printf("Select your query :-\n");
	printf("1. Get capital from state\n");
	printf("2. Get state from capital\n");
	printf("3. Exit\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	send(network_socket,&choice,sizeof(choice),0);
	ch = getchar();
	switch(choice)
	{
		case 1:
			printf("Enter the state: ");
			scanf("%[^\n]",state);
			n = strlen(state);
			send(network_socket,&n,sizeof(n),0);
			send(network_socket,state,n,0);
			recv(network_socket,&flag,sizeof(flag),0);
			if(flag==1)
			{
				printf("\nMatch found!\n");
				recv(network_socket,&n,sizeof(n),0);
				recv(network_socket,data,n,0);
				data[n] = '\0';
				printf("Capital: %s\n",data);
			}
			else
			{
				printf("\nMatch not found!\n");
				printf("Enter the capital city: ");
				ch = getchar();
				scanf("%[^\n]",data);
				n = strlen(data);
				send(network_socket,&n,sizeof(n),0);
				send(network_socket,data,n,0);
				printf("\nServer's database updated successfully.\n");
			}
			break;
			
		case 2:
			printf("Enter the capital city: ");
			scanf("%[^\n]",capital);
			n = strlen(capital);
			send(network_socket,&n,sizeof(n),0);
			send(network_socket,capital,n,0);
			recv(network_socket,&flag,sizeof(flag),0);
			if(flag==1)
			{
				printf("\nMatch found!\n");
				recv(network_socket,&n,sizeof(n),0);
				recv(network_socket,data,n,0);
				data[n] = '\0';
				printf("State: %s\n",data);
			}
			else
			{
				printf("\nMatch not found!\n");
				printf("Enter the state: ");
				ch = getchar();
				scanf("%[^\n]",data);
				n = strlen(data);
				send(network_socket,&n,sizeof(n),0);
				send(network_socket,data,n,0);
				printf("\nServer's database updated successfully.\n");
			}
			break;
			
		case 3:
			printf("Connection terminated\n");
			goto label2;
			
		default:
			printf("Wrong choice\n");
	}
	//ch = getchar();
	printf("\n");
	goto label1;
	label2:
	close(network_socket);
	return 0;
}
