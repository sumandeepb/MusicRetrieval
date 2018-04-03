/*
    common.h - common header file for Music Retrieval Modules
    Beginning Date : June 20, 2006
    Completion Date : Juen 20, 2006
    Latest Modification : June 23,2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \brief Constant definitions commonly shared by the project files
*/
#if !defined (_COMMON_H)

#define _COMMON_H

#define real double
#define natural long
#define PI 3.14159265359f
#define TWOPI 6.28318530718f

// mfcc parameters
#define WINDOWSIZE 512L
#define WINDOWOVERLAP 256L
#define _CEPSTRALCOEFS 13

// table 1 parameters : Table of data points with SONG ID and FRAME ID
#define _TABLE1NAME "table1.tab"
#define _TAB1DATASIZE _CEPSTRALCOEFS * sizeof (real)
#define _TAB1SONGIDSIZE 9
#define _TAB1FRAMEIDSIZE sizeof (long)
#define _TAB1RECORDSIZE _TAB1DATASIZE+_TAB1SONGIDSIZE+_TAB1FRAMEIDSIZE

// table 2 parameters : Table of Cluster Centers
#define _TABLE2NAME "table2.tab"
#define _TAB2DATA _CEPSTRALCOEFS
#define _TAB2RECORDSIZE _CEPSTRALCOEFS * sizeof (real)

// table 3 parameters : Table of responsibility of each cluster center to data points
#define _TABLE3NAME "table3.tab"

// table 4 parameters : Table of data points ID's  matching the query. Refer to table 1 for the actual data point params
#define _TABLE4NAME "table4.tab"

// table 5 parameters : Table of query result, frame sequences that match the query
#define _TABLE5NAME "table5.tab"
#define _TAB5RECORDSIZE _TAB1SONGIDSIZE + 3 * sizeof (long)

#endif
