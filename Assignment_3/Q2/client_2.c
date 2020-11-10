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

struct employee 
{
	int id;
	int tot,bal,ext;
};

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
	
	while(1)
	{
	
		
		
		int id,flag = 0;
		printf("Enter the employee ID: ");
		scanf("%d",&id);
		send(network_socket,&id,sizeof(id),0);
		recv(network_socket,&flag,sizeof(flag),0);
		if(flag==0)
		{
			printf("Record not found.\n");
		}
		else
		{
			int leaves;
			printf("Enter the number of leaves: ");
			scanf("%d",&leaves);
		}
		
		
		
		
		
		
		char ch1;
		printf("Do you want to continue? (y/n): ");
		scanf("%c",&ch1);
		send(network_socket,&ch1,sizeof(ch1),0);
		if(ch1=='n' || ch1=='N')
		{
			break;
		}
	}
	printf("Session terminated.\n");
	close(network_socket);
	return 0;
}
