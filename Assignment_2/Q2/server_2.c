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

struct record
{
	char state[30];
	char capital[30];
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
	label1:
	recv(client_socket,&choice,sizeof(choice),0);
	int n,flag = 0;
	char data[30];
	struct record r1;
	FILE *ptr = fopen("Record.txt","r+");
	switch(choice)
	{
		case 1:
			recv(client_socket,&n,sizeof(n),0);
			recv(client_socket,data,n,0);
			data[n] = '\0';
			while(fread(&r1,sizeof(struct record),1,ptr))
			{
				if(strcmp(r1.state,data)==0)
				{
					++flag;
					break;
				}
			}
			fclose(ptr);
			send(client_socket,&flag,sizeof(flag),0);
			if(flag==1)
			{
				n = strlen(r1.capital);
				send(client_socket,&n,sizeof(n),0);
				send(client_socket,r1.capital,n,0);
			}
			else
			{
				ptr = fopen("Record.txt","a+");
				strcpy(r1.state,data);
				recv(client_socket,&n,sizeof(n),0);
				recv(client_socket,r1.capital,n,0);
				r1.capital[n] = '\0';
				fwrite(&r1,sizeof(struct record),1,ptr);
				fclose(ptr);
			}
			break;
			
		case 2:
			recv(client_socket,&n,sizeof(n),0);
			recv(client_socket,data,n,0);
			data[n] = '\0';
			while(fread(&r1,sizeof(struct record),1,ptr))
			{
				if(strcmp(r1.capital,data)==0)
				{
					++flag;
					break;
				}
			}
			fclose(ptr);
			send(client_socket,&flag,sizeof(flag),0);
			if(flag==1)
			{
				n = strlen(r1.state);
				send(client_socket,&n,sizeof(n),0);
				send(client_socket,r1.state,n,0);
			}
			else
			{
				ptr = fopen("Record.txt","a+");
				strcpy(r1.capital,data);
				recv(client_socket,&n,sizeof(n),0);
				recv(client_socket,r1.state,n,0);
				r1.state[n] = '\0';
				fwrite(&r1,sizeof(struct record),1,ptr);
				fclose(ptr);
			}
			break;
			
		case 3:
			printf("Connection terminated by client.\n");
			goto label2;
			
		default:
			printf("Invalid choice received from client.\n");
	}
	//ch = getchar();
	goto label1;
	label2:
	close(server_socket);
	return 0;
}
