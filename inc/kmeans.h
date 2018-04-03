/*
    kmeans.h - Class header file for K means clustering.
    Beginning Date : June 16, 2006
    Completion Date : June 20, 2006
    Latest Modification : June 20, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Kmeans
    \brief K-Means Clustering

    K-Means clustering is an indexing method for a collection of data points. It's based on
unsupervised learing neural network. Indexes a collection of data points into K categories
*/

#if !defined (_KMEANS_H)
#define _KMEANS_H

// standard include files
#include "math.h"

/// Precision of clustering. L2NORM change in mean value
#define _PRECISION 1E-6

class Kmeans {
    private:
    protected:
        long N, D, K;
    public:
        void KmeansCalculate (double **X, double **mean, bool **responsibility, long n, long d, long k = 0);
};

#endif
