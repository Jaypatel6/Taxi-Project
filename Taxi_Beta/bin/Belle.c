#include "Belle.h"
char Belle(char *string)
{
char *comp=NULL;
char *word=NULL;
char *word2=NULL;

/* Word Bank*/
char str2[]=" do what how when who where why wen ";
char negative[]=" don't cancel not nevermind bu ";
char confirm[]=" yes yea okay sure good confirm perfect hoa ";
char dev_serverdown[]=" Des ";
char greetings[]=" hey hi hello morning greetings up ";
char demand[]=" want get xiang ";
/*Hard coding streets in for now for easier testing purposes*/
char street[]= " Antbeater Road Barracuda Pkwy Cauliflower Ave Doc Arthur Blvd East Main Four Or Five Hours Freeway Gymboree Road Hazard Ave Irvine Classic Drive Jerkly Ave Karmans Van Ave Lawnut Ave Michelangelo Drive New Irvine Blvd Orange Hill Road Pale Loop Quail Mill Pkwy Rectangular Adobe Road Stand Fourth Talton Pkwy University Circle Verde Palo Road West Campus Drive X Roads Yoming Ave Z End 1st 2nd 3rd 4th 5th 6th 7th 8th 9th 10th 11th 12th 13th 14th 15th 16th 17th 18th 19th 20th 21st 22nd 23rd 24th 25th 26th 27th 28th 29th 30th 31st 32nd 33rd 34th 35th 36th 37th 38th 39th 40th 41st 42nd ";
char and[]= " and he ";
char from[]= " from cong ";
char to[]= " to dao ";

int leng,x,count,question;

count=0;
question =0;

char str[100]={0};

printf("\nEnter Command : ");
scanf("%[^\n]s", str);

leng=strlen(str);
/*sleep(1);
printf("Belle is typing...\n");
sleep(2);*/
printf("Belle: ");
comp = strtok(str," ");
while (comp != NULL) {
	if (searchword(str2, comp)) {
        /* Match found */
	#ifdef DDEBUG
        printf("Question word found: %s\n", comp);
	#endif

	sleep(2);	
	printf("That's a very good question, ");
        count =1;
	
	}
		
	if (searchword(street, comp))
	{
	if(*(comp-3)=='t'||*(comp-4)=='d')
	{
	word=comp;
	printf("So you want to go to %s, ", word);
	count =1;
	}
	if(*(comp-5)=='f'||*(comp-5)=='c')
	{
	word2=comp;
	printf("I assume you are at %s, ",word2);
	count =1;
	}
	if(word==NULL&&word2==NULL)
	{
	printf("Sorry to be clear can you say from where to where? Thanks. ");
	count=1;
	}
	if(word!=NULL&&word2!=NULL)
	{
	/*Calculate Price and Calculate ETA functions will be called here*/
	printf("the ETA would be BLANK and the price would be BLANK. Would you like to take it? ");
	count=1;
	}
	}
	if (searchword(confirm, comp)) {
	printf("Perfect your taxi will be arrving soon. ");
	/* Confirm order function will be called here*/
	count=1;
	}
	if (searchword(greetings, comp)) {
        /* Match found */
	#ifdef DDEBUG
        printf("Greetings word found : %s\n", comp);
        #endif
	printf("Hello! Hope you are having a great day. ");
	count=1;
	}
 	if (searchword(dev_serverdown, comp)) {
        /* Match found */
        printf("Server will be down, authorized by %s\n", comp);
        count =1;
        }

comp = strtok(NULL," ");
}
if((word==NULL&&word2!=NULL)||(word!=NULL&&word2==NULL))
{
printf("sorry you mind telling me from where to where you would like to go instead? "); 
}
if(count==0)
{
printf("Sorry I dont understand what you are saying!");
count =0;
}
printf("\n");
return 0;
}

int searchword(char *text, char *word) {
    int i;

    while (*text != '\0') {
        while (isspace((unsigned char) *text))
            text++;
        for (i = 0; *text == word[i] && *text != '\0'; text++, i++);
        if ((isspace((unsigned char) *text) || *text == '\0') && word[i] == '\0')
            return 1;
        while (!isspace((unsigned char) *text) && *text != '\0')
            text++;
    }

    return 0;
}


