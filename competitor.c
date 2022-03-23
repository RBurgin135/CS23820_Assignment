/**
 * a collection of functions and struct definitions for handling the competitor data and behaviour
 * also handles event and racetime data
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "competitor.h"
#include "utility.h"

//printing

/**
 * function to list the contact details of a competitor
 * @param comp the competitor
 */
void print_competitor_contact_details(competitor_ptr comp){
    printf("Competitor %d Name: %s, %s\n", comp->competitor_number, comp->surname, comp->given_names);
    printf("Email address: %s\n", comp->email);
    printf("Flyer ID: %s\n\n", comp->flyer_id);
}


/**
 * function to print data of a competitor in the table format described in the brief
 * @param comp the competitor
 */
void print_competitor_table_format(competitor_ptr comp){
    printf("%s %s\t%d\t%s\t%s\n",
           comp->given_names,
           comp->surname,
           comp->competitor_number,
           comp->flyer_id,
           comp->email);
}


/**
 * function to print the track times or state of disqualification of a competitor
 * @param comp the competitor
 */
void print_comp_times(competitor_ptr comp) {
    if(comp->disqualified){
        printf(".disqualified. \n");
        return;
    }
    //iterate through track times
    for(race_time_ptr current_tt = comp->track_times;
        current_tt!=NULL;
        current_tt = current_tt->next){
        format_and_print_time(current_tt->time);
    }
    format_and_print_time(comp->total_time);
    printf("\n");
}


/**
 * formats a provided track time into m:ss.s, then outputs it
 * @param time the track time stored in seconds
 */
void format_and_print_time(double time){
    if(time<=0){
        printf("  -   \t\t");
        return;
    }
    int minutes = 0;
    while(time-60 > 0){
        minutes++;
        time-=60;
    }
    printf("%d:%04.1lf\t\t", minutes, time);
}


/**
 * iterates through the competitor list and outputs the surnames to the standard output,
 * helpful when debugging
 * @param list the competitor linked list
 */
void show_list(competitor_ptr list){
    competitor_ptr current_element = list;
    while(current_element != NULL) {
        printf("%s |", current_element->surname);
        current_element = current_element->next;
    }
    printf("\n");
}

//basic

/**
 * function to add a provided competitor to the competitor list stored in the event struct, and
 * adjust the list length accordingly
 * @param e_ptr pointer referencing a pointer to the event struct holding the competitor list data
 * @param new_comp the competitor to be added
 */
void add_competitor(event_ptr *e_ptr, competitor_ptr new_comp) {
    //add to list
    new_comp->next = (*e_ptr)->competitors;
    new_comp->track_times = NULL;
    (*e_ptr)->competitors = new_comp;
    (*e_ptr)->comp_length++;
    printf("competitor %s %s added\n",new_comp->given_names, new_comp->surname);
}


/**
 * function to remove a competitor from the competitor list stored in the event struct, and adjust
 * the list length accordingly. the competitor will be found using their competitor number
 * @param e_ptr pointer referencing a pointer to the event struct holding the competitor list data
 * @param removal_comp_no the competitor number of the competitor to be removed
 */
void remove_competitor(event_ptr *e_ptr, int removal_comp_no) {
    //search through list
    for (competitor_ptr * current_item_ptr = &(*e_ptr)->competitors;
         *current_item_ptr != NULL;
         current_item_ptr = &((*current_item_ptr)->next)) {
        if((*current_item_ptr)->competitor_number == removal_comp_no){
            //safe remove node
            competitor_ptr removed_node = *current_item_ptr;
            *current_item_ptr = removed_node->next;
            printf("competitor %s %s removed\n",removed_node->given_names, removed_node->surname);
            free(removed_node);
            (*e_ptr)->comp_length--;
            if((*e_ptr)->comp_length == 0) (*e_ptr)->competitors = NULL;
            return;
        }
    }
    printf("\tno competitor found for that number\n");
}


/**
 * safely resets the data for the competitor list
 * @param comp_ptr pointer to the head of the competitor list
 * @param length_ptr pointer to the length of the competitor list
 */
void reset_competitors(competitor_ptr *comp_ptr, int * length_ptr){
    *length_ptr = 0;
    clear_comp(comp_ptr);
}

//sorting

/**
 * function responsible for starting the merge sort
 * @param e_ptr pointer referencing a pointer to the event struct
 * @param f boolean function to sort with
 */
void sort_competitors(event_ptr *e_ptr, int (*f)(competitor_ptr, competitor_ptr)) {
    if((*e_ptr)->competitors == NULL) return;
    (*e_ptr)->competitors = merge_sort((*e_ptr)->competitors, (*e_ptr)->comp_length, *f);
}


/**
 * boolean function to be used in sorting; sorts competitors alphabetically by surname
 */
