#ifndef ALGORITHMSOLVER_H
#define ALGORITHMSOLVER_H

#include <QHash>
#include <iostream>
#include <stdio.h>
#include "limits"

class AlgorithmSolver
{
public:
    AlgorithmSolver(double **matrix, const int size);

    void print();

private:
    double **costMatrix;
    int size;

    double findMinimalRowElement(int row);
public:


};

#endif // ALGORITHMSOLVER_H
