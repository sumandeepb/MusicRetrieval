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
