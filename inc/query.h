/*
    query.h - Header file for query module. Computes matching song ID and Frame range as per the query snippet
    Beginning Date : June 21, 2006
    Completion Date : June 23, 2006
    Latest Modification : June 28, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Query
    \brief Music video retrieval query

Performs retrieval query of a song snippet on the entire song database. Uses the pre-clustered
classification to reduce search space, thereby signigficantly reducing search time
*/
#if !defined (_QUERY_H)

#define _QUERY_H

#define _QUERYMFCCTEMPFILE "querymfcc.temp"
#define _FILTERORDER 5

#include "mfcc.h"
#include "filter.h"
#include "quicksort.h"

/**
    \struct table1Record
    \brief Song database record

Structure of a single record in the song database. Only the mfcc coefficients are stored in the database
*/
struct table1Record {
    real dataPoint [_CEPSTRALCOEFS];
    char songID [_TAB1SONGIDSIZE];
    long frameID;
};

/**
    \struct table5Record
    \brief Result of query

Structure of a single record in the query result. Contains the rank of the result, song ID, start and end positions of the matching frame sequence
*/
struct table5Record {
    long rank;
    char songID [_TAB1SONGIDSIZE];
    long startFrameID;
    long endFrameID;
};

class Query {
    public:
        long query (short * querySignal, long sampleRate, long numInputSample, table5Record * recordList, long timeFrame = 23);
};

#endif
