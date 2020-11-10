#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include "services.h"

int main()
{
	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	int addrlen = sizeof(server_address);
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	bind(server_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	listen(server_socket,10);
	int client_socket;
	client_socket=accept(server_socket,NULL,NULL);
	
	char ch = 'y';
	int choice,ack,nBytes;
	struct sample s1;
	int roll_no;
	
	while(ch=='y' || ch=='Y')
	{
		printf("1. Add a record\n");
		printf("2. Retrieve a single record (using Roll Number)\n");
		printf("3. View all records (using Roll Number)\n");
		printf("4. Modify a record (using Roll Number)\n");
		printf("5. Delete a record (using Roll Number)\n");
		printf("6. Download a copy of record file\n");
		recv(client_socket,&choice,sizeof(choice),0);
		printf("Selected %d\n",choice);
		
		switch(choice)
		{
			case 1:
				receive_object(&s1,&client_socket);
				output(&s1);
				printf("Opening File\n");
				ack = add_record(s1);
				printf("Sending acknowldgment\n");
				send(client_socket,&ack,sizeof(ack),0);
				break;
				
			case 2:
				recv(client_socket,&roll_no,sizeof(int),0);
				s1 = find_record(roll_no);
				send_object(&s1,&client_socket);
				break;
				
			case 3:
				view_all(&client_socket);
				break;
				
			case 4:
				recv(client_socket,&roll_no,sizeof(int),0);
				modify_record(roll_no,&client_socket);
				break;
				
			case 5:
				recv(client_socket,&roll_no,sizeof(int),0);
				ack = delete_record(roll_no);
				send(client_socket,&ack,sizeof(ack),0);
				break;
				
			case 6:
				upload_file(&client_socket);
				break;
				
			default:
				printf("Invalid Choice!!!\n");
				
		}
		recv(client_socket,&ch,sizeof(ch),0);
		if(ch!='y' && ch!='Y')
		{
			break;
		}
	}	
	printf("Terminating Session!\n");
	close(server_socket);
	return 0;
}
