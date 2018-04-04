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
    window.h - Class header file for window filtering. Supports Hamming, ... windows
    Beginning Date : June 1, 2006
    Completion Date : June 9, 2006
    Latest Modification : June 9, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Window
    \brief Windowing for anti-aliasing

    Class to perform windowing on an one dimentional digital signal. It's a technique
to reduce aliasing effects. The Window class contains implementations for various
filters such as Hamming ... etc
*/

#if !defined (_WINDOW_H)
#define _WINDOW_H

// project include files
#include "common.h"

class Window {
    private:
        double * hammingTable;
    protected:
    public:
        // Member function to perform Hamming Window filtering on given input signal
        void windowHamming (short int * insignal, long N, long startIndex, short int * outsignal);
        void Window :: windowHammingUpdateTable (long N);
};

#endif
