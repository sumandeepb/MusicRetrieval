/*
** Copyright (C) 1998-2004 George Tzanetakis <gtzan@cs.uvic.ca>
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
    fft.h - Class header file for computing Fast Fourier Transform
    Beginning Date : June 6, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 9, 2006

    Code modified by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Fft
    \brief Fast Fourier Transform.

   Class for calculating the fft (Fast Fourier Transform) of the input signal vector.
*/

#if !defined (MARSYAS_FFT_H)
#define MARSYAS_FFT_H

// standard include files
#include <stdio.h>
#include <math.h>

// project include files
#include "common.h"

class Fft
{
private:
  void bitreverse(real x[], int N);
public:
  void rfft( real x[], int  N, int forward);
  void cfft(real x[], int N, int forward);
};

#endif
	
