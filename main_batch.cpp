/*
    Copyright (C) 2006-2018 Sumandeep Banerjee

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
int main_batch (int argc, char * argv []) {
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
