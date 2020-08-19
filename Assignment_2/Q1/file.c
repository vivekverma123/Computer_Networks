//this programme can be used to add words to the dictionary locally

//words already present in the dictionary
/*

Word: do
Meaning: accomplish, prepare, resolve, work out
Word: say
Meaning: suggest, disclose, answer
Word: go
Meaning: continue, move, lead
Word: get
Meaning: bring, attain, catch, become
Word: make
Meaning: create, cause, prepare, invest

*/

#include<stdio.h>
#include<stdlib.h>

struct record
{
	char word[100],meaning[100];
};

int main()
{
	struct record r1;
	FILE *ptr;
	ptr = fopen("Record.dat","a+");
	char ch;
	int n,i;
	printf("Enter the number of words to be added or enter 0 to only view the current dictionary: ");
	scanf("%d",&n);
	ch = getchar();
	for(i=0;i<n;++i)
	{
		printf("Word: ");
		scanf("%[^\n]",r1.word);
		ch = getchar();
		printf("Meaning: ");
		scanf("%[^\n]",r1.meaning);
		ch = getchar();
		fwrite(&r1,sizeof(struct record),1,ptr);
	}	
	fclose(ptr);
	ptr = fopen("Record.dat","r+");
	while(fread(&r1,sizeof(struct record),1,ptr))
	{
		printf("%s: %s\n",r1.word,r1.meaning);
	}
	return 0;
}