int sort_by_surname(competitor_ptr left, competitor_ptr right){
    return strcmp(left->surname,right->surname)<0;
}


/**
 * boolean function to be used in sorting; sorts competitors by total time in ascending order,
 * while also placing competitors with no total time stored and disqualified competitors at the bottom of the list
 */
int sort_by_total_time(competitor_ptr left, competitor_ptr right){
    int r_dis = right->disqualified;
    int l_dis = left->disqualified;
    int r_tot = right->total_time==0;
    int l_tot = left->total_time==0;
    int l_is_faster = left->total_time<right->total_time;
    return r_dis || (!l_dis && r_tot) || (!l_tot && l_is_faster);
}


/**
 * function to iterate through a competitors track times and sum them
 * @param comp pointer to the competitor
 */
void find_total_time(competitor_ptr comp){
    comp->total_time = 0;
    for(race_time_ptr t = comp->track_times; t != NULL; t = t->next){
        comp->total_time += t->time;
    }
}


/**
 * recursive function to split competitor lists in half; for use in a merge sort
 * @param f the function which determines the criteria in which the list will be sorted by
 * @return the sorted competitor list
 */
competitor_ptr merge_sort(competitor_ptr list, int length, int (*f)(competitor_ptr, competitor_ptr)) {
    //base case
    if(length == 1) return list;

    //find middle
    int middle = length/2;
    competitor_ptr left, right;
    int left_length = middle;
    int right_length = length - middle;

    //find halves
    left = list;
    competitor_ptr current_element = list;
    for(int i=0; i<left_length-1; i++){
        current_element = current_element->next;
    }
    right = current_element->next;
    current_element->next = NULL;

    //call mergesort for both halves
    left = merge_sort(left, left_length, *f);
    right = merge_sort(right, right_length, *f);

    //merge
    return merge(left, right, *f);
}


/**
 * function to merge two competitor lists back together in a desired order; for use in a merge sort
 * @param f the function which determines the criteria in which the list will be sorted by
 * @return the sorted competitor list
 */
competitor_ptr merge(competitor_ptr left, competitor_ptr right,
                     int (*f)(competitor_ptr, competitor_ptr)) {
    competitor_ptr sorted_list = NULL, hold = NULL;
    while(left!=NULL && right != NULL){
        if((*f)(left, right)){
            hold = left;
            left = left->next;
            hold->next = sorted_list;
            sorted_list = hold;
        } else{
            hold = right;
            right = right->next;
            hold->next = sorted_list;
            sorted_list = hold;
        }
    }
    if(left == NULL) sorted_list = add_all(sorted_list, right);
    else sorted_list = add_all(sorted_list, left);
    return reverse_list(sorted_list);
}

//track

/**
 * function to allow a competitor to receive a new track time; places a placeholder track time in all other
 * competitors, and acts upon disqualification if necessary
 * @param comp_ptr pointer to the competitor list
 * @param comp_no competitor number of the competitor to receive the new track time
 * @param new_time the new track time to be given
 * @param track_name the name of the track the time is associated with
 */
void give_comp_track_time(competitor_ptr *comp_ptr, int comp_no, double new_time, char *track_name) {
    //find competitor
    competitor_ptr current_element;
    for(current_element = *comp_ptr;
        current_element != NULL;
        current_element = current_element->next){
        if(current_element->competitor_number == comp_no) {
            //disqualification check
            if(add_track_time(&(current_element->track_times), new_time, track_name)){
                printf("player raced twice, and is disqualified\n");
                current_element->disqualified = 1;
                clear_tt(&current_element->track_times);
            }
        } else{
            //add placeholder track time
            add_track_time(&(current_element->track_times), 0, track_name);
        }
    }
}


/**
 * adds a track time to the track times linked list, and assesses disqualification
 * if no track time for provided track name is stored
 * @param tt_ptr pointer to the track times linked list
 * @param new_time the new time to be added
 * @param track_name the name of the track the time is associated with
 * @return 1 if the competitor responsible for the track times list should be disqualified
 * 0 if not
 */
int add_track_time(race_time_ptr *tt_ptr, double new_time, char *track_name) {
    race_time_ptr current_tt;
    for(current_tt = *tt_ptr;
        current_tt != NULL;
        current_tt = current_tt->next) {
        //disqualification check
        if(strcmp(current_tt->track_name, track_name) == 0){
            //check if placeholder exists
            if(current_tt->time!=0) return 1; //failure

            //append if placeholder exists
            current_tt->time = new_time;
            return 0; //success
        }
    }

    //add to list
    race_time_ptr new_time_node = malloc(sizeof(race_time));
    new_time_node->time = new_time;
    strcpy(new_time_node->track_name, track_name);
    new_time_node->next = *tt_ptr;
    *tt_ptr = new_time_node;
    return 0; //success
}

