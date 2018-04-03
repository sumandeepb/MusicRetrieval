/*
    cluster.cpp - Class source file for cluster class.
    Beginning Date : June 20, 2006
    Completion Date : June 20, 2006
    Latest Modification : June 20, 2006

    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard include files
#include <stdio.h>
#include <stdlib.h>

// project include files
#include "common.h"
#include "cluster.h"
#include "kmeans.h"

/**
    Reads in the data points from table1, allocates the required storage elements.
Calls the Kmeans module, to perform K-Mean clustering of the data. Writes the means
and responsibilitx matrix to table 2 and table 3 respectively
*/
void Cluster :: cluster ()
{
    double **X, **mean;
    bool **responsibility;
    FILE *tab1Fp, *tab2Fp, *tab3Fp;
    long n, d, k, N, D, K, recordSize;
    Kmeans k1;

    if (!(tab1Fp = fopen (_TABLE1NAME, "rb")))
    {
        printf ("Can't open file %s\n", _TABLE1NAME);
        exit (0);
    }

    if (!(tab2Fp = fopen (_TABLE2NAME, "wb")))
    {
        printf ("Can't open file %s\n", _TABLE2NAME);
        exit (0);
    }

    if (!(tab3Fp = fopen (_TABLE3NAME, "wb")))
    {
        printf ("Can't open file %s\n", _TABLE3NAME);
        exit (0);
    }

    // determine parameters
    fseek (tab1Fp, 0, SEEK_END);
    recordSize = (long)_TAB1RECORDSIZE;
    N = (ftell (tab1Fp)) / recordSize;

    K = (long) sqrt ((double)N);

    D = _CEPSTRALCOEFS;

    // allocate space for N data points with dimention D
    X = (double **) calloc (N, sizeof (double *));
    for (n = 0; n < N; n ++)
        X [n] = (double *) calloc (D, sizeof (double));

    // allocate space for K means with dimention D
    mean = (double **) calloc (K, sizeof (double *));
    for (k = 0; k < K; k ++)
        mean [k] = (double *) calloc (D, sizeof (double));

    // allocate space for the responsibility matrix N X K
    responsibility = (bool **) calloc (N, sizeof (bool *));
    for (n = 0; n < N; n ++)
        responsibility [n] = (bool *) calloc (K, sizeof (bool));

    // read data points in X
    for (n = 0; n < N; n++)
    {
        fseek (tab1Fp, n * recordSize, SEEK_SET);
        fread (X [n], sizeof (real), D, tab1Fp);
    }

    // perform K means clustering
    k1.KmeansCalculate(X, mean, responsibility, N, D, K);

    // write the means in table 2
    for (k = 0; k < K; k ++)
    {
        fwrite (mean [k], sizeof (real), D, tab2Fp);
    }

    // write the responsibility matrix in table 3
    for (k = 0; k < K; k ++)
    {
        for (n = 0; n < N; n ++)
        {
            if (responsibility [n][k] == true)
            {
                fwrite (&k, sizeof (long), 1, tab3Fp);
                fwrite (&n, sizeof (long), 1, tab3Fp);
            }
        }
    }

    fclose (tab1Fp);
    fclose (tab2Fp);
    fclose (tab3Fp);
} // end of cluster
