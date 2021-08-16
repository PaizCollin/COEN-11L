#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insert(void);
void delete(void);
void list(void);
void searchSize(void);
void clearAll(void);

#define ENTRY   struct entry
struct entry
{
        char names[20];
        int parties;
        ENTRY *next;
};

#define LIST    struct list
struct list
{
        ENTRY *head;
        ENTRY *tail;
};

LIST lists[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

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
                                clearAll();
                                return(0);
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
        p = (ENTRY *) malloc (sizeof(ENTRY));

        printf("Name: ");
        scanf("%s", name); //read user input for name

        for(i=0; i<4; i++)
        {
                q = lists[i].head;
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
        }

        printf("Party Size: ");
        scanf("%d", &party); //read user input for party size
        p->next = NULL;

        switch(party)
        {
                case 1:
                case 2:
                        i = 0;
                        break;
                case 3:
                case 4:
                        i = 1;
                        break;
                case 5:
                case 6:
                        i = 2;
                        break;
                default:
                        i = 3;
                        break;
        }

        strcpy(p->names, name); //copies name to the name list
        p->parties = party; //copies the party size to the party list
        p->next = NULL;
        printf("%s party of %d has been reserved\n", name, party);

        if(lists[i].head == NULL && lists[i].tail == NULL)
        {
                lists[i].head = p;
                lists[i].tail = p;
        }
        else
        {
                lists[i].tail->next = p;
                lists[i].tail = lists[i].tail->next;
        }

        return;
}


void delete() //function to remove the oldest reservation that fits the size parameter
{

        int size = 0;
        int flag = 0;
        int i, j;

        ENTRY *p, *q;

        for(i=0; i<4; i++)
        {
                if(lists[i].head == NULL)
                {
                        flag++;
                }
                if(flag == 4)
                {
                        printf("No Reservations\n");
                        return;
                }
        }

        printf("Size of the opening: ");
        scanf("%d", &size); //read user input for party size

        switch(size)
        {
                case1:
                case2:
                        i = 0;
                        break;
                case3:
                case4:
                        i = 1;
                        break;
                case5:
                case6:
                        i = 2;
                        break;
                default:
                        i = 3;

        }

        p = lists[i].head;

        for(j=0; j<4; j++)
        {
                p = lists[j].head;
                while(p != NULL) //iterates through all parties
                {
                        if(p->parties <= size) //finds the first party that fits the open party size
                        {
                                size = size - p->parties;
                                printf("%s with a party of %d is being seated\n", p->names, p->parties);

                                if(p == lists[j].head)
                                {
                                        lists[j].head = p->next;
                                        if(lists[j].head == NULL)
                                        {
                                                lists[j].tail = NULL;
                                        }
                                        free(p);
                                        p = q = lists[j].head;
                                        flag = 1;
                                }
                                else
                                {
                                        q->next = p->next;
                                        free(p);
                                        p = q->next;
                                        if(p == NULL)
                                        {
                                                lists[j].tail = q;
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
        }
                if(flag == 0)
                {
                        printf("No reservations fit that opening\n");
                        return;
                }
}

void list() //function to list all current reservation names and associated party sizes
{

        int i;

        ENTRY *p;

        for(i=0; i<4; i++)
	{
                p = lists[i].head;
                while(p != NULL)
                {
                        printf("%s, %d\n", p->names, p->parties);
                        p = p->next;
                }
        }
}


void searchSize()
{
        int size = 0;
        int i;

        ENTRY *p;

        printf("Party Size: ");
        scanf("%d", &size);

        for(i=0; i<4; i++)
        {
                p = lists[i].head;
                while(p != NULL) //searches all available names
                {
                        if(p->parties <= size)
                        {
                                printf("%s, %d\n", p->names, p->parties);
                        }
                        p = p->next;
                }
        }
}

void clearAll()
{
        int i;

        ENTRY *p;

        for(i=0; i<4; i++)
        {
                p = lists[i].head;

                while(p != NULL)
                {
                        free(p);
                        p = p->next;
                }
        }
}
