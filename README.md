# CS23820_Assignment

This is my submission for my assignment for the C and C++ module for my second year of university. It is a program to help track entrants and performance for a hypothetical drone racing competition. I received an overall mark of 78% for this work, and an overall mark of 84% for the module.

## MAIN PROGRAMS:
### Entrant Registration Program:
It is responsible for handling the data for the event, the competitors, and handling reading and writing to and from the competitor files. It will compile to ERP_Richard_Burgin_CS23820_Assignment.exe . erp.c is the starting file.
In its compilation it uses:
- erp.c
- erp_functions.c
- erp_functions.h
- file_management.c
- file_management.h
- competitor.c
- competitor.h
- utility.c
- utility.h
- track.c
- track.h

### Competition Day Program:
It is responsible for taking in new times, manually or by Lap Timer Results file, and storing it. Then if necessary producing a results table for the user. It will compile to CDP_Richard_Burgin_CS23820_Assignment.exe . cdp.c is the starting file.
In its compilation it uses:
- cdp.c
- cdp_functions.c
- cdp_functions.h
- file_management.c
- file_management.h
- competitor.c
- competitor.h
- utility.c
- utility.h
- track.c
- track.h


## SOURCE AND HEADER FILES:

erp.c: starting file for the ERP and gives the user a textual interface to perform further actions

erp_functions.c: holds functions required only by the ERP.
    erp_function.h is the header file.

gdp.c: starting file for the GDP and gives the user a textual interface to perform further actions.

gdp_functions.c: holds functions required only by the GDP.
    gdp_functions.h is the header file.

file_management.c: holds functions used to interact with files of any kind.
    file_management.h is the header file.

competitor.c: holds functions used to manipulate the event, competitor, and race_time structs, along with the
    instances of the competitor and track_times linked lists.
    competitor.h is the header file and contains struct definitions.

track.c: holds functions used to manipulate the track struct.
    track.h is the header file and contains a struct definition.

utility.c: holds helpful helper functions used throughout the system.
    utility.h is the header file.


## DATA FILES:

Competitor files: stored as a text file these hold the event information on the first 2 lines, then list details for the competitors stored; in format:
```
EVENT_TITLE
EVENT_DATE
COMPETITOR_SURNAME
COMPETITOR_GIVEN NAMES
COMPETITOR_NUMBER
COMPETITOR_FLYER ID
etc for all competitors stored...
```


Lap timer results files: stored as a text file these hold the data for the track, and the competitors track times for that track; in format:
```
TRACK_NAME
RACE_DATE
RACE_TIME
COMPETITOR_NUMBER,TIME  (in m:ss.s)
etc for all track times stored...
```


## LIBRARIES:
The following libraries are used in both programs:
- stdlib.h
- stdio.h
- string.h

The following is only used in the ERP:
- time.h
