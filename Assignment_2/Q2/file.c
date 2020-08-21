#include<stdio.h>
#include<stdlib.h>

struct record
{
	char state[30];
	char capital[30];
};

int main()
{
	struct record r1;
	FILE *ptr;
	ptr = fopen("Record.txt","a+");
	char ch;
	int n,i;
	printf("Enter the number of words to be added or enter 0 to only view the current database: ");
	scanf("%d",&n);
	ch = getchar();
	for(i=0;i<n;++i)
	{
		printf("State: ");
		scanf("%[^\n]",r1.state);
		ch = getchar();
		printf("Capital: ");
		scanf("%[^\n]",r1.capital);
		ch = getchar();
		fwrite(&r1,sizeof(struct record),1,ptr);
	}	
	fclose(ptr);
	printf("\nThe entries present in the database are :-\n");
	ptr = fopen("Record.txt","r+");
	while(fread(&r1,sizeof(struct record),1,ptr))
	{
		printf("%s: %s\n",r1.state,r1.capital);
	}
	return 0;
}
