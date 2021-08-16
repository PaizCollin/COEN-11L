
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int division();

int main() { //chooses 2 random numbers, calls the division function and checks if it returned 1 in order to count the number of correct answers. repeats 10 times

        int i;
        int check;
        int counter = 0;
        int dividend;
        int quotient;
        int divisor;

        srand((int)time(NULL));

        for(i=0; i<10; i++)
        {
                quotient = rand() % 13; //set value for quotient
                divisor = rand() % 12 + 1; //set value for divisor
                check = division(dividend, divisor, quotient); //call division function
                if (check == 1)
                {
                        counter++; //iterate answers correctly up by 1
                }
        }

        printf("You got %d correct! \n", counter);
}

int division(int n1, int n2, int n3) { //determines the dividend based on the divisor and quotient grabbed from the main function. prints the division problem, awaits a response and checks the user's response with the quotient

        int answer;

        n1 = n2 * n3; //set the dividend
        printf("%d / %d = ", n1, n2); //print the problem
        scanf("%d", &answer); //check for response

        if(answer == n3) //check if answer equals the quotient
        {
                printf("Correct! \n"); //print correct
                return 1;
        }
        else
        {
                printf("Incorrect! The correct answer was %d \n", n3); //print correct answer
                return 0;
        }
}
