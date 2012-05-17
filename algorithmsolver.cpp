#include "algorithmsolver.h"

AlgorithmSolver::AlgorithmSolver(double **matrix, const int size):
    size(size)
{   
    costMatrix = matrix;
}

void AlgorithmSolver::solve()
{
    // Step 1
    substractMinFromAllRows();
    substractMinFromAllCols();

    //TODO: other steps
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

double AlgorithmSolver::findMinimalColElement(int col)
{
    double min = std::numeric_limits<double>::infinity();
    for (int i = 0; i < size; i++) {
        if (costMatrix[i][col] < min)
            min = costMatrix[i][col];
    }
    return min;
}

void AlgorithmSolver::substractMinFromAllRows()
{
    for (int i = 0; i < size; i++)
    {
        double min = findMinimalRowElement(i);

        for (int j = 0; j < size; j++)
        {
            costMatrix[i][j] -= min;
        }
    }
}

void AlgorithmSolver::substractMinFromAllCols()
{
    for (int j = 0; j < size; j++)
    {
        double min = findMinimalColElement(j);

        for (int i = 0; i < size; i++)
        {
            costMatrix[i][j] -= min;
        }
    }
}
