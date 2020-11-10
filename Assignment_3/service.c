#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct employee
{
	char id[20];
	int tot,curr,ext;
};

struct employee search(FILE *ptr, char id[20])
{
	fseek(ptr,0,SEEK_SET);
	struct employee e1;
	while(fread(&e1,sizeof(e1),1,ptr))
	{
		if(strcmp(id,e1.id)==0)
		{
			return e1;
		}
	}
}

void edit(FILE *ptr, struct employee e2)
{
	int count = 0;
	fseek(ptr,0,SEEK_SET);
	count = ftell(ptr);
	struct employee e1;
	while(fread(&e1,sizeof(e1),1,ptr))
	{
		if(strcmp(e1.id,e2.id)==0)
		{	
			fseek(ptr,count,SEEK_SET);
			fwrite(&e2,sizeof(e1),1,ptr);
		}
		count = ftell(ptr);
	}
}

int main()
{
	FILE *ptr;
	ptr = fopen("file.dat","a");
	int n,i;
	scanf("%d",&n);
	struct employee e1;
	for(i=0;i<n;++i)
	{
		scanf("%s %d %d %d",e1.id,&e1.tot,&e1.curr,&e1.ext);
		fwrite(&e1,sizeof(e1),1,ptr);
	}
	fclose(ptr);
	ptr = fopen("file.dat","r");
	while(fread(&e1,sizeof(e1),1,ptr))
	{
		printf("Employee ID: %s\n",e1.id);
		printf("Total Leaves: %d\n",e1.tot);
		printf("Current Balance: %d\n",e1.curr);
		printf("Extra Leaves: %d\n",e1.ext);
		printf("\n");
	}
	/*char str[25] = "E2";
	e1 = search(ptr,str);
	printf("Employee ID: %s\n",e1.id);
	printf("Total Leaves: %d\n",e1.tot);
	printf("Current Balance: %d\n",e1.curr);
	printf("Extra Leaves: %d\n",e1.ext);
	printf("\n");
	strcpy(e1.id,"E1");
	e1.tot = 20;
	e1.curr = 0;
	fclose(ptr);
	e1.ext = 0;
	ptr = fopen("file.dat","r+");
	edit(ptr,e1);*/
	fclose(ptr);
	return 0;
}
