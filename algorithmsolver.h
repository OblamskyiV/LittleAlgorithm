#ifndef ALGORITHMSOLVER_H
#define ALGORITHMSOLVER_H

#include <QHash>
#include <QVector>
#include <iostream>
#include <stdio.h>
#include "limits"

struct Node {
    QVector<QPair<QPair<int, int>, int> > path;
    double** costMatrix;
    double mark;
    Node *left, *right, *parent;
};

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


    //double findMinimalRowElement(int row);
    //double findMinimalColElement(int col);
    double substractMinFromAllRows(double **matrix, int matrixSize, double currentMark);
    double substractMinFromAllCols(double **matrix, int matrixSize, double currentMark);

    double findMaxMatrixElement(double** matrix, int size);
    double findMinimalRowElement(double** matrix, int size, int row, QPair<int, int>);
    double findMinimalColElement(double** matrix, int size, int col, QPair<int, int>);
    QVector<QPair<QPair<int, int>, int> > findChainWithMaxCoeff(double** matrix, int size);

    void removeRowAndCol(double **matrix, int size, int row, int col);

    int findRank(double **matrix, int size);

    double** copyMatrix(double** matrix, int size);

    double** checkMatrixRank(double** matrix, int size, int **x, int **y);
public:

    void solve();

    Node* divaricate(Node* node);
};

#endif // ALGORITHMSOLVER_H
