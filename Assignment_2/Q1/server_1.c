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
	char word[100];
	char meaning[100];
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
	int client_socket;
	client_socket=accept(server_socket,NULL,NULL);
	char word[100],meaning[100];
	int n;
	recv(client_socket,&n,sizeof(n),0);
	recv(client_socket,word,n,0);
	word[n] = '\0';
	FILE *ptr;
	ptr = fopen("Record.dat","r+");
	int flag = 0;
	struct record r1;
	printf("Loking into the server's database.\n");
	while(fread(&r1,sizeof(struct record),1,ptr))
	{
		if(strcmp(r1.word,word)==0)
		{
			++flag;
			break;
		}
	}
	fclose(ptr);
	send(client_socket,&flag,sizeof(flag),0);
	if(flag==0)
	{
		printf("Match not found, requesting the meaning.\n");
		recv(client_socket,&n,sizeof(n),0);
		recv(client_socket,meaning,n,0);
		meaning[n] = '\0';
		strcpy(r1.word,word);
		strcpy(r1.meaning,meaning);
		ptr = fopen("Record.dat","a");
		fwrite(&r1,sizeof(struct record),1,ptr);
		fclose(ptr);
		printf("1 word with meaning added to the server's database.\n");
	}	
	else
	{
		printf("Match found\n");
		n = strlen(r1.meaning);
		send(client_socket,&n,sizeof(n),0);
		send(client_socket,r1.meaning,n,0);
	}
	printf("Session terminated.\n");
	close(server_socket);
	return 0;
}
