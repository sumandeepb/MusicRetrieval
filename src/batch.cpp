/*
    batch.cpp - Class source file for batch class.
    Beginning Date : June 25, 2006
    Completion Date : June 25, 2006
    Latest Modification : June 25, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// project include files
#include "batch.h"
#include "common.h"

/**
    Parses an entire list of .wav files and sends them to batchAdd for mfcc
extraction and entry into table 1
*/

void Batch :: batchUpdate (char **filelist, long numFiles, long timeFrame)
{
    for (long i = 0; i < numFiles; i ++)
        batchAdd (filelist [i], timeFrame);
}

/**
    Adds one .wav file given by infile into the table 1 containing mfcc data records

    timeFrame : Duration of audio signal (in ms) per mfcc vector
*/
void Batch :: batchAdd (char *infile, long timeFrame)
{
    FILE *inFp, *outFp;
    real *dataBlock;
    long frameID;
    MFCC m1;
    Wave w1;
    short * waveData;
    double ** mfccData;

    dataBlock = (real*) calloc (_CEPSTRALCOEFS, sizeof (real));

    w1.waveRead(infile);
    waveData = (short *) calloc (w1.getNumChannels() * w1.getNumSamplesPerChannel(), sizeof (short));
    w1.waveLoad(0, w1.getNumSamplesPerChannel(), waveData);
    w1.waveDownmix(waveData, waveData);

    m1.MFCCcompute (waveData, w1.getSampleRate(), w1.getNumSamplesPerChannel(), mfccData, _BATCHTEMPFILE, timeFrame);

    // open input mfcc file
    if (!(inFp = fopen (_BATCHTEMPFILE, "rb")))
    {
        printf ("Can't open file %s\n", _BATCHTEMPFILE);
        exit (0);
    }

    // open output mfcc file
    if (!(outFp = fopen (_TABLE1NAME, "ab")))
    {
        printf ("Can't open file %s\n", _TABLE1NAME);
        exit (0);
    }

    frameID = 0;
    while (!feof (inFp))
    {
        if (fread (dataBlock, sizeof (real), _CEPSTRALCOEFS, inFp) != _CEPSTRALCOEFS)
            break;

        fwrite (dataBlock, sizeof (real), _CEPSTRALCOEFS, outFp);
        fwrite (infile, sizeof (char), _TAB1SONGIDSIZE, outFp);
        fwrite (&frameID, sizeof (long), 1, outFp);
        frameID++;
    }

    free (dataBlock);
    free (waveData);
    free (infile);
    fclose (inFp);
    fclose (outFp);
}
