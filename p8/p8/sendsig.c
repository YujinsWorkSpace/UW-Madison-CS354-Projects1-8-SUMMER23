////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c division.c mySigHandler.c
// This File:        sendsig.c
// Other Files:      division.c mySigHandler.c
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
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // check number of arguments
    if(argc != 3) {
        printf("Usage: sendsig <signal type> <pid>\n");
        return 1;
    }
    // ascii text to int to get pid
    int pid = atoi(argv[2]);
    // for correct signal type
    int signal_type;
    // send sigint for input i
    if(strcmp(argv[1], "-i") == 0) {
        signal_type = SIGINT;
    } else if(strcmp(argv[1], "-u") == 0) { // send sigusr for input u
        signal_type = SIGUSR1;
    } else {
        // invalid input
        printf("Invalid signal type. Use -i for SIGINT or -u for SIGUSR1.\n");
        return 1;
    }
    // failed to send signal
    if(kill(pid, signal_type) == -1) {
        perror("Error sending signal");
        return 1;
    }

    return 0;
}

