#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insert(void);
void delete(void);
void list(void);
void searchSize(void);

#define ENTRY   struct entry
struct entry
{
        char names[20];
        int parties;
        ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;

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
        int party;
        int duplicate (char *);
        char name[20];

        ENTRY *p, *q;
        q = head;
        p = (ENTRY *) malloc (sizeof(ENTRY));

        printf("Name: ");
        scanf("%s", name); //read user input for name

        while(q != NULL) //checks for unique name
        {
                if(strcmp(name, q->names) == 0)
                {
                        printf("Enter a unique name: ");
                        scanf("%s", name);
                        continue;
                }
                q = q->next;
        }

        printf("Party Size: ");
        scanf("%d", &party); //read user input for party size
        p->next = NULL;
        strcpy(p->names, name); //copies name to the name list
        p->parties = party; //copies the party size to the party list
        printf("%s party of %d has been reserved\n", name, party);

        if(head == NULL && tail == NULL)
        {
                head = p;
                tail = p;
        }
        else
        {
                tail->next = p;
                tail = tail->next;
        }

        return;
}

void delete() //function to remove the oldest reservation that fits the size parameter
{

        int size = 0;
        int flag = 0;
        int i, j;

        ENTRY *p, *q;

        q = p = head;

        if(head == NULL)
        {
                printf("No Reservations\n");
                return;
        }
        else
        {
                printf("Size of the opening: ");
                scanf("%d", &size); //read user input for party size

                while(p != NULL) //iterates through all parties
                {
                        if(p->parties <= size) //finds the first party that fits the open party size
                        {
                                size = size - p->parties;
                                printf("%s with a party of %d is being seated\n", p->names, p->parties);

                                if(p==head)
                                {
                                        head = p->next;
                                        if(head == NULL)
                                        {
                                                tail = NULL;
                                        }
                                        free(p);
                                        p = q = head;
                                        flag = 1;
                                }
                                else
                                {
                                        q->next = p->next;
                                        free(p);
                                        p = q->next;
                                        if(p == NULL)
                                        {
                                                tail = q;
                                        }
                                        flag = 1;
                                }
                        }
                        else
                        {
                                q = p;
                                p = p->next;
                        }
                }
                if(flag == 0)
                {
                        printf("No reservations fit that opening\n");
                        return;
                }
        }
}

void list() //function to list all current reservation names and associated party sizes
{

        ENTRY *p;
        p = head;

        while(p != NULL)
        {
                printf("%s, %d\n", p->names, p->parties);
                p = p->next;
        }
}


void searchSize()
{
        int size = 0;

        ENTRY *p;
        p = head;

        printf("Party Size: ");
        scanf("%d", &size);

        while(p != NULL) //searches all available names
        {
                if(p->parties <= size)
                {
                        printf("%s, %d\n", p->names, p->parties);
                }
                p = p->next;
        }
}
