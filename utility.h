#include "competitor.h"
#include "track.h"

void clear_comp(competitor_ptr * comp_ptr);

void clear_tracks(track_ptr * t_ptr);

void clear_tt(race_time_ptr * tt_ptr);

void clear_event(event_ptr * e_ptr);

int validate_int_input();

int input_for_options(int no_of_options);

int comp_in_list(int comp_no, competitor_ptr comp_head);

competitor_ptr add_all(competitor_ptr comp, competitor_ptr other);

competitor_ptr reverse_list(competitor_ptr comp);
