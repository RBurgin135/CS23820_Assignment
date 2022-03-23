#include "macros.h"

//types
#ifndef TRACK
#define TRACK
/**
 * pointer to track struct
 */
typedef struct track_struct track;
typedef track * track_ptr;

/**
 * track struct responsible for holding all information about a track and a pointer to
 * the next item in the tracks linked list
 */
struct track_struct{
    char name[TEXT_LENGTH];
    char date[DATE_LENGTH];
    char time[TIME_LENGTH];

    track_ptr next; //holds the next item in the linked list
};
#endif

//functions

void add_track(track_ptr *tracks_ptr, int *no_of_tracks, char *name,
               char *date, char *time);

int track_in_list(track_ptr * tracks_ptr, char * name);