#include "algorithmsolver.h"

AlgorithmSolver::AlgorithmSolver(double **matrix, const int size):
    size(size)
{   
    costMatrix = matrix;
}

void AlgorithmSolver::print()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%9.2f | ", costMatrix[i][j]);
        }
        printf("\n");
    }
}

double AlgorithmSolver::findMinimalRowElement(int row)
{
    double min = std::numeric_limits<double>::infinity();
    for (int j = 0; j < size; j++) {
        if (costMatrix[row][j] < min)
            min = costMatrix[row][j];
    }
    return min;
}
