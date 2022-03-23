/**
 * collection of functions and a struct definition responsible for the data and behaviour related to tracks
 */

#include <stdlib.h>
#include <string.h>
#include "track.h"

/**
 * function to add a track to the tracks linked list
 * @param tracks_ptr pointer referencing a pointer to the tracks linked list
 * @param no_of_tracks number of tracks in the tracks linked list
 */
void add_track(track_ptr *tracks_ptr, int *no_of_tracks, char *name,
               char *date,char *time) {
    if(track_in_list(tracks_ptr, name)) return;

    //create new track
    track_ptr new_track = malloc(sizeof (track));
    strcpy(new_track->name, name);
    strcpy(new_track->date, date);
    strcpy(new_track->time, time);

    //add to list
    new_track->next = *tracks_ptr;
    *tracks_ptr = new_track;
    (*no_of_tracks)++;
}


/**
 * boolean function to check if a track of provided name is in the list
 * @param tracks_ptr pointer referencing a pointer to the tracks linked list
 * @param name name of the track to find
 * @return 1 if the track is found in the list, 0 if not
 */
int track_in_list(track_ptr * tracks_ptr, char * name){
    for(track_ptr t = *tracks_ptr;
        t != NULL;
        t= t->next){
        if(strcmp(t->name, name)==0) return 1; //track is in list
    }
    return 0; //track is not in list
}