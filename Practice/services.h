#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void send_string(char *ptr, int *socket)
{
	int n = strlen(ptr);
	send(*socket,&n,sizeof(n),0);
	send(*socket,ptr,n,0);
}

void receive_string(int *socket, char str[])
{
	int n;
	recv(*socket,&n,sizeof(n),0);
	recv(*socket,str,n,0);
	str[n] = '\0';
}

struct sample
{
	char name[100];
	float gpa;
	int roll_no;
};

void input(struct sample *s1)
{
	fflush(stdin);
	printf("Enter the following details :-\n");
	printf("Name: ");
	char ch = getchar();
	scanf("%[^\n]",s1->name);
	printf("Roll Number: ");
	scanf("%d",&s1->roll_no);
	fflush(stdin);
	printf("Grade Point Average: ");
	scanf("%f",&s1->gpa);
	fflush(stdin);
}

void output(struct sample *s1)
{
	printf("Name: %s\n",s1->name);
	printf("Roll Number: %d\n",s1->roll_no);
	printf("Grade Point Average: %f\n",s1->gpa);
}

void send_object(struct sample *s1, int *socket)
{
	send_string(s1->name,socket);
	send(*socket,&s1->roll_no,sizeof(s1->roll_no),0);
	send(*socket,&s1->gpa,sizeof(s1->gpa),0);
}

void receive_object(struct sample *s1, int *socket)
{
	receive_string(socket,s1->name);
	recv(*socket,&s1->roll_no,sizeof(s1->roll_no),0);
	recv(*socket,&s1->gpa,sizeof(s1->gpa),0);
}

struct sample find_record(int roll_no)
{
	struct sample s1;
	int flag=-1;
	FILE *ptr = fopen("Record.txt","r+");
	if(ptr==NULL)
	{
		printf("Failed\n");
	}
	fseek(ptr,0L,SEEK_SET);
	while(fread(&s1,sizeof(struct sample),1,ptr))
	{
		//output(&s1);
		if(s1.roll_no==roll_no)
		{
			flag += 1;
			break;
		}
	}
	fclose(ptr);
	if(flag==-1)
	{
		s1.roll_no = -1;
	}
	return s1;
}

int add_record(struct sample s1)
{
	if(find_record(s1.roll_no).roll_no!=s1.roll_no)
	{
		FILE *ptr = fopen("Record.txt","a+");
		fwrite(&s1,sizeof(struct sample),1,ptr);
		fclose(ptr);
		return 1;
	}
	else
	{
		return 0;
	}
}

void view_all(int *socket)
{
	struct sample s1;
	FILE *ptr = fopen("Record.txt","r+");
	if(ptr==NULL)
	{
		printf("Failed\n");
	}
	fseek(ptr,0L,SEEK_SET);
	while(fread(&s1,sizeof(struct sample),1,ptr))
	{
		send_object(&s1,socket);
		printf("\n");
	}
	s1.roll_no = -1;
	send_object(&s1,socket);
	fclose(ptr);
}

int modify_record(int roll_no, int *socket)
{
	struct sample s2;
	FILE *ptr = fopen("Record.txt","r+");
	if(ptr==NULL)
	{
		printf("Is NUll\n");
	}
	int flag = 0;
	int ack = 0;
	while(fread(&s2,sizeof(struct sample),1,ptr))
	{	
		if(s2.roll_no==roll_no)
		{
			++flag;
			struct sample s1;
			printf("Record found, new details requested!\n");
			ack = 1;
			
			send(*socket,&ack,sizeof(int),0);
			receive_object(&s1,socket);
			
			fseek(ptr,-sizeof(struct sample),SEEK_CUR);
			fwrite(&s1,sizeof(struct sample),1,ptr);
			break;
		}
	}	
	if(ack==0)
	{
		send(*socket,&ack,sizeof(int),0);
	}
	fclose(ptr);
	return flag;
}

int delete_record(int roll_no)
{
	struct sample s1;
	FILE *ptr1,*ptr2;
	ptr1 = fopen("Record.txt","r+");
	ptr2 = fopen("temp.txt","w+");
	fseek(ptr1,0,SEEK_SET);
	int flag = 0;
	while(fread(&s1,sizeof(struct sample),1,ptr1))
	{
		if(s1.roll_no==roll_no)
		{
			++flag;
			continue;
		}
		else
		{
			fwrite(&s1,sizeof(struct sample),1,ptr2);
		}
	}
	fclose(ptr1);
	fclose(ptr2);
	system("rm Record.txt");
	system("mv temp.txt Record.txt");
	return flag;
}

void upload_file(int *socket)
{
	FILE *ptr = fopen("Record.txt","r+");
	fseek(ptr,0,SEEK_END);
	int len = ftell(ptr),i;
	fclose(ptr);
	char ch;
	send(*socket,&len,sizeof(len),0);
	ptr = fopen("Record.txt","r+");
	for(i=0;i<len;++i)
	{
		ch = fgetc(ptr);
		//printf("%c",ch);
		send(*socket,&ch,sizeof(char),0);
	}
	fclose(ptr);
	printf("%d bytes transferred successfully.\n",len);
}

void download_file(int *socket)
{
	FILE *ptr = fopen("DownloadedFile.txt","w+");
	int len,i;
	char ch;
	recv(*socket,&len,sizeof(len),0);
	fseek(ptr,0,SEEK_CUR);
	for(i=0;i<len;++i)
	{
		recv(*socket,&ch,sizeof(char),0);
		//printf("%c",ch);
		fputc(ch,ptr);
	}
	fclose(ptr);
	printf("%d bytes fetched.\n",len);
	printf("File downloaded and saved as DownloadedFile.txt\n");
}


