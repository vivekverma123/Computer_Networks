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
	char word[100],meaning[100];
	int n;
	printf("Enter the word: ");
	char ch;
	scanf("%[^\n]",word);
	n = strlen(word);
	word[n] = '\0';
	send(network_socket,&n,sizeof(n),0);
	send(network_socket,word,n,0);
	int flag = 0;
	recv(network_socket,&flag,sizeof(flag),0);
	if(flag==0)
	{
		printf("Word not found.\n");
		printf("Enter the meaning to update in the server: ");
		ch = getchar();
		scanf("%[^\n]",meaning);
		n = strlen(meaning);
		send(network_socket,&n,sizeof(n),0);
		send(network_socket,meaning,n,0);
		printf("Word updated in server's database successfully.\n");
	}
	else
	{
		printf("Word found.\n");
		recv(network_socket,&n,sizeof(n),0);
		recv(network_socket,meaning,n,0);
		meaning[n] = '\0';
		printf("Meaning fetched from server's database: %s\n",meaning);
	}
	printf("Session terminated.\n");
	close(network_socket);
	return 0;
}
