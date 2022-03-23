#include "competitor.h"


int open_file(event_ptr *e_ptr, char *current_filename, void (*f)(FILE *, event_ptr *));

void read_from_ltr_file(FILE *f, event_ptr *e_ptr);

void read_from_comp_file(FILE *f, event_ptr *e_ptr);

void save_comp_file(event_ptr *e_ptr, char *filename);

