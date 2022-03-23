#include "macros.h"
#include "track.h"

#ifndef COMPETITOR
#define COMPETITOR


//types
/**
 * defining pointers to structs which would be used for linked lists, as well as
 * making code more readable
 */
typedef struct competitor_data_struct competitor;
typedef competitor * competitor_ptr;

typedef struct race_time_struct race_time;
typedef race_time * race_time_ptr;

typedef struct event_struct event;
typedef event * event_ptr;

/**
 * event struct responsible for holding its own details, as well as holding the head
 * to the tracks and competitors linked lists, alongside their lengths
 */
struct event_struct{
    char title[TEXT_LENGTH];
    char date[DATE_LENGTH];

    //contains the data for the competitors
    competitor_ptr competitors;
    int comp_length;

    //contains the data for the tracks
    track_ptr tracks;
    int no_of_tracks;
};

/**
 * race time struct responsible for holding the information for the competitors track times,
 * as well as a pointer to the next item in the linked list
 */
struct race_time_struct {
    double time;
    char track_name[TEXT_LENGTH];

    //links to the next item in the linked list
    race_time_ptr next;
};

/**
 * competitor struct responsible for holding the details of a competitor, as well as the head
 * of the track times linked list and the lists details. it also holds a pointer to the next
 * item in the competitors linked list
 */
struct competitor_data_struct{
    //data stored in file
    char surname[TEXT_LENGTH];
    char given_names[TEXT_LENGTH];
    char email[TEXT_LENGTH];
    char flyer_id[ID_LENGTH];
    int competitor_number;

    //holds the track time linked list
    race_time_ptr track_times;
    double total_time;
    int disqualified;

    //links to the next item in the linked list
    competitor_ptr next;
};
#endif


//functions
//printing

void print_competitor_contact_details(competitor_ptr comp);

void print_competitor_table_format(competitor_ptr comp);

void print_comp_times(competitor_ptr comp);

void format_and_print_time(double time);

void show_list(competitor_ptr list);

//basic

void add_competitor(event_ptr *e_ptr, competitor_ptr new_comp);

void remove_competitor(event_ptr *e_ptr, int removal_comp_no);

void reset_competitors(competitor_ptr *comp_ptr, int * length_ptr);

//sorting

void sort_competitors(event_ptr *e_ptr, int (*f)(competitor_ptr, competitor_ptr));

int sort_by_surname(competitor_ptr left, competitor_ptr right);

int sort_by_total_time(competitor_ptr left, competitor_ptr right);

void find_total_time(competitor_ptr comp);

competitor_ptr merge_sort(competitor_ptr list, int length, int (*f)(competitor_ptr, competitor_ptr));

competitor_ptr merge(competitor_ptr left, competitor_ptr right, int (*f)(competitor_ptr, competitor_ptr));

//track

void give_comp_track_time(competitor_ptr *comp_ptr, int comp_no, double new_time, char *track_name);

int add_track_time(race_time_ptr *tt_ptr, double new_time, char *track_name);

