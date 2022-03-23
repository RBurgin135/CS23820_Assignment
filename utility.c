/**
 * a collection of helpful functions used throughout the system
 */

#include <stdlib.h>
#include <stdio.h>
#include "utility.h"


/**
 * function safely clears all the data from a competitor struct
 * @param comp_ptr pointer referencing a pointer to the competitor struct
 */
void clear_comp(competitor_ptr * comp_ptr){
    competitor_ptr current_item = *comp_ptr;
    competitor_ptr hold;
    while(current_item){
        hold = current_item;
        clear_tt(&current_item->track_times);
        current_item = current_item->next;
        free(hold);
    }
    *comp_ptr = NULL;
}


/**
 * function safely clears all the data from a track struct
 * @param t_ptr pointer referencing a pointer to the track struct
 */
void clear_tracks(track_ptr * t_ptr){
    track_ptr current_item = *t_ptr;
    track_ptr hold;
    while(current_item){
        hold = current_item;
        current_item = current_item->next;
        free(hold);
    }
    *t_ptr = NULL;
}


/**
 * function safely clears all the data from a race_time struct
 * @param tt_ptr pointer referencing a pointer to the race_time struct
 */
void clear_tt(race_time_ptr * tt_ptr){
    race_time_ptr current_item = *tt_ptr;
    race_time_ptr hold;
    while(current_item){
        hold = current_item;
        current_item = current_item->next;
        free(hold);
    }
    *tt_ptr = NULL;
}


/**
 * function safely clears all the data from an event struct
 * @param e_ptr pointer referencing a pointer to the event struct
 */
void clear_event(event_ptr * e_ptr){
    (*e_ptr)->title[0] = '\0';
    (*e_ptr)->date[0] = '\0';
    (*e_ptr)->competitors = NULL;
    (*e_ptr)->tracks = NULL;
    (*e_ptr)->comp_length = 0;
}


/**
 * function to ask until a valid int input is received from the user,
 * to provide input validation
 * @return the integer inputted by the user
 */
int validate_int_input(){
    int input;
    char check;
    char ignore;
    int verify;
    while(1) {
        scanf("%d", &input);
        verify = 1;
        check = getchar();
        if (check != EOF && check != '\n') { //if character is found
            printf("Invalid -not a number\n");
            verify = 0;
            scanf("%[^\n]c", &ignore);
        }
        if(verify) return input;
    }
}


/**
 * function to ask until an int input from user which is within 0-no_of_options is provided,
 * for use in menus to prevent user from entering an invalid choice
 * @param no_of_options the upper bound of the allowed input
 * @return the options selected
 */
int input_for_options(int no_of_options){
    //validates int inputs
    int input;
    while(1) {
        input = validate_int_input();
        if (input>=no_of_options || 0>input) {
            printf("Invalid -not an option\n");
            continue;
        }
        return input;
    }
}


/**
 * boolean function to check if there is a competitor with competitor number equal to comp_no
 * @param comp_no competitor number to find
 * @param comp_head pointer to the competitor list
 * @return 1 if there is a competitor with competitor number equal to comp_no, 0 if not
 */
int comp_in_list(int comp_no, competitor_ptr comp_head){
    competitor_ptr current_element = comp_head;
    while(current_element!=NULL){
        if (current_element->competitor_number == comp_no)
            return 0;
        current_element = current_element->next;
    }
    return 1;
}


/**
 * function to add all of one list into another
 * @param comp to list to be appended to
 * @param other list to add all of its contents to another
 * @return comp
 */
competitor_ptr add_all(competitor_ptr comp, competitor_ptr other){
    competitor_ptr hold;
    while(other != NULL){
        hold = other;
        other = other->next;
        hold->next = comp;
        comp = hold;
    }
    return comp;
}


/**
 * takes a competitor list and reverses it
 * @param comp the competitor list
 * @return the reversed list
 */
competitor_ptr reverse_list(competitor_ptr comp){
    competitor_ptr hold = NULL, reversed_list = NULL;
    while(comp != NULL){
        hold = comp;
        comp = comp->next;
        hold->next = reversed_list;
        reversed_list = hold;
    }
    return reversed_list;
}
