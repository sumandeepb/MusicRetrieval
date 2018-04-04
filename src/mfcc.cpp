/*
** Copyright (C) 1998-2005 George Tzanetakis <gtzan@cs.uvic.ca>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/*
    Copyright (C) 2006-2018 Sumandeep Banerjee
*/

/*
    mfcc.cpp - Class source file for computing MFCC coefficients
    Beginning Date : June 6, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 21, 2006

    Code modified by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard header files
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// project header files
#include "mfcc.h"

/**
    Computes mfcc coefficients. Calls the other functions namely MFCCupdate, MFCCdownmix, and MFCCprocess. Can be used as a standalone mfcc module (along with the dependencies)

    inputSignal (input)     : Time domain input audio signal
    sampleRate (input)      : Sampling rate of the input signal
    numInputSamples (input) : size of the input signal
    mfccVector (output)     : pointer to mfcc feature vectors
    timeFrame (input)       : Duration (in miliseconds) of audio signal that will produce one mfcc vector, default value is 23ms
    mfccfilename (output)   : File path/name of the mfcc coefficient file. Will be written with mfcc vectors of dimention "_CEPSTRALCOEFS" representing each "timeFrame" duration of audio signal
                              if given as Null, then no mfcc output file will be generated

    return value : size of mfccVector i.e. numFeatureVectors. Each feature vector is of dimention cepstralCoefs_
*/
long MFCC :: MFCCcompute (short * inputSignal, long sampleRate, long numInputSamples, double **mfccVector, char * mfccfilename, long timeFrame) {
    long sampleIndex, i, j,  defaultTimeFrame, downSampleFactor, numFeatureVectors, n;
    FILE *fp, *mfccfp;
    real *tempMFCCdata;
    short * data;
    real * MFCCdata;
    Window win1;

    // open mfcc temp file for writing
	if(!(fp = fopen (_MFCCTEMPFILE, "wb")))					// if can't open then exit
	{
		printf ("Can't open file %s\n", _MFCCTEMPFILE);		// print error message
		exit (0);
	}

    samplingRate_ = sampleRate;
    defaultTimeFrame = (WINDOWSIZE * 1000L) / sampleRate;
    downSampleFactor = (long) ceil ((float) timeFrame / (float) defaultTimeFrame);
    numFeatureVectors = numInputSamples / downSampleFactor;

    // allocate memory for wave data
    data = (short *) calloc (WINDOWSIZE, sizeof (short));
    // allocate MFCC data
    mfccVector = (double **) calloc (numFeatureVectors, sizeof (double *));
    for (i = 0;  i < numFeatureVectors; i ++)
        mfccVector [i] = (double *) calloc (cepstralCoefs_, sizeof (double));

    // call MFCCupdate to initialize parameters for MFCC computation
    MFCCupdate ();
    // allocate memory for MFCC data array
    MFCCdata = (real *) calloc (cepstralCoefs_, sizeof (real));
    // temporary MFCC data array
    tempMFCCdata = (real *) calloc (cepstralCoefs_, sizeof (real));
    // intialize Hamming window coefficients
    win1.windowHammingUpdateTable (WINDOWSIZE);
    // compute MFCCs of overlaping blocks
    for (sampleIndex = 0; sampleIndex < numInputSamples; sampleIndex += (WINDOWSIZE - WINDOWOVERLAP))
    {
        if (sampleIndex + WINDOWSIZE < numInputSamples)
        {
            // load wave data into data array
            for (i = 0; i < WINDOWSIZE; i ++)
                data [i] = inputSignal [sampleIndex + i];
            // perform hamming window
            win1.windowHamming (data, WINDOWSIZE, 0, data);
            // compute MFCC coefficients for the data block
            MFCCprocess (data, MFCCdata);
            // write MFCC coefficients into temporary file
            fwrite (MFCCdata, sizeof (real), cepstralCoefs_, fp);
        }
    }

    fclose (fp);

    // open mfcc temp file for reading
	if(!(fp = fopen (_MFCCTEMPFILE, "rb")))					// if can't open then exit
	{
		printf ("Can't open file %s\n", _MFCCTEMPFILE);		// print error message
		exit (0);
	}

    if (mfccfilename != NULL)
    {
        // open .mfcc file for writing
	    if(!(mfccfp = fopen (mfccfilename, "wb")))					// if can't open then exit
        {
            printf ("Can't open file %s\n", mfccfilename);		// print error message
            exit (0);
	    }
    }

    n = 0;

    // downsample MFCC coefficients to produce one vector for each timeFrame duration
    while (!feof (fp))
    {
        for (j = 0; j < cepstralCoefs_; j ++)
            tempMFCCdata [j] = 0.0;

        for (i = 0; i < downSampleFactor; i ++)
        {
            if (fread (MFCCdata, sizeof (real), cepstralCoefs_, fp) != cepstralCoefs_)
                break;
            for (j = 0; j < cepstralCoefs_; j ++)
                tempMFCCdata [j] += MFCCdata [j];
        }

        for (j = 0; j < cepstralCoefs_; j ++)
            mfccVector [n][j]= tempMFCCdata [j];

        n ++;

        // write final MFCC data into file
        if (mfccfilename != NULL)
            fwrite (tempMFCCdata, sizeof (real), cepstralCoefs_, mfccfp);
    }

    fclose (fp);

    if (mfccfilename != NULL)
        fclose (mfccfp);

    free (data);
    free (mfccVector);
    free (MFCCdata);
    free (tempMFCCdata);
    free (freqs_);
    free (lower_);
    free (center_);
    free (upper_);
    free (triangle_heights_);
    free (fftFreqs_);
    free (mfccFilterWeights_);
    free (mfccDCT_);
    free (fmagnitude_);
    free (earMagnitude_);
    free (inSignalBuffer);

    return (numFeatureVectors);
} // end of MFCCcompute

