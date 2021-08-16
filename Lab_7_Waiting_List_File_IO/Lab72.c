#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insert(char *, int);
int duplicate(char *);
void delete(void);
void list(void);
void searchSize(void);
void read(char *);
void save(char *);
void clearAll(void);

#define ENTRY   struct entry

struct entry
{
        char names[20];
        int parties;
        ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;

int main(int argc, char *argv[1]) //prints and awaits an option using a switch and calls the corresponding function
{
        int answer;
        int party;
        char name[20];

        if(argc==1)
        {
                printf("File is missing\n");
                return 1;
        }

        read(argv[1]);

        while(1)
        {
                printf("MENU\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Size Search\n 0 - Quit\n"); //prints the menu
                scanf("%d", &answer); //read user input
                printf("Option: %d\n", answer);
                switch(answer) //switch for all menu options
                {
                        case 1: //calls insert function
                                printf("Enter a name: ");
                                scanf("%s", name);
                                duplicate(name);
                                printf("Party Size: ");
                                scanf("%d", &party);
                                printf("%s party of %d has been reserved\n", name, party);
                                insert(name, party);
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
                                save(argv[1]);
                                clearAll();
                                return 0;
                        default: //notifies user of an invalid input
                                printf("Please use an available option\n");
                                break;
                }
        }
}

void insert(char *n, int size) //function used to insert a new reservation
{
        ENTRY *p;

        p = (ENTRY *) malloc (sizeof(ENTRY));

        p->next = NULL;
        strcpy(p->names, n); //copies name to the name list
        p->parties = size; //copies the party size to the party list

        if(head == NULL && tail == NULL)
        {
                head = p;
                tail = p;
                p->next = NULL;
        }
        else
        {
                tail->next = p;
                tail = tail->next;
                p->next = NULL;
        }

        return;
}       

int duplicate(char *n)
{
        ENTRY *q;
        q = head;
        
        while(q != NULL)
        {
                if(strcmp(n, q->names) == 0)
                {
                        printf("Enter a unique name: ");
                        scanf("%s", n);
                }
                q = q->next;
        }
        return 0;
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

void read(char *f)
{
        FILE *fptr;
        ENTRY *p;
        int num;
        char name[20];

        fptr = fopen(f, "r");
        if(fptr == NULL)
        {
                printf("File is missing\n");
                return;
        }

        while(fscanf(fptr, "%s %d", name, &num) == 2)
        {
                insert(name, num);
        }
        fclose(fptr);
        printf("Read successful\n");
}

void save(char *f)
{
        FILE *fptr;
        ENTRY *p;
        p = head;

        fptr = fopen(f, "w");

        if(fptr == NULL)
        {
                printf("File is missing");
                return;
        }

        while(p != NULL)
        {
                fprintf(fptr, "%s\t\t%d\n", p->names, p->parties);
                p = p->next;
        }
        fclose(fptr);
        printf("Save Successful\n");

        return;
}

void clearAll()
{
        ENTRY *p;

        p = head;

        while(p != NULL)
        {
                free(p);
                p = p->next;
        }
}

