#ifndef ALGORITHMSOLVER_H
#define ALGORITHMSOLVER_H

#include <QHash>
#include <QVector>
#include <iostream>
#include <stdio.h>
#include "limits"

class AlgorithmSolver
{
public:
    AlgorithmSolver(double **matrix, const int size);

    void printCostMatrix();
    void printContour();

private:
    double **costMatrix;
    int size;
    QVector<QPair<int, int> > contour;

    double findMinimalRowElement(int row);
    double findMinimalColElement(int col);

    void substractMinFromAllRows();
    void substractMinFromAllCols();

    void removeRowAndCol(int row, int col);
public:

    void solve();
};

#endif // ALGORITHMSOLVER_H
