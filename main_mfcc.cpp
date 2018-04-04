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
    main_mfcc.cpp - main routine for MFCC module
    Beginning Date : June 1, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 21, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \brief Command line main routine for computing mfcc coefficients of a given wave signal
*/

// standard include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// projet include files
#include "mfcc.h"

// main_mfcc function
int main_mfcc (int argc, char * argv []) {
    MFCC mfcc1;
    Wave w1;
    char * infile, * outfile;
    short * waveData;
    double ** mfccData;

    // process command line parameters
    if (argc < 2 || argc > 3)
    {
		printf ("Command line usage :- \nmfcc infile [timeframe = 23]\n");
        printf ("infile     : input file = infile.wav\n");
        printf ("timeframe  : temporal width (in milliseconds) of each MFCC frame generated\n");
        printf ("Generates mfcc output file = infile.mfcc\n");
        printf ("Note       : Do not provide the extentions. \n\t     .wav and .mfcc extentions are automatically appended");
		exit (0);
    }

    infile = (char *) calloc (strlen (argv [1]) + 5, sizeof (char));
    strcpy (infile, argv [1]);
    strcat (infile, ".wav");
    outfile = (char *) calloc (strlen (argv [1]) + 6, sizeof (char));
    strcpy (outfile, argv [1]);
    strcat (outfile, ".mfcc");

    w1.waveRead(infile);
    waveData = (short *) calloc (w1.getNumChannels() * w1.getNumSamplesPerChannel(), sizeof (short));
    w1.waveLoad(0, w1.getNumSamplesPerChannel(), waveData);
    w1.waveDownmix(waveData, waveData);

    // call mfcc with user specified time frame
    if (argc == 3)
        mfcc1.MFCCcompute (waveData, w1.getSampleRate(), w1.getNumSamplesPerChannel(), mfccData, outfile, (long) atoi (argv [2]));
    // call mfcc with default time frame
    else
        mfcc1.MFCCcompute (waveData, w1.getSampleRate(), w1.getNumSamplesPerChannel(), mfccData, outfile);

    free (infile);
    free (outfile);

    return (0);
} // end of main_mfcc function
