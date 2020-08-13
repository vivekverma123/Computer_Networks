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
	//define server address
	
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10001);
	server_address.sin_addr.s_addr=INADDR_ANY;
	
	// binding IP and Port
	bind(server_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	
	//listening for connection
	listen(server_socket,10);
	
	//accpting a connection
	int client_socket;
	client_socket=accept(server_socket,NULL,NULL);
	
	//connect(socket,address of the connecting socket,length of address)
	//receiving data from client
	
	while(1)
	{
		//memset(message,'\0',sizeof(message));
		char message[39],ch1;
		int x = 0;
		recv(client_socket,&x,sizeof(x),0);
		recv(client_socket,message,x,0);
		printf("Processing\n");
		if(x==39)
		{
			char ans[22];
			int i,j = 0;
			for(i=0;i<4;++i)
			{
				ans[j++] = message[i];
			}
			ans[j++] = ':';
			ans[j++] = '0';
			ans[j++] = ':';
			for(i=10;i<14;++i)
			{
				ans[j++] = message[i];
			}	
			ans[j++] = ':';
			ans[j++] = ':';
			for(i=30;i<39;++i)
			{
				ans[j++] = message[i];
			}
			ans[j] = '\0';
			//display(ans);
			send(client_socket,ans,strlen(ans),0);
		}
		else if(x==22)
		{
			char ans[39];
			int i,j = 0,k = 0;
			for(i=0;i<6;++i)
			{
				ans[j++] = message[i];
			}
			for(k=0;k<3;++k)
			{
				ans[j++] = '0';
			}
			ans[j++] = ':';
			for(i=7;i<=10;++i)
			{
				ans[j++] = message[i];
			}
			ans[j++] = ':';
			for(k=0;k<4;++k)
			{
				ans[j++] = '0';
			}
			ans[j++] = ':';
			for(k=0;k<4;++k)
			{
				ans[j++] = '0';
			}
			ans[j++] = ':';
			for(k=0;k<4;++k)
			{
				ans[j++] = '0';
			}
			ans[j++] = ':';
			for(i=13;i<22;++i)
			{
				ans[j++] = message[i];
			}
			ans[j] = '\0';
			//display(ans);
			send(client_socket,ans,strlen(ans),0);
		}
		else
		{
			char message1[] = "Invalid data";
			send(client_socket,message1,strlen(message1),0);
		}
		recv(client_socket,&ch1,sizeof(ch1),0);
		if(ch1=='n' || ch1=='N')
		{
			break;
		}	
	}
	printf("Session terminated by client.\n");
	close(server_socket);
	return 0;
}
