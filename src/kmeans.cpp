/*
    kmeans.cpp - Class source file for K means clustering.
    Beginning Date : June 16, 2006
    Completion Date : June 20, 2006
    Latest Modification : June 21, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard include files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// project header files
#include "kmeans.h"

/**
    function to compute K-means (K cluster centres) from the given set of data points

    X (input) : Set of n data points of dimention d. n X d

    mean (output) : Cluster centres. k X d

    responsibility (output) : responsibility of each data point n X k i.e. which data points belong which cluster
*/
void Kmeans :: KmeansCalculate (double **X, double **mean, bool **responsibility, long n, long d, long k) {
    long winnerID, R, iterations;
    double distance, minDistance, *newMean, *oldMean, error;

    // assume default vaule of K (number of clusters) as sqrt(N) if not supplied by user
    N = n;
    D = d;
    K = k;
    if (K == 0)
        K = (long) sqrt ((double)N);

    // random initialization of the K means from the data set
    srand (time (NULL));
    for (k = 0; k < K; k++)
    {
        n = (long)(((double) rand () / (double) RAND_MAX) * (double)N);
        for (d = 0; d < D; d++)
            mean [k][d] = X [n][d];
    }

    iterations = 0;
    while (1)
    {
        // assignment step, select winners for each data point
        for (n = 0; n < N; n ++)
        {
            // minDistance = 0.0;
            for (k = 0; k < K; k ++)
            {
                distance = 0.0;
                for (d = 0; d < D; d ++)
                {
                    distance += (X [n][d] - mean [k][d]) * (X [n][d] - mean [k][d]);
                }
                // Euclidean distance between nth data point and kth mean
                distance = sqrt (distance);
                if (k == 0 || distance < minDistance)
                {
                    minDistance = distance;
                    // index of the winner mean
                    winnerID = k;
                }
                responsibility [n][k] = false;
            }
            // responsibility matrix
            responsibility [n][winnerID] = true;
        }

        // update step, update kth mean to the mean of its responsibilities
        newMean = (double *) calloc (D, sizeof (double));
        oldMean = (double *) calloc (D, sizeof (double));
        error = 0.0;
        for (k = 0; k < K; k ++)
        {
            R = 0;
            for (d = 0; d < D; d ++)
            {
                newMean [d] = 0.0;
                oldMean [d] = mean [k][d];
            }

            for (n = 0; n < N; n ++)
            {
                if (responsibility [n][k] == true)
                {
                    for (d = 0; d < D; d ++)
                    {
                        // compute new mean of the kth cluster
                        newMean [d] +=  X [n][d];
                    }
                    R ++;
                }
            }

            if (R > 0)
            {
                for (d = 0; d < D; d ++)
                {
                    // update mean with the new mean
                    mean [k][d] = newMean [d] / (double)R;
                }
            }

            // compute sum of changes in all the means
            for (d = 0; d < D; d ++)
            {
                error += (mean [k][d] - oldMean [d]) * (mean [k][d] - oldMean [d]);
            }
            error = sqrt (error); // L2Norm is used for error measure
        }

        iterations ++;
        // break loop when error i.e. sum of changes in means goes below required precision
        // maximum iterations 100
        if (iterations >= 100 || error < _PRECISION)
            break;
    }
} // end of KmeansCalculate
