////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c division.c mySigHandler.c
// This File:        division.c
// Other Files:      sendsig.c mySigHandler.c
// Semester:         CS 354 SUMMER 2023
// Instructor:       jaso
//
// Author:           Yujin Wang
// Email:            ywang2589@wisc.edu
// CS Login:         yujin
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int count = 0;

void sigint_handler(int signum){
	printf("\nTotal number of operations completed successfully: %i\n", count);
	printf("The program will be terminated.\n");
	exit(EXIT_SUCCESS);
}

void sigfpe_handler(int signum){
	printf("Error: a division by 0 operation was attempted.\n");	
	printf("Total number of operations completed successfully: %i\n", count);
	printf("The program will be terminated.\n");
	exit(EXIT_SUCCESS);
}

int main() {
    char buffer[100];
    int int1;
    int int2;
  
    struct sigaction sigint;
    memset(&sigint, 0, sizeof(sigint));
    sigint.sa_handler = sigint_handler;

    if (sigaction(SIGINT, &sigint, NULL) != 0){
    printf("Signal Error: Unable to handle SIGINT");
    exit(EXIT_FAILURE);
    }

    struct sigaction divide0;
    memset(&divide0, 0, sizeof(divide0));
    divide0.sa_handler = sigfpe_handler;

    if (sigaction(SIGFPE, &divide0, NULL) != 0){
    printf("SIGFPE Error: Unable to handle SIGFPE");
    exit(EXIT_FAILURE);
    }


    while(1) {
        printf("Enter first integer: ");
        fgets(buffer, 100, stdin);
        int1 = strtol(buffer, NULL, 10);

        printf("Enter second integer: ");
        fgets(buffer, 100, stdin);
        int2 = strtol(buffer, NULL, 10);

        printf("%d / %d is %d with a remainder of %d\n", int1, int2, int1/int2, int1%int2);
        count++; 
        
    }

    return 0;
}

