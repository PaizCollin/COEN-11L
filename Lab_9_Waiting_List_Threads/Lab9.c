#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define ENTRY   struct entry

struct entry
{
        char names[20];
        int parties;
        ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;

pthread_mutex_t mutex;

void insert(char *, int);
int duplicate(char *);
void delete(void);
void list(void);
void searchSize(void);
void rread(char *);
void save(char *);
void clearAll(ENTRY *);
void backwardsList(ENTRY *);
void backwardsNames(char *);
void *autoSave(void *);
void readAutoSaved(char *);

int main(int argc, char *argv[]) //prints and awaits an option using a switch and calls the corresponding function
{
        int answer;
        int party;
        char name[20];

        ENTRY *p;
        p = head;

        pthread_t thr;
        pthread_mutex_init(&mutex, NULL);
        pthread_create(&thr, NULL, autoSave,(void*) argv[2]);

        if(argc==1)
        {
                printf("File is missing\n");
                return 1;
        }

        rread(argv[1]);

        while(1)
        {
                printf("MENU\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Size Search\n 5 - List Backwards\n 6 - Names Backwards\n 7 - Binary File\n 0 - Quit\n"); //prints the menu
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
                                pthread_mutex_lock(&mutex);
                                insert(name, party);
                                pthread_mutex_unlock(&mutex);
                                break;
                        case 2: //calls delete function
                                pthread_mutex_lock(&mutex);
                                delete();
                                pthread_mutex_unlock(&mutex);
                                break;
                        case 3: //calls list function
                                list();
                                break;
                        case 4: //calls search size function
                                searchSize();
                                break;
                        case 5: //calls backwards list function
                                backwardsList(head);
                                break;
                        case 6:
                                p = head;
                                while(p != NULL)
                                {
                                        backwardsNames(p->names);
                                        p = p->next;
                                        printf("\n");
                                }
                                break;
                        case 7:
                                readAutoSaved(argv[2]);
                                break;
                        case 0: //ends program
                                pthread_mutex_lock(&mutex);
                                pthread_cancel(thr);
                                save(argv[1]);
                                pthread_mutex_unlock(&mutex);
                                clearAll(head);
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

void rread(char *f)
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

void clearAll(ENTRY *p)
{
        if(p == NULL)
        {
                return;
        }
        else
        {
                clearAll(p->next);
        }
        free(p);
        return;
}

void backwardsList(ENTRY *p)
{
        if(p == NULL)
        {
                return;
        }
        else
        {
                backwardsList(p->next);
        }
        printf("%s, %d\n", p->names, p->parties);
        return;
}

void backwardsNames(char *n)
{
        if(*n == '\0')
        {
                return;
        }
        else
        {
                backwardsNames(n+1);
        }
        printf("%c", *n);
        return;
}

void *autoSave(void *arg)
{
        char *file_name = (char *)arg;
        FILE *fptr;
        ENTRY *p;

        while(1) //write to binary file
        {
                pthread_mutex_lock(&mutex);

                fptr = fopen(file_name, "wb");
                if(fptr == NULL)
                {
                        printf("Error writing to file\n");
                }

                p = head;
                while(p != NULL)
                {
                        fwrite(p, sizeof(ENTRY), 1, fptr);
                        p = p->next;
                }
                printf("\nAutosave complete\n");

                fclose(fptr);

                pthread_mutex_unlock(&mutex);

                sleep(15);
        }
}

void readAutoSaved(char *f)
{
        FILE *fptr;
        ENTRY temp;

        fptr = fopen(f, "rb");
        if(fptr == NULL)
        {
                printf("File is missing\n");
                return;
        }

        while(fread(&temp, sizeof(ENTRY), 1, fptr) == 1)
        {
                printf("%s, %d\n", temp.names, temp.parties);
        }
        fclose(fptr);
        return;
}
