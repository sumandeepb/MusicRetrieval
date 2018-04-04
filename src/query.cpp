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
    query.cpp - Source file for query module. Computes matching song ID and Frame range as per the query snippet
    Beginning Date : June 21, 2006
    Completion Date : June 23, 2006
    Latest Modification : June 28, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// project include files
#include "common.h"
#include "query.h"
#include "mfcc.h"
#include "quicksort.h"
#include "filter.h"

/**
    Performs query processing and search

    querySignal : input time domain audio signal used as a query
    sampleRate : sampling rate of the query signal
    numInputSamples : number of samples in the query input signal
    recordList : Ranked ist of winner records
    timeframe : Duration (in miliseconds) of audio signal taken one mfcc vector, default value is 23ms

    Return value : number of records in the recordList
*/
long Query :: query (short * querySignal, long sampleRate, long numInputSamples, table5Record * recordList, long timeFrame) {
    MFCC mfcc1;
    Filter fil1;
    QuickSort sort1;
    FILE *queryFp, *tab1Fp, *tab2Fp, *tab3Fp, *tab4Fp, *tab5Fp;
    double **mean, **queryData, distance, minDistance, **mfccData;
    double *frameString, *tempframeString, *coefficients, prevMatch, currMatch, rankValue;
    long N, K, D, n, k, d, i, j, c, RecordSize, *queryWinnerList, winnerID, queryWinnerID, dataPointID, iterations;
    long numWinnerDataPoints, *winnerDataPoints, maxFrameID, minRecordID, maxRecordID, startFrameID, endFrameID, numResults;
    char stringBuffer [_TAB1SONGIDSIZE+1];
    table1Record *winnerRecord, tempRecord;
    table5Record resultRecord;

    // compute mfcc coefficients of query audio signal
    mfcc1.MFCCcompute(querySignal, sampleRate, numInputSamples, mfccData, _QUERYMFCCTEMPFILE, timeFrame);
    D = _CEPSTRALCOEFS;

    if (!(tab2Fp = fopen (_TABLE2NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE2NAME);		// print error message
		exit (0);
    }

    fseek (tab2Fp, 0, SEEK_END);
    RecordSize = _TAB2RECORDSIZE;
    K = ftell (tab2Fp) / RecordSize;

    // allocate space for K means with dimention D
    mean = (double **) calloc (K, sizeof (double *));
    for (k = 0; k < K; k ++)
        mean [k] = (double *) calloc (D, sizeof (double));

    fseek (tab2Fp, 0, SEEK_SET);
    for (k = 0; k < K; k ++)
        fread (mean [k], sizeof (real), D, tab2Fp);

    fclose (tab2Fp);

    if (!(queryFp = fopen (_QUERYMFCCTEMPFILE, "rb")))
    {
        printf ("Can't open file %s\n", _QUERYMFCCTEMPFILE);		// print error message
		exit (0);
    }

    fseek (queryFp, 0, SEEK_END);
    RecordSize = _TAB2RECORDSIZE;
    N = ftell (queryFp) / RecordSize;

    // allocate space for N data points with dimention D
    queryData = (double **) calloc (N, sizeof (double *));
    for (n = 0; n < N; n ++)
        queryData [n] = (double *) calloc (D, sizeof (double));

    fseek (queryFp, 0, SEEK_SET);
    for (n = 0; n < N; n ++)
        fread (queryData [n], sizeof (real), D, queryFp);

    fclose (queryFp);

    queryWinnerList = (long *) calloc (N, sizeof (long));

    // select winners for each data point
    for (n = 0; n < N; n ++)
    {
        for (k = 0; k < K; k ++)
        {
            distance = 0.0;
            for (d = 0; d < D; d ++)
            {
                distance += (queryData [n][d] - mean [k][d]) * (queryData [n][d] - mean [k][d]);
            }

            // Euclidean distance between nth data point and kth mean
            distance = sqrt (distance);
            if (k == 0 || distance < minDistance)
            {
                minDistance = distance;
                // index of the winner mean
                winnerID = k;
            }
        }

        queryWinnerList [n] = winnerID;
    }

    sort1.quickSort (queryWinnerList, N);

    if (!(tab3Fp = fopen (_TABLE3NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE3NAME);		// print error message
		exit (0);
    }

    if (!(tab4Fp = fopen (_TABLE4NAME, "wb")))
    {
        printf ("Can't open file %s\n", _TABLE4NAME);		// print error message
		exit (0);
    }

    n = 0;
    queryWinnerID = queryWinnerList [0];
    fread (&winnerID, sizeof (long), 1, tab3Fp);
    fread (&dataPointID, sizeof (long), 1, tab3Fp);

    while (1)
    {
        if (winnerID < queryWinnerID)
        {
            fread (&winnerID, sizeof (long), 1, tab3Fp);
            fread (&dataPointID, sizeof (long), 1, tab3Fp);
            continue;
        }
        else if (winnerID == queryWinnerID)
        {
            fwrite (&dataPointID, sizeof (long), 1, tab4Fp);
            fread (&winnerID, sizeof (long), 1, tab3Fp);
            fread (&dataPointID, sizeof (long), 1, tab3Fp);
            continue;
        }
        else if (winnerID > queryWinnerID)
        {
            n ++;
            queryWinnerID = queryWinnerList [n];
        }

        if (n >= N || feof (tab3Fp))
            break;

    }

    fclose (tab3Fp);
    fclose (tab4Fp);

    if (!(tab4Fp = fopen (_TABLE4NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE4NAME);		// print error message
		exit (0);
    }

    fseek (tab4Fp, 0, SEEK_END);
    numWinnerDataPoints = ftell (tab4Fp) / sizeof (long);
    winnerDataPoints = (long *) calloc (numWinnerDataPoints, sizeof (long));

    fseek (tab4Fp, 0, SEEK_SET);
    fread (winnerDataPoints, sizeof (long), numWinnerDataPoints, tab4Fp);

    sort1.quickSort (winnerDataPoints, numWinnerDataPoints);

    fclose (tab4Fp);

    if (!(tab1Fp = fopen (_TABLE1NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE1NAME);		// print error message
		exit (0);
    }

    RecordSize = _TAB1RECORDSIZE;

    winnerRecord = (table1Record *) calloc (numWinnerDataPoints, sizeof (table1Record));
    for (i = 0; i < numWinnerDataPoints; i ++)
    {
        fseek (tab1Fp, winnerDataPoints [i] * RecordSize, SEEK_SET);
        fread (winnerRecord [i].dataPoint, sizeof (real), _CEPSTRALCOEFS, tab1Fp);
        fread (winnerRecord [i].songID, sizeof (char), _TAB1SONGIDSIZE, tab1Fp);
        fread (&winnerRecord [i].frameID, sizeof (long), 1, tab1Fp);
    }

    coefficients = (double *) calloc (_FILTERORDER * 2 + 1, sizeof (double));
    for (j = -_FILTERORDER; j <= _FILTERORDER; j ++)
    {
        coefficients [j + _FILTERORDER] = 1.0 / ((double)_FILTERORDER * 2.0 + 1.0);
    }

    i = 0;
    tempRecord = winnerRecord [i];
    minRecordID = i;
    
    if (!(tab5Fp = fopen (_TABLE5NAME, "wb")))
    {
        printf ("Can't open file %s\n", _TABLE5NAME);		// print error message
		exit (0);
    }

    while (1)
    {
        if (i == numWinnerDataPoints || memcmp (tempRecord.songID, winnerRecord [i].songID, _TAB1SONGIDSIZE) != 0)
        {
            maxFrameID = winnerRecord [i - 1].frameID;
            if (frameString != NULL)
                free (frameString);
            if (tempframeString != NULL)
                free (tempframeString);
            frameString = (double *) calloc (maxFrameID + 1, sizeof (double));
            tempframeString = (double *) calloc (maxFrameID + 1, sizeof (double));
            maxRecordID = i;
            for (j = 0; j <= maxFrameID; j ++)
            {
                 frameString [j] = 0.0;
            }
            for (j = minRecordID; j < maxRecordID; j ++)
                frameString [winnerRecord [j].frameID] = 1.0;

            // do processing on the bit string ... apply
            memcpy (tempframeString, frameString, (maxFrameID + 1) * sizeof (double));
            fil1.myfilter (coefficients, _FILTERORDER, frameString, maxFrameID);
            for (j = 0; j <= maxFrameID; j ++)
            {
                if (frameString [j] >= 0.5)
                    frameString [j] = 1.0;
                else
                    frameString [j] = 0.0;
            }

            // find matching frame sequences
            prevMatch = 0.0;
            for (j = 0; j <= maxFrameID; j++)
            {
                currMatch = frameString [j];
                if (prevMatch == 0.0 && currMatch == 1.0)
                {
                    startFrameID = j;
                    prevMatch = currMatch;
                }
                if (prevMatch == 1.0 && currMatch == 0.0)
                {
                    endFrameID = j;
                    prevMatch = currMatch;
                    rankValue = 0.0;
                    for (c = startFrameID; c < endFrameID; c++)
                    {
                        if (frameString [c] != tempframeString [c])
                            rankValue += 1.0;
                    }
                    rankValue /= (double)(endFrameID - startFrameID);
                    if ((endFrameID - startFrameID) > N / 2)
                    {
                        resultRecord.rank = (long)(100.0 * rankValue);
                        resultRecord.startFrameID = startFrameID;
                        resultRecord.endFrameID = endFrameID;
                        memcpy (resultRecord.songID, tempRecord.songID, _TAB1SONGIDSIZE);
                        fwrite (&resultRecord.rank, sizeof (long), 1, tab5Fp);
                        fwrite (resultRecord.songID, sizeof (char), _TAB1SONGIDSIZE, tab5Fp);
                        fwrite (&resultRecord.startFrameID, sizeof (long), 1, tab5Fp);
                        fwrite (&resultRecord.endFrameID, sizeof (long), 1, tab5Fp);
                    }
                }
            }

            tempRecord = winnerRecord [i];
            minRecordID = i;
        }
        i ++;
        if (i > numWinnerDataPoints)
            break;
    }

    fclose (tab5Fp);
    fclose (tab1Fp);

    if (!(tab5Fp = fopen (_TABLE5NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE5NAME);		// print error message
		exit (0);
    }

    long * rankList;

    fseek (tab5Fp, 0, SEEK_END);
    RecordSize = _TAB5RECORDSIZE;
    numResults = ftell (tab5Fp) / RecordSize;
    fseek (tab5Fp, 0, SEEK_SET);

    recordList = (table5Record *) calloc (numResults, sizeof (table5Record));
    rankList = (long *) calloc (numResults, sizeof (long));
    for (i = 0; i < numResults; i ++)
    {
        fread (&recordList[i].rank, sizeof (long), 1, tab5Fp);
        fread (recordList[i].songID, sizeof (char), _TAB1SONGIDSIZE, tab5Fp);
        fread (&recordList[i].startFrameID, sizeof (long), 1, tab5Fp);
        fread (&recordList[i].endFrameID, sizeof (long), 1, tab5Fp);
    }

    for (i = 0; i < numResults; i ++)
    {
        for (j = 0; j < numResults - 1; j ++)
        {
            if (recordList[j].rank > recordList[j + 1].rank)
            {
                memcpy (&resultRecord, &recordList[j], sizeof (table5Record));
                memcpy (&recordList[j], &recordList[j + 1], sizeof (table5Record));
                memcpy (&recordList[j + 1], &resultRecord, sizeof (table5Record));
            }
        }
    }

    fclose (tab5Fp);

    if (!(tab5Fp = fopen (_TABLE5NAME, "wb")))
    {
        printf ("Can't open file %s\n", _TABLE5NAME);		// print error message
		exit (0);
    }

    // output needs to be modified as per the requirement of the interface
    // presently we have file output to table5.tab, screen display, as well as return the array of ranked list
    // apprepriate lines need to be commented out after deciding on the output
    printf ("Rank Normalized Hamming Distance Match Length (sec) SongID     start position (sec)   end position (sec)\n");
    for (i = 0; i < numResults; i ++)
    {
        fwrite (&recordList[i].rank, sizeof (long), 1, tab5Fp);
        fwrite (recordList[i].songID, sizeof (char), _TAB1SONGIDSIZE, tab5Fp);
        fwrite (&recordList[i].startFrameID, sizeof (long), 1, tab5Fp);
        fwrite (&recordList[i].endFrameID, sizeof (long), 1, tab5Fp);

        strncpy (stringBuffer, recordList[i].songID, _TAB1SONGIDSIZE);
        stringBuffer [_TAB1SONGIDSIZE] = '\0';
        printf ("%4d %27d %18d %s %20d %18d\n", i,  recordList[i].rank, (recordList[i].endFrameID - recordList[i].startFrameID) / (1000 / timeFrame), stringBuffer, recordList[i].startFrameID / (1000 / timeFrame), recordList[i].endFrameID / (1000 / timeFrame));
    }

    fclose (tab5Fp);
    return (numResults);
}
