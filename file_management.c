/**
 * a collection of functions to read from and write to text based files
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file_management.h"


/**
 * opens a competitor file, and handles any errors
 * @param e_ptr pointer to event struct
 * @param current_filename string to store the filename of the file to be opened;
 * for use in saving back to that file if necessary
 * @param f function used to read in the data from the file
 * @return if an error has occurred and the file has not been opened, 0 if the file
 * has successfully been opened
 */
int open_file(event_ptr *e_ptr, char *current_filename, void (*f)(FILE *, event_ptr *)) {
    //open file
    printf("Enter the name of the file: \n");
    char filename[TEXT_LENGTH];
    scanf(" %[^\n]s", filename);
    FILE * file = fopen(filename, "r");
    if(file == NULL) {
        printf("- error opening file -\n");
        return 1; //failure
    }
    printf("opening file\n");
    strcpy(current_filename,filename);
    (*f)(file, e_ptr);
    return 0; //success
}


/**
 * reads in the data from the lap timer results file into the event struct
 * @param f pointer to the lap timer results file
 * @param e_ptr pointer referencing a pointer to event struct
 */
void read_from_ltr_file(FILE *f, event_ptr *e_ptr) {
    //record track details
    char name[TEXT_LENGTH];
    char date[DATE_LENGTH];
    char time[TIME_LENGTH];
    fscanf(f, "%s", name);
    fscanf(f, "%s", date);
    fscanf(f, "%s", time);
    add_track(&(*e_ptr)->tracks, &(*e_ptr)->no_of_tracks, name, date, time);

    //record track times
    int comp_no;
    int minutes;
    double seconds;
    do {
        //read in data
        fscanf(f, "%d,%d:%lf\n",&comp_no, &minutes, &seconds);
        give_comp_track_time(&(*e_ptr)->competitors, comp_no, (minutes * 60) + seconds, name);
    } while(!feof(f));
    printf("successfully loaded\n");
    fclose(f);
}


/**
 * reads in the data from the competitor file into the event struct
 * @param f pointer to the competitor file
 * @param e_ptr pointer referencing a pointer to event struct
 */
void read_from_comp_file(FILE *f, event_ptr *e_ptr) {
    //reset
    reset_competitors(&(*e_ptr)->competitors, &(*e_ptr)->comp_length);

    //record event data
    fscanf(f," %[^\n]s", (*e_ptr)->title);
    fscanf(f,"%s", (*e_ptr)->date);

    //record competitor data
    competitor_ptr new_item;
    do {
        new_item = (competitor_ptr) malloc(sizeof(competitor));

        //read in data
        fscanf(f, " %[^\n]s", new_item->surname);
        fscanf(f, " %[^\n]s", new_item->given_names);
        fscanf(f, " %s", new_item->email);
        fscanf(f, "%d", &new_item->competitor_number);
        fscanf(f, " %s", new_item->flyer_id);
        new_item->track_times = NULL;
        new_item->disqualified = 0;

        add_competitor(e_ptr, new_item);
    } while(!feof(f));
    printf("successfully loaded\n");
    fclose(f);
}


/**
 * opens a file and writes all the event and competitor data into it
 * @param e_ptr pointer referencing a pointer to the event struct holding both the event and competitor data
 * @param filename the filename of the file to be written to
 */
void save_comp_file(event_ptr *e_ptr, char *filename) {
    printf("Saving to file: %s\n", filename);

    FILE * f = fopen(filename,"w");
    if(f == NULL){
        printf("- error opening file -");
    }else{
        //record event data
        fprintf(f,"%s\n",(*e_ptr)->title);
        fprintf(f,"%s",(*e_ptr)->date);

        //record competitor data
        competitor_ptr current_item = (*e_ptr)->competitors;
        while (current_item != NULL) {
            fprintf(f, "\n%s\n", current_item->surname);
            fprintf(f, "%s\n", current_item->given_names);
            fprintf(f, "%s\n", current_item->email);
            fprintf(f, "%d\n", current_item->competitor_number);
            fprintf(f, "%s", current_item->flyer_id);
            current_item = current_item->next;
        }
        printf("successfully saved\n");
        fclose(f);
    }
}

