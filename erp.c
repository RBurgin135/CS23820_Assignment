#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "erp_functions.h"
#include "utility.h"
#include "file_management.h"

/**
 * main function for Entrant Registration Program
 */
int main() {
    time_t t;
    srand((unsigned) time(&t));

    //data
    char current_filename[TEXT_LENGTH];
    event_ptr the_event = malloc(sizeof(event));
    clear_event(&the_event);

    //start menu
    int choice;
    do{
        printf("Enter a choice: \n"
               "\t1. open a competitor file\n"
               "\t2. list competitor table\n"
               "\t3. list competitor contact details\n"
               "\t4. enter a new competitor\n"
               "\t5. remove a competitor\n"
               "\t6. save the current data\n"
               "\t0. exit the program\n");
        choice = input_for_options(7);

        //perform action specified by choice
        switch(choice){
            case 1:
                open_file(&the_event, current_filename, read_from_comp_file);
                break;
            case 2:
                list_competitors(&the_event, print_competitor_table_format);
                break;
            case 3:
                list_competitors(&the_event, print_competitor_contact_details);
                break;
            case 4:
                input_new_competitor(&the_event);
                break;
            case 5:
                input_comp_to_remove(&the_event);
                break;
            case 6:
                save_data_menu(&the_event, current_filename);
                break;
            case 0:
                printf("exiting the program\n");
                break;
            default:
                printf("Invalid -not an option\n");
                break;
        }
    }while(choice!=0);
    clear_comp(&(the_event->competitors));
    clear_event(&the_event);
    printf("Thank you for using the program\n");
    return 0;
}
