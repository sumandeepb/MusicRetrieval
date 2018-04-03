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
    mfcc.h - Class header file for computing MFCC coefficients
    Beginning Date : June 6, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 21, 2006

    Code modified by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class MFCC
    \brief Mel-Frequency Cepstral Coefficients

    Mel-Frequency cepstral coefficients (mfcc) are features frequently used in
Speech Recognition. The MFCC class encapsulates the various modules needed to
compute the mfcc coefficients from a given wave (.wav) format file.
*/

#if !defined (_MARSYAS_MFCC_H)
#define _MARSYAS_MFCC_H

// project header files
#include "common.h"
#include "wave.h"
#include "window.h"
#include "fft.h"

/// This temporary file is generated by the MFCC class to store intermediate data
#define _MFCCTEMPFILE "mfcc.temp"

class MFCC
{
    private:
        real lowestFrequency_;
        natural linearFilters_;
        real linearSpacing_;
        natural logFilters_;
        real logSpacing_;
        natural totalFilters_;

        natural fftSize_, pfftSize_;
        natural samplingRate_, psamplingRate_;
        natural cepstralCoefs_;

        natural inSize;

        real * freqs_;
        real * lower_;
        real * center_;
        real * upper_;
        real * triangle_heights_;

        real * fftFreqs_;
        real ** mfccFilterWeights_;
        real ** mfccDCT_;
        real * earMagnitude_;
        real * fmagnitude_;
        real * inSignalBuffer;

        bool init_;

        void MFCCupdate();
        void MFCCprocess(short * inSignal, real * outSignal);
    protected:

    public:
        long MFCC :: MFCCcompute (short * inputSignal, long sampleRate, long numInputSamples, double **mfccVector, char * mfccfilename = 0, long timeFrame = 23);
};

#endif

	