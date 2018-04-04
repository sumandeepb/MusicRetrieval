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
    cluster.h - Class header file for cluster class for Music Retrieval Module.
    Beginning Date : June 20, 2006
    Completion Date : June 20, 2006
    Latest Modification : June 20, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Cluster
    \brief Clustering for music retrieval.

    Performs K-Means clustering on the set of data points, used to index the
data into clusters, thereby reducing the search space to only matching clusters
instead of the entire database
*/
#if !defined (_CLUSTER_H)
#define _CLUSTER_H

// project include files
#include "kmeans.h"

class Cluster{
    public:
        void cluster ();
};

#endif
