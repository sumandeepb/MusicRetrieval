/*
    filer.h - Header file for filter
    Beginning Date : June 23, 2006
    Completion Date : June 23 2006
    Latest Modification : June 23, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Filter
    \brief IIR filter

    IIR filter having neumerator coefficients and denominator as 1
*/

#if !defined (_FILTER_H)

#define _FILTER_H

class Filter {
    public:
        void myfilter (double * coefficients, long order, double * signal, long N);
};
#endif
