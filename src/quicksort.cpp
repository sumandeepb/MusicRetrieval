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
    quicksort.cpp - Source file for quick sort algoritm
    Beginning Date : June 22, 2006
    Completion Date : June 22, 2006
    Latest Modification : June 22, 2006

    Code modified by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// project header files
#include "quicksort.h"

/**
    Recusive module of quick sort

    numbers : input array of numbers to sort

    left : leftmost index of the subarray to sort

    right : rightmost index of the subarray to sort
*/
void QuickSort :: q_sort(long numbers[], long left, long right)
{
  long pivot, l_hold, r_hold;

  l_hold = left;
  r_hold = right;
  pivot = numbers[left];
  while (left < right)
  {
    while ((numbers[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      numbers[left] = numbers[right];
      left++;
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      numbers[right] = numbers[left];
      right--;
    }
  }
  numbers[left] = pivot;
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot)
    q_sort(numbers, left, pivot-1);
  if (right > pivot)
    q_sort(numbers, pivot+1, right);
}

/**
    Quick Sort module

    numbers : input array of numbers to sort

    array_size : toal number of elements in the input array
*/
void QuickSort :: quickSort(long numbers[], long array_size)
{
  q_sort(numbers, 0, array_size - 1);
}
