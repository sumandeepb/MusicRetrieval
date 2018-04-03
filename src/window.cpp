/*
    window.cpp - Class source file for window filtering. Supports Hamming, ... windows
    Beginning Date : June 1, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 9, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard include files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// project include files
#include "window.h"

/**
    Performs Hamming window filtering. windowHammingUpdateTable is to be called before windowHamming

    insignal : pointer to input signal

    N : order of the window filter

    startIndex : starting index of the window relative to the input signal. Windowing
 done on startIndex to startIndex + N

    outsignal : pointer to the filter output (should be of length N)
*/
void Window :: windowHamming (short int * insignal, long N, long startIndex, short int * outsignal) {
    long i;

    for (i = 0; i < N; i ++)
    {
        // apply filter from lookup table generated by windowHammingUpdateTable
        outsignal [i] = (short int) (double (insignal [i + startIndex]) * hammingTable [i]);
    }
}

/**
    Generates the hamming window lookup table for fast filter operation

    N : order of hamming window to be generated
*/
void Window :: windowHammingUpdateTable (long N) {
    hammingTable = (double *) calloc (N, sizeof (double));
    for (long i = 0; i < N; i ++)
    {
        // generate hamming window coefficients using the formula
        hammingTable [i] = 0.54 - 0.46 * cos (TWOPI * double (i) / double (N - 1));
    }
}
