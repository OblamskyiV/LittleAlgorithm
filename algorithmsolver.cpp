#include "algorithmsolver.h"

AlgorithmSolver::AlgorithmSolver(double **matrix, const int size):
    size(size)
{   
    costMatrix = matrix;
    contour = QVector<QPair<int, int> >();
}

void AlgorithmSolver::solve()
{
    do {
        substractMinFromAllRows();
        substractMinFromAllCols();

        //TODO: other steps

        exit(0);

    } while (findRank() > 2);

    //TODO: last step
}

void AlgorithmSolver::printCostMatrix()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%9.2f | ", costMatrix[i][j]);
        }
        printf("\n");
    }
}

void AlgorithmSolver::printContour()
{
    for (int i = 0; i < contour.size(); i++) {
        std::cout << "(" << contour.at(i).first << ", " << contour.at(i).second << "); ";
    }
    std::cout << std::endl;
}

double AlgorithmSolver::findMinimalRowElement(int row)
{
    double min = std::numeric_limits<double>::infinity();
    for (int j = 0; j < size; j++) {
        if (costMatrix[row][j] >= 0 && costMatrix[row][j] < min)
            min = costMatrix[row][j];
    }
    return min;
}

double AlgorithmSolver::findMinimalColElement(int col)
{
    double min = std::numeric_limits<double>::infinity();
    for (int i = 0; i < size; i++) {
        if (costMatrix[i][col] >= 0 && costMatrix[i][col] < min)
            min = costMatrix[i][col];
    }
    return min;
}

void AlgorithmSolver::substractMinFromAllRows()
{
    for (int i = 0; i < size; i++)
    {
        double min = findMinimalRowElement(i);

        if (min >= 0)
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

        if (min >= 0)
            for (int i = 0; i < size; i++)
            {
                costMatrix[i][j] -= min;
            }
    }
}

void AlgorithmSolver::removeRowAndCol(int row, int col)
{
    for (int i = 0; i < size; i++)
    {
        costMatrix[i][col] = -1;
    }

    for (int j = 0; j < size; j++)
    {
        costMatrix[row][j] = -1;
    }

    costMatrix[row][col] = std::numeric_limits<double>::infinity();
}

int AlgorithmSolver::findRank()
{
    int rank = size;

    for (int i = 0; i < size; i++)
        if (costMatrix[0][i] == -1)
            rank--;

    return rank;
}
