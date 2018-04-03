/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This program demonstrates the use of the quick sort algorithm.  For
 * more information about this and other sorting algorithms, see
 * http://linux.wku.edu/~lamonml/kb.html
 *
 */

/*
    quicksort.h - Header file for quick sort algoritm
    Beginning Date : June 22, 2006
    Completion Date : June 22, 2006
    Latest Modification : June 22, 2006

    Code modified by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class QuickSort
    \brief Quick Sort

Applies Quick Sort algorithm to sort a given list of numbers in ascending order
*/
#if !defined (_QSORT_H)

#define _QSORT_H

class QuickSort {
    public:
        void quickSort(long numbers[], long array_size);
        void q_sort(long numbers[], long left, long right);
};
#endif
