#include <stdio.h>
#include <stdlib.h>
#include "cdp_functions.h"
#include "file_management.h"
#include "competitor.h"
#include "track.h"
#include "utility.h"

/**
 * main function for Competition Day Program
 */
int main() {
    //data
    char current_comp_filename[TEXT_LENGTH];
    char current_ltr_filename[TEXT_LENGTH];
    event_ptr the_event = malloc(sizeof(event));
    clear_event(&the_event);

    //open comp file
    printf("Open a competitor file \n");
    while(open_file(&the_event, current_comp_filename, read_from_comp_file));

    //menu
    int choice;
    do{
        printf("\nWhat would you like to do: \n"
               "\t1. enter competition results manually\n"
               "\t2. open a lap timer results file\n"
               "\t3. produce competition results table\n"
               "\t0. exit the program\n");
        choice = input_for_options(4);

        //perform action specified by choice
        switch(choice){
            case 1:
                enter_comp_results(&the_event);
                break;
            case 2:
                while(open_file(&the_event, current_ltr_filename, read_from_ltr_file));
                break;
            case 3:
                produce_results_table(&the_event);
                break;
            case 0:
                printf("exiting the program\n");
                break;
            default:
                printf("Invalid -not an option\n");
                break;
        }
    }while(choice!=0);
    clear_comp(&the_event->competitors);
    clear_tracks(&the_event->tracks);
    clear_event(&the_event);
    printf("Thank you for using the program\n");
    return 0;
}

