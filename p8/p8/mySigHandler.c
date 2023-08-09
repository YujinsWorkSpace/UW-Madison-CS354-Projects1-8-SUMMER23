////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c division.c mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      division.c sendsig.c
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
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

volatile sig_atomic_t alarm_seconds = 4;  // global variable for alarm seconds
volatile sig_atomic_t sigusr1_count = 0;  // global variable for SIGUSR1 count

// signal handler function for SIGALRM
void alarm_handler(int signal) {
    pid_t pid = getpid();
    time_t current_time;
    char *c_time_string;

    // get the current time
    current_time = time(NULL);

    // convert to local time format
    c_time_string = ctime(&current_time);

    // print PID and current time
    printf("PID: %d CURRENT TIME: %s", pid, c_time_string);

    // re-arm the alarm
    alarm(alarm_seconds);
}

// signal handler function for SIGUSR1
void sigusr1_handler(int signal) {
    sigusr1_count += 1;
    printf("SIGUSR1 handled and counted!\n");

    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_handler = sigusr1_handler;

}

// signal handler function for SIGINT
void sigint_handler(int signal) {
    printf("\nSIGINT handled.\nSIGUSR1 was handled %d times. Exiting now.\n", sigusr1_count);
    exit(0);
}

int main() {
    struct sigaction act;
    // setup the sigaction struct for act
    memset(&act, 0, sizeof(act));
    act.sa_handler = &alarm_handler;
    act.sa_flags = SA_RESTART;
    if(sigaction(SIGALRM, &act, NULL) != 0) {
        perror("Error: cannot handle SIGALRM");
        return 1;
    }

    // setup the sigaction struct for SIGUSR1
    memset(&act, 0, sizeof(act));
    act.sa_handler = &sigusr1_handler;
    act.sa_flags = SA_RESTART;
    if(sigaction(SIGUSR1, &act, NULL) != 0) {
        perror("Error: cannot handle SIGUSR1");
        return 1;
    }

    // setup the sigaction struct for SIGINT
    memset(&act, 0, sizeof(act));
    act.sa_handler = &sigint_handler;
    act.sa_flags = SA_RESTART;
    if(sigaction(SIGINT, &act, NULL) != 0) {
        perror("Error: cannot handle SIGINT");
        return 1;
    }

    // set the alarm
    alarm(alarm_seconds);

    // print the instructions to the user
    printf("PID and time print every 4 seconds.\n");
    printf("Type Ctrl-C to end the program.\n");

    // enter an infinite loop
    while(1) {
    }

    return 0;
}

