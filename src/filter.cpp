/*
    filer.cpp - Source file for filter
    Beginning Date : June 23, 2006
    Completion Date : June 23 2006
    Latest Modification : June 23, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// project include files
#include "filter.h"

/**
    Performs IIR filtering with numerator coefficients only.

    coefficients : Array of 2 * order + 1 filter coefficients

    order : order of filtering

    signal : input / output signal

    N : number of samples in the signal
*/
void Filter :: myfilter (double * coefficients, long order, double * signal, long N) {
    long i, j;
    double filtersum;
    for (i = 0; i < N; i ++)
    {
        filtersum = 0;
        for (j = -order; j <= order; j ++)
        {
            if (i + j >= 0 && i + j < N)
                filtersum += coefficients [j + order] * signal [i + j];
        }
        signal [i] = filtersum;
    }
}
