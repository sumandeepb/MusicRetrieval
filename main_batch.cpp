/*
    main_batch.cpp - main routine for batch process module
    Beginning Date : June 20, 2006
    Completion Date : June 20, 2006
    Latest Modification : June 20, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \brief Command line main routine for clubbing mfcc files from multiple audio signals
 into a single consolidated data point collection, required for clustering
*/

// standard include files
#include <stdlib.h>
#include <string.h>

// project include files
#include "common.h"
#include "batch.h"

// main_batch function
int main (int argc, char * argv []) {
    Batch b1;
    char ** filelist;

    filelist = (char **) calloc (argc - 1, sizeof (char *));
    for (long i = 0; i < argc - 1; i++)
        filelist [i] = (char *) calloc (256, sizeof (char));

    for (long i = 0; i < argc - 1; i++)
        strcpy (filelist [i], argv [i + 1]);

    b1.batchUpdate(filelist, argc - 1, 250);

    return (0);
} // end of main_batch function
