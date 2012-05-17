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
    double bottomBoundary;


    double findMinimalRowElement(int row);
    double findMinimalColElement(int col);
    void substractMinFromAllRows();
    void substractMinFromAllCols();

    double findMaxMatrixElement(double** matrix, int size);
    double findMinimalRowElement(double** matrix, int size, int row, QPair<int, int>);
    double findMinimalColElement(double** matrix, int size, int col, QPair<int, int>);
    QVector<QPair<int, int> > findChainWithMaxCoef();

    void removeRowAndCol(int row, int col);

    int findRank();
public:

    void solve();
};

#endif // ALGORITHMSOLVER_H