/**
    Intializes parameters and filter coefficients for mfcc computation. Also allocates memory for various storage elements
*/
void MFCC :: MFCCupdate()
{
    
    natural i,j;
    fftSize_ = WINDOWSIZE;
    inSize = WINDOWSIZE / 2;
    cepstralCoefs_ = _CEPSTRALCOEFS;

    // Initialize frequency boundaries for filters
    freqs_ = (real *) calloc (42, sizeof (real));
    lowestFrequency_ = 133.3333f;
    linearFilters_ = 13;
    linearSpacing_ = 66.66666f;
    logFilters_ = 27;
    logSpacing_ = 1.0711703f;
    totalFilters_ = linearFilters_ + logFilters_;
    lower_ = (real *) calloc (totalFilters_, sizeof (real));
    center_ = (real *) calloc (totalFilters_, sizeof (real));
    upper_ = (real *) calloc (totalFilters_, sizeof (real));
    triangle_heights_ = (real *) calloc (totalFilters_, sizeof (real));

    // Linear filter boundaries
    for (i=0; i< linearFilters_; i++)
	   freqs_[i] = lowestFrequency_ + i * linearSpacing_;

    // Logarithmic filter boundaries
    real first_log = freqs_[linearFilters_-1];
    for (i=1; i<=logFilters_+2; i++)
       freqs_[linearFilters_-1+i] = first_log * pow(logSpacing_, (real)i);

    // Triangles information
    for (i=0; i<totalFilters_; i++)
	   lower_[i] = freqs_[i];
    for (i=1; i<= totalFilters_; i++)
	   center_[i-1] = freqs_[i];
    for (i=2; i<= totalFilters_+1; i++)
	   upper_[i-2] = freqs_[i];
    for (i=0; i<totalFilters_; i++)
	   triangle_heights_[i] = (real)(2.0 / (upper_[i] - lower_[i]));
      
    // allocate memory for fft signal
    fftFreqs_ = (real *) calloc (fftSize_, sizeof (real));
    cepstralCoefs_ = 13;

    for (i=0; i< fftSize_; i++)
    {
	   fftFreqs_[i] = (real)i / (real)fftSize_ * (real)samplingRate_;
    }

    // allocate memory for mfcc filter basis function
    mfccFilterWeights_ = (real **) calloc (totalFilters_, sizeof (real *));
    for (i = 0; i < totalFilters_; i++)
        mfccFilterWeights_[i] = (real *) calloc (fftSize_, sizeof (real));

    // allocate memory for DCT basis function
    mfccDCT_ = (real **) calloc (cepstralCoefs_, sizeof (real *));
    for (i = 0; i < cepstralCoefs_; i++)
        mfccDCT_[i] = (real *) calloc (totalFilters_, sizeof (real));

    natural chan;
      
    // Initialize mfcc filter coefficients
    for (chan = 0; chan < totalFilters_; chan++)
	{
        for (i=0; i< fftSize_; i++)
	    {
	       if ((fftFreqs_[i] > lower_[chan])&& (fftFreqs_[i] <= center_[chan]))
	       {
		      mfccFilterWeights_[chan][i] = triangle_heights_[chan] * ((fftFreqs_[i] - lower_[chan])/(center_[chan] - lower_[chan]));
           }
	       if ((fftFreqs_[i] > center_[chan]) && (fftFreqs_[i] <= upper_[chan]))
	       {
		      mfccFilterWeights_[chan][i] = triangle_heights_[chan] * ((upper_[chan] - fftFreqs_[i])/(upper_[chan] - center_[chan]));
	       }
	   }
    }

    // Initialize DCT coefficients
    real scale_fac = (real)(1.0/ sqrt((real)(totalFilters_/2)));
    for (j = 0; j<cepstralCoefs_; j++)
	{
        for (i=0; i< totalFilters_; i++)
        {
	       mfccDCT_[j][i] = scale_fac * cos(j * (2*i +1) * PI/2/totalFilters_);
	       if (i == 0)
	           mfccDCT_[j][i] *= (real)(sqrt(2.0)/2.0);
        }
    }
  
    pfftSize_ = fftSize_;
    psamplingRate_ = samplingRate_;
  
    // allocate memory for fft signal and mfcc coefficients
    fmagnitude_ = (real *) calloc (inSize * 2, sizeof (real));
    earMagnitude_ = (real *) calloc (totalFilters_, sizeof (real));
    inSignalBuffer = (real *) calloc (inSize * 2, sizeof (real));
}

