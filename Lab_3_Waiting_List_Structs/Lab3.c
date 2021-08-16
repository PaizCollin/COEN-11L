#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int openings = 0;
int i;
int j;
char name[20];
int party;
int duplicate (char *);
char names[10][20];
int parties[10];

void insert(void);
void delete(void);
void list(void);
void searchSize(void);

typedef struct entry
{
        char names[20];
        int parties;
}ENTRY;

int counter = 0;
ENTRY reservations[10];
ENTRY *p = reservations;

int main(void) //prints and awaits an option using a switch and calls the corresponding function
{
        int answer;

        while(1)
        {
                printf("MENU\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Size Search\n 0 - Quit\n"); //prints the menu
                scanf("%d", &answer); //read user input
                printf("Option: %d\n", answer);
                switch(answer) //switch for all menu options
                {
                        case 1: //calls insert function
                                insert();
                                break;
                        case 2: //calls delete function
                                delete();
                                break;
                        case 3: //calls list function
                                list();
                                break;
                        case 4: //calls search size function
                                searchSize();
                                break;
                        case 0: //ends program
                                return 0;
                        default: //notifies user of an invalid input
                                printf("Please use an available option\n");
                                break;
                }
        }
}

void insert() //function used to insert a new reservation
{

        if(openings == 10) //only 10 reservations are allowed
        {
                printf("There are no available time slots\n");
                return;
        }

        ENTRY *p = reservations;

        printf("Name: ");
        scanf("%s", name); //read user input for name
        for(i=0; i<openings; i++) //checks for unique name
        {
                while(strcmp((p+i)->names, name)==0)
                {
                        printf("Enter a unique name: ");
                        scanf("%s", name);
                }
        }

        printf("Party Size: ");
        scanf("%d", &party); //read user input for party size

        p+=openings;

        strcpy(p->names, name); //copies name to the name list
        p->parties = party; //copies the party size to the party list
        printf("%s party of %d has been reserved\n", name, party);
        openings++; //increases the number of reservations

}       


void delete() //function to remove the oldest reservation that fits the size parameter
{
        
        int size = 0;
        ENTRY *p = reservations;
        int flag = 0;
        int currentopenings = openings;

        if(openings == 0) //determines if there are any reservations that exist
        {
                printf("No Reservations\n");
        }
        else
        {
                printf("Size of the opening: ");
                scanf("%d", &size); //read user input for party size
                
                while(flag < currentopenings && size > 0) //iterates through all parties
                {
                        if(p->parties <= size) //finds the first party that fits the open party size
                        {
                                size = size - p->parties;
                                
                                printf("%s with a party of %d is being seated\n", p->names, p->parties);
                        
                                for(i=0; i<currentopenings; i++) //shifts the list
                                {
                                        strcpy((p+i)->names, (p+i+1)->names); //shift name list up
                                        (p+i)->parties = (p+i+1)->parties; //shift party list up
                                      
                                }
                                openings--; //one less reservation
                                flag++;
                                continue;
                        }       
                        flag++;
                        p++;    
                }               
        }       
}       

void list() //function to list all current reservation names and associated party sizes
{

        ENTRY *p = reservations;
        
        while(p->names[0] != '\0')
        {       
                printf("%s, %d\n", p->names, p->parties);
                p++;
        }
}       

void searchSize()
{       
        int size = 0;
        ENTRY *p = reservations;
                
        printf("Party Size: ");
        scanf("%d", &size);

        while(p->names[0] != '\0') //searches all available names
        {
                if(p->parties <= size)
                {
                        printf("%s, %d\n", p->names, p->parties);
                }
                p++;
        }
}
