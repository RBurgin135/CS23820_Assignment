/**
 * collection of functions to carry out tasks exclusive to the CDP program
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "utility.h"
#include "file_management.h"
#include "competitor.h"
#include "cdp_functions.h"
#include "track.h"

/**
 * allows the user to manually enter the track data, as well as the competitor results
 * @param e_ptr pointer referencing a pointer to the event struct holding both the
 * tracks and competitor linked lists
 */
void enter_comp_results(event_ptr *e_ptr) {
    printf("Manually entering competition results:\n");

    //record track details
    char name[TEXT_LENGTH];
    char date[DATE_LENGTH];
    char time[TIME_LENGTH];
    printf("\tenter the title of the track:\n");
    scanf("%s", name);
    printf("\tenter the track date:\n");
    scanf("%s", date);
    printf("\tenter the track time:\n");
    scanf("%s", time);
    add_track(&(*e_ptr)->tracks, &(*e_ptr)->no_of_tracks, name, date, time);

    //record track times
    printf("manually enter details for the competitors:\n");
    int comp_no;
    int minutes;
    double seconds;
    while(1) {
        printf("\tenter the competitor number(0 to exit):\n");
        comp_no = validate_int_input();
        if(comp_no == 0) return;
        printf("\tenter the time:\n");
        scanf("%d:%lf",&minutes,&seconds);
        give_comp_track_time(&(*e_ptr)->competitors, comp_no, (minutes * 60) + seconds, name);
    }
}


/**
 * function to format the results table and present it to the user
 * @param e_ptr pointer referencing a pointer to the event struct holding all the event,
 * competitor and track data
 */
void produce_results_table(event_ptr *e_ptr) {
    printf("Showing results table:\n");
    for(competitor_ptr c = (*e_ptr)->competitors; c!=NULL; c=c->next){
        find_total_time(c);
    }
    sort_competitors(e_ptr, sort_by_total_time);

    //event details
    if (strlen((*e_ptr)->title) == 0) printf("- No event data stored -\n");
    else printf("Competition: %s\t Date: %s\n", (*e_ptr)->title, (*e_ptr)->date);

    //headings
    printf("NAME\t\t\t\t\tComp No");
    // + track names
    for(track_ptr track_node = (*e_ptr)->tracks; track_node!=NULL; track_node = track_node->next){
        printf("\t\t%s", track_node->name);
    }
    printf("\t\tTotal\n");

    //competitor
    if ((*e_ptr)->competitors == NULL) {
        printf("- No competitor data stored -\n");
        return;
    }
    printf("======================================================================\n");
    for(competitor_ptr current_element = (*e_ptr)->competitors;
        current_element!=NULL;
        current_element = current_element->next){
        //details
        printf("%s %s%*s%d\t",
               current_element->given_names,
               current_element->surname,
               (TEXT_LENGTH)-(int) strlen(current_element->given_names)
               -(int)strlen(current_element->surname),
               "",
               current_element->competitor_number);

        //track times
        print_comp_times(current_element);
    }
}