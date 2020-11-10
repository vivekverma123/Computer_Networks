#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

/*void send_object(struct sample *s1, int *socket)
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
}*/

struct sample find_record(int roll_no)
{
	struct sample s1;
	int flag=-1;
	FILE *ptr = fopen("DownloadedFile.txt","r+");
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

void add_record(struct sample s1)
{
	FILE *ptr = fopen("DownloadedFile.txt","a");
	if(find_record(s1.roll_no).roll_no!=s1.roll_no)
	{
		fwrite(&s1,sizeof(struct sample),1,ptr);
		printf("Record added successfully.\n");
	}
	else
	{
		printf("Record with the given roll number already exists!\n");
	}
	fclose(ptr);
	
}

void view_all()
{
	struct sample s1;
	FILE *ptr = fopen("DownloadedFile.txt","r+");
	if(ptr==NULL)
	{
		printf("Failed\n");
	}
	fseek(ptr,0L,SEEK_SET);
	printf("\n");
	while(fread(&s1,sizeof(struct sample),1,ptr))
	{
		output(&s1);
		printf("\n");
	}
	fclose(ptr);
}

int modify_record(int roll_no)
{
	struct sample s2;
	FILE *ptr = fopen("DownloadedFile.txt","r+");
	if(ptr==NULL)
	{
		printf("Is NUll\n");
	}
	int flag = 0;
	while(fread(&s2,sizeof(struct sample),1,ptr))
	{	
		if(s2.roll_no==roll_no)
		{
			++flag;
			struct sample s1;
			printf("Record found, enter the new details!\n");
			input(&s1);
			fseek(ptr,-sizeof(struct sample),SEEK_CUR);
			fwrite(&s1,sizeof(struct sample),1,ptr);
			break;
		}
	}	
	fclose(ptr);
	return flag;
}

int delete_record(int roll_no)
{
	struct sample s1;
	FILE *ptr1,*ptr2;
	ptr1 = fopen("DownloadedFile.txt","r+");
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
	system("rm DownloadedFile.txt");
	system("mv temp.txt DownloadedFile.txt");
	return flag;
}

int main()
{
	while(1)
	{
		printf("1. Add a record\n");
		printf("2. View a record\n");
		printf("3. View all records\n");
		printf("4. Modify (by roll number)\n");
		printf("5. Delete (by roll number)\n");
		int choice;
		printf("Enter your choice: ");
		scanf("%d",&choice);
		fflush(stdin);
		char ch = 'y';
		struct sample s1;
		int roll_no;
		switch(choice)
		{
			case 1:
				
				input(&s1);
				add_record(s1);
				break;
				
			case 2:
			
				printf("Enter the Roll Number: ");
				scanf("%d",&roll_no);
				s1 = find_record(roll_no);
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
				view_all();
				break;
				
			case 4:
				printf("Enter the roll number to search the record: ");
				scanf("%d",&roll_no);
				if(modify_record(roll_no)==1)
				{
					printf("Record updated successfully!\n");
				}
				else
				{
					printf("Record with the given roll number doesn't exist!\n");
				}
				break;
				
			case 5:
				printf("Enter the roll number to search the record: ");
				scanf("%d",&roll_no);
				if(delete_record(roll_no)==1)
				{
					printf("Record deleted successfully!\n");
				}
				else
				{
					printf("Record with the given roll number doesn't exist!\n");
				}
				break;
			
			default:
				printf("Ivalid Choice\n");
				
		}
		fflush(stdin);
		printf("Do you want to continue? (y/n): ");
		char ch1 = getchar();
		scanf("%c",&ch);
		if(ch=='y' || ch=='Y')
		{
			
		}
		else
		{
			break;
		}
		fflush(stdin);
	}
	printf("\n");
	return 0;
}
