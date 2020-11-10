#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include "services.h"

int main()
{
	int network_socket;
	network_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	int addrlen = sizeof(server_address);
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(10000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	int status=connect(network_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	if(status==-1)
	{
		printf("\n connection error.....");
	}
	
	char ch = 'y';
	int choice;
	struct sample s1;
	int roll_no,ack,count = 0;
	
	while(ch=='y' || ch=='Y')
	{
		printf("1. Add a record\n");
		printf("2. Retrieve a single record (using Roll Number)\n");
		printf("3. View all records (using Roll Number)\n");
		printf("4. Modify a record (using Roll Number)\n");
		printf("5. Delete a record (using Roll Number)\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		fflush(stdin);
		char ch = 'y';
		send(network_socket,&choice,sizeof(choice),0);
		
		switch(choice)
		{
			case 1:
				input(&s1);
				send_object(&s1,&network_socket);
				
				recv(network_socket,&ack,sizeof(ack),0);
				
				if(ack==1)
				{
					printf("Record added successfully\n");
				}
				else
				{
					printf("Record by the same roll number already exists in the server's database\n");
				}
				
				break;
				
			case 2:
				printf("Enter the Roll Number: ");
				scanf("%d",&roll_no);
				send(network_socket,&roll_no,sizeof(int),0);
				receive_object(&s1,&network_socket);
				if(s1.roll_no==-1)
				{
					printf("The record not found!\n");
				}
				else
				{
					output(&s1);
				}
				break;
			
			case 3:
				count = 0;
				receive_object(&s1,&network_socket);
				while(s1.roll_no!=-1)
				{
					output(&s1);
					count += 1;
					receive_object(&s1,&network_socket);
				}
				printf("%d records fetched.\n",count);
				break;
				
			case 4:
				printf("Enter the roll number to search the record: ");
				scanf("%d",&roll_no);
				
				send(network_socket,&roll_no,sizeof(int),0);
				recv(network_socket,&ack,sizeof(int),0);
				
				if(ack==1)
				{
					printf("Record found, enter the new details :- \n");
					input(&s1);
					send_object(&s1,&network_socket);
					printf("Record modified successfully.\n");
				}
				else
				{
					printf("Record with the given roll number doesn't exist!\n");
				}
				break;
				
			case 5:
				printf("Enter the Roll Number: ");
				scanf("%d",&roll_no);
				
				send(network_socket,&roll_no,sizeof(int),0);
				recv(network_socket,&ack,sizeof(int),0);
				
				if(ack==1)
				{
					printf("Record deleted successfully\n");
				}
				else
				{
					printf("Record by the same roll number doesn't exist in the server's database!\n");
				}
				
				break;
				
				
			default:
				printf("Invalid Choice!!!\n");
				
		}
		
		fflush(stdin);
		printf("Do you want to continue? (y/n): ");
		char ch1 = getchar();
		scanf("%c",&ch);
		send(network_socket,&ch,sizeof(ch),0);
		fflush(stdin);
		if(ch!='y' && ch!='Y')
		{
			break;
		}
	}	
	printf("Session Terminated!!!\n");
	close(network_socket);
	return 0;
}
