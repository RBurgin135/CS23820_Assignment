/**
 * collection of functions to carry out tasks exclusive to the ERP program
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utility.h"
#include "file_management.h"
#include "erp_functions.h"

/**
 * gives a textual interface to allow the user to either save the current
 * data to the original file or to create a new event and save it to that
 * @param e_ptr pointer referencing a pointer to the event struct
 * @param current_filename filename for the currently opened competitor file
 * if applicable
 */
void save_data_menu(event_ptr *e_ptr, char *current_filename) {
    int choice;
    do {
        printf("Enter a choice: \n"
               "\t1. save the data to the current file\n"
               "\t2. save the data to a new event\n"
               "\t0. go back\n");
        choice = input_for_options(3);
        switch (choice) {
            case 1:
                if(strlen(current_filename)==0) printf("- Invalid -no file open -\n");
                else save_comp_file(e_ptr, current_filename);
                choice = 0;
                break;
            case 2:
                create_event(e_ptr, current_filename);
                choice = 0;
                break;
            case 0:
                printf("\tgoing back\n");
                break;
            default:
                printf("- Invalid -not an option -\n");
                break;
        }
    }while(choice!=0);
}


/**
 * function to allow the user to input a new competitor
 * @param e_ptr pointer referencing a pointer to the event struct
 */
void list_competitors(event_ptr * e_ptr, void (*f)(competitor_ptr)){
    //show event data
    if (strlen((*e_ptr)->title) == 0) printf("- No event data stored -\n");
    else printf("Competition: %s\t Date: %s\n", (*e_ptr)->title, (*e_ptr)->date);

    //sort competitor data
    sort_competitors(e_ptr, sort_by_surname);

    //show heading
    if(*f== print_competitor_table_format) {
        printf("NAME \tCompetitor No\tFlyer ID\tEmail\n"
               "=========================================================================================\n");
    } else if (*f == print_competitor_contact_details){
        printf("Competitor contact details\n");
    }

    //show competitor data
    if ((*e_ptr)->competitors == NULL) printf("- No competitor data stored -\n");
    else {
        for (competitor_ptr current_element = (*e_ptr)->competitors;
             current_element != NULL;
             current_element = current_element->next) {
            (*f)(current_element);
        }
    }
}


/**
 * function to allow the user to input a competitor to remove
 * @param e_ptr pointer referencing a pointer to the event struct
 */
void input_new_competitor(event_ptr *e_ptr) {
    competitor_ptr temp = malloc(sizeof(competitor));
    printf("Creating a new competitor:\n");

    //input chars
    printf("\tenter the surname:");
    scanf(" %[^\n]s", temp->surname);
    printf("\tenter the given title(s):");
    scanf(" %[^\n]s", temp->given_names);
    printf("\tenter the email:");
    scanf(" %s", temp->email);
    printf("\tenter the flyer ID:");
    scanf(" %s", temp->flyer_id);

    //generate comp number
    int generated_comp_no = (rand()%((*e_ptr)->comp_length+1))+1; //random number between 1 and competitor length
    while (!comp_in_list(generated_comp_no, (*e_ptr)->competitors))
        generated_comp_no = (rand()%((*e_ptr)->comp_length+1))+1; //make sure the competitor number is unique
    printf("\tgenerated competitor number is %d\n", generated_comp_no);
    temp->competitor_number = generated_comp_no;

    //exit function
    add_competitor(e_ptr, temp);
}


/**
 * function to allow the user to input new event data
 * @param event_title reference to the current event title to be changed
 * @param event_date reference to the current event date to be changed
 */
void input_comp_to_remove(event_ptr *e_ptr) {
    int removal_comp_no;
    printf("Removing competitor:\n");
    //check
    if ((*e_ptr)->competitors == NULL) {
        printf("- No competitor data stored -\n");
    }
    //remove
    printf("\tenter competitor number of the competitor to remove:\n");
    removal_comp_no = validate_int_input();
    remove_competitor(e_ptr, removal_comp_no);
}


/**
 * function responsible for creating a new event and saving the relevant information
 * to a competitor file
 * @param e_ptr pointer referencing a pointer to the event struct
 * @param current_filename filename for the currently opened competitor file
 * if applicable
 */
void input_event_data(char *event_title, char *event_date){
    //reset data
    event_title[0] = '\0';
    event_date[0] = '\0';

    //title
    printf("\tenter the event title:\n");
    scanf(" %[^\n]s",event_title);

    //date
    char day[3], month[3], year[5];
    printf("\tenter the day (dd): \n");
    scanf("%s", day);
    printf("\tenter the month (mm): \n");
    scanf("%s", month);
    printf("\tenter the year (yyyy): \n");
    scanf("%s", year);
    strcat(event_date,day), strcat(event_date,"/"), strcat(event_date,month), strcat(event_date,"/"), strcat(event_date,year);
}


/**
 * function to allow printing of event and competitor information in a provided format
 * @param e_ptr pointer referencing a pointer to the event struct
 * @param f function providing the formatting
 */
void create_event(event_ptr *e_ptr, char *current_filename) {
    printf("Creating a new event:\n");
    char * event_title = (*e_ptr)->title;
    char * event_date = (*e_ptr)->date;

    //create file
    char filename[30];
    printf("\tenter the title for the new file:\n");
    scanf(" %[^\n]s",filename);
    FILE * f = fopen(filename, "r");
    if (f){ //if file of filename exists
        fclose(f);
        printf("\tthere already exists a file of that title, enter what to do:"
               "\n\t\t0. abort save\n\t\t1. overwrite file\n");
        int choice = input_for_options(2);
        if(choice == 0) printf("\taborting\n");
        else if(choice == 1) {
            input_event_data(event_title, event_date);
            save_comp_file(e_ptr, filename);
            strcpy(current_filename, filename);
        }
        else printf("\tInvalid -not a choice, aborting\n");
    } else { //if file does not already exist
        input_event_data(event_title, event_date);
        save_comp_file(e_ptr, filename);
    }
}