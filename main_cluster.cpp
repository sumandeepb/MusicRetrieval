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
    main_cluster.cpp - main routine for clustering module.
    Beginning Date : June 20, 2006
    Completion Date : June 21, 2006
    Latest Modification : June 21, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \brief Command line main function for clustering the data points in table 1
*/
// project include files
#include "cluster.h"

// main_cluster function
int main_cluster (int argc, char * argv []) {
    Cluster c1;
    c1.cluster ();
    
    return 0;
} // end of main_cluster function
