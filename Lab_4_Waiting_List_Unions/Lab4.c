#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insert(void);
void delete(void);
void list(void);
void searchSize(void);

typedef union extra
{
        char birthday_name[20];
        int years;
        float average_age;
}EXTRA;

typedef struct entry
{
        char names[20];
        int parties;
        int occasion;
        EXTRA extra_info;
}ENTRY;

int openings = 0;
ENTRY reservations[10];

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

        int i, j;
        int duplicate (char *);
        int whatoccasion = 0;
        int numyears = 0;
        float age = 0.0;
        char bdayname[20];
        int party;
        char name[20];

        if(openings == 10)
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

        p+=openings;

        printf("Party Size: ");
        scanf("%d", &party); //read user input for party size

        printf("Occasion: ");
        scanf("%d", &whatoccasion); //read user input for occasion type
        switch(whatoccasion) //switch for occasion
        {
                case 1: //for birthday
                        printf("Name of the Birthday Person: ");
                        scanf("%s", bdayname);
                        strcpy(p->extra_info.birthday_name, bdayname);
                        break;
                case 2: //for anniversary
                        printf("Years: ");
                        scanf("%d", &numyears);
                        p->extra_info.years = numyears;
                        break;
                default: //any other circumstance
                        printf("Average Age: ");
                        scanf("%f", &age);
                        p->extra_info.average_age = age;
                        break;
        }

        strcpy(p->names, name); //copies name to the name list
        p->parties = party; //copies the party size to the party list
        p->occasion = whatoccasion; //copies occasion to the current reservation
        printf("%s party of %d has been reserved\n", name, party);
        openings++; //increases the number of reservations
}


void delete() //function to remove the oldest reservation that fits the size parameter
{
        int i, j;
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
                                        (p+i)->occasion = (p+i+1)->occasion; //shift up occasion
                                        (p+i)->extra_info = (p+i+1)->extra_info; //shift up extra info
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
                printf("%s, %d, %d, ", p->names, p->parties, p->occasion);
                if(p->occasion == 1) //if birthday
                {
                        printf("%s \n", p->extra_info.birthday_name);
                }       
                else if(p->occasion == 2) //if anniversary
                {       
                        printf("%d \n", p->extra_info.years);
                }
                else //if anthing else
                {       
                        printf("%f \n", p->extra_info.average_age);
                }       
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
                        printf("%s, %d, %d ", p->names, p->parties, p->occasion);
                        if(p->occasion == 1) //if birthday
                        {
                                printf("%s \n", p->extra_info.birthday_name);
                        }
                        else if(p->occasion == 2) //if anniversary
                        {
                                printf("%d \n", p->extra_info.years);
                        }
                        else //if anything else
                        {
                                printf("%f \n", p->extra_info.average_age);
                        }
                }
                p++;
        }
}  