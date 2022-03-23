/**
 * collection of functions to carry out tasks exclusive to the ERP program
 */

#include "competitor.h"

void save_data_menu(event_ptr *e_ptr, char *current_filename);

void list_competitors(event_ptr * e_ptr, void (*f)(competitor_ptr));

void input_new_competitor(event_ptr *e_ptr);

void input_comp_to_remove(event_ptr *e_ptr);

void input_event_data(char *event_title, char *event_date);

void create_event(event_ptr *e_ptr, char *current_filename);