/**
    Extracts mfcc parameters from a given input signal and puts into the output signal. MFCCupdate must be called before for intialisation of parameters and allocation of memory
*/
void MFCC :: MFCCprocess(short * inSignal, real * outSignal)
{
    natural i,k;
    Fft f1;
    // copy input signal and perform fft
    for (i = 0; i < inSize * 2; i ++)
    {
        inSignalBuffer [i] = (real) inSignal [i];
    }
    f1.rfft (inSignalBuffer, inSize, 1);

    // take log of amplitude
    for (i = 0; i < inSize; i ++)
    {
        inSignalBuffer [i] = (sqrt (inSignalBuffer [2 * i] * inSignalBuffer [2 * i] + inSignalBuffer [2 * i + 1] * inSignalBuffer [2 * i + 1]));
    }

    // mirror the spectrum
    for (long o=0; o < inSize; o++)
    {
        fmagnitude_[o] = inSignalBuffer[o];
    }
    for (long o=0; o< inSize; o++)
    {
        fmagnitude_[o + inSize] = fmagnitude_[inSize - o];
    }
    real sum = 0.0;

    // Calculate the filterbank responce
    for (i=0; i<totalFilters_; i++)
    { 
        sum = 0.0;
        for (k=0; k<fftSize_; k++)
	    {
	       sum += (mfccFilterWeights_[i][k] * fmagnitude_[k]);
        }
        if (sum != 0.0)
	       earMagnitude_[i] = log10(sum);
        else
	       earMagnitude_[i] = 0.0;
    }

    // Take the DCT
    for (long o=0; o < cepstralCoefs_; o++)
    {
        sum =0.0;
        for (k=0; k < totalFilters_; k++)
	    {
	       sum += (mfccDCT_[o][k] * earMagnitude_[k]);
	    }
        outSignal[o] = sum;
    }
}
