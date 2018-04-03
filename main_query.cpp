/*
    main_query.cpp - main routine for query module.
    Beginning Date : June 21, 2006
    Completion Date : June 23, 2006
    Latest Modification : June 23, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \brief Commandline main routine for performing retrieval query
*/
// standard include files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// project include files
#include "common.h"
#include "query.h"

int main (int argc, char * argv []) {
    Query q1;
    clock_t t1, t2;
    Wave w1;
    short * waveData;
    table5Record * result;

    t1 = clock ();
    w1.waveRead(argv [1]);
    waveData = (short *) calloc (w1.getNumChannels() * w1.getNumSamplesPerChannel(), sizeof (short));
    w1.waveLoad(0, w1.getNumSamplesPerChannel(), waveData);
    w1.waveDownmix(waveData, waveData);
    q1.query (waveData, w1.getSampleRate (), w1.getNumSamplesPerChannel(), result, 250);
    t2 = clock ();
    printf ("Time for executing query (%s) was %5.3f seconds", argv [1], ((double)t2 - (double)t1) / (double)CLK_TCK);
}
