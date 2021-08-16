#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int openings = 0;
int i;
int j;
char name[20];
int party;
char names[10][20];
int parties[10];


void insert(void);
void delete(void);
void list(void);

int main(void) //prints and awaits an option using a switch and calls the corresponding function
{
        int answer;

        for(i=0; i<10; i++) //sets all names to null
        {
                names[i][0] = '\0';
        }

        while(1)
        {
                printf("MENU\n 1 - Insert\n 2 - Delete\n 3 - List\n 0 - Quit\n"); //prints the menu
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
        printf("Name: ");
        scanf("%s", name); //read user input for name
        printf("Party Size: ");
        scanf("%d", &party); //read user input for party size

        for(i=0; i<10; i++) //iterates until it finds the first empty reservation slot
        {
                if(names[i][0] == '\0') //finds the empty slot
                {
                        for(j=0; j<20; j++) //copies each character to the name list
                        {
                                names[i][j] = name[j];
                        }
                        parties[i] = party; //copies the party size to the party list
                        printf("%s party of %d has been reserved\n", name, party);
                        openings++; //increases the number of reservations
                        break;
                }
        }
}

void delete() //function to remove the oldest reservation that fits the size parameter
{

int size = 0;

        if(openings == 0) //determines if there are any reservations that exist
        {
                printf("No Reservations\n");
        }
        else
        {
                printf("Size of the opening: ");
                scanf("%d", &size); //read user input for party size

                i = 0;

                while(names[i][0] != '\0' && size !=0) //iterates through all parties
                {
                        if(parties[i] <= size) //finds the first party that fits the open party size
                        {
                                size = size - parties[i];

                                printf("%s with a party of %d is being seated\n", names[i], parties[i]);

                                for(j=i; j<10; j++) //iterates through all following reservations to shift them up
                                {
                                        if(names[j][0] != '\0') //while not null
                                        {
                                                strcpy(names[j], names[j+1]); //shift name list up
                                                parties[j] = parties[j+1]; //shift party list up
                                        }
                                }

                                openings--; //one less reservation
                                continue;
                        }
                        i++;
                }
        }
}

void list() //function to list all current reservation names and associated party sizes
{
        for(i=0; i<10; i++) //iterates through all reservations
        {
                if(names[i][0] == '\0') //if the reservation is null, break the for loop
                {
                        break;
                }
                else //print the name and party size under the associated reservation slot
                {
                        printf("%s, %d\n", names[i], parties[i]);
                }
        }
}
