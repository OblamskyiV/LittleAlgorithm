#include "algorithmsolver.h"

AlgorithmSolver::AlgorithmSolver(double **matrix, const int size):
    size(size)
{   
    costMatrix = matrix;
    contour = QVector<QPair<int, int> >();
    bottomBoundary = 0;
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

double AlgorithmSolver::findMinimalRowElement(double** matrix, int matrixSize,int row,
                                              QPair<int, int> excludedChain)
{
    double min = std::numeric_limits<double>::infinity();
    for (int j = 0; j < matrixSize; j++) {
        if (matrix[row][j] >= 0
                && matrix[row][j] < min
                && j != excludedChain.second)
            min = matrix[row][j];
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

double AlgorithmSolver::findMinimalColElement(double** matrix, int matrixSize, int col,
                                              QPair<int, int> excludedChain)
{
    double min = std::numeric_limits<double>::infinity();
    for (int i = 0; i < matrixSize; i++) {
        if (matrix[i][col] >= 0
                && matrix[i][col] < min
                && i != excludedChain.first)
            min = matrix[i][col];
    }
    return min;
}

void AlgorithmSolver::substractMinFromAllRows()
{
    for (int i = 0; i < size; i++)
    {
        double min = findMinimalRowElement(i);
        bottomBoundary += min;

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
        bottomBoundary += min;

        if (min >= 0)
            for (int i = 0; i < size; i++)
            {
                costMatrix[i][j] -= min;
            }
    }
}

double AlgorithmSolver::findMaxMatrixElement(double** matrix, int size)
{
    double maxValue = -1;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix[i][j] > maxValue)
                maxValue = matrix[i][j];
    return maxValue;

}

QVector<QPair<int, int> > AlgorithmSolver::findChainWithMaxCoef()
{
    // create temporary matrix
    double** tmpCostMatrix = new double*[size];
    for (unsigned int i = 0; i < size; ++i)
    {
        tmpCostMatrix[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (costMatrix[i][j] == 0) {
                tmpCostMatrix[i][j] = costMatrix[i][j];

                tmpCostMatrix[i][j] = findMinimalRowElement(costMatrix, size, i,
                                                            QPair<int, int>(i, j))
                        + findMinimalColElement(costMatrix, size, j,
                                                QPair<int, int>(i, j));
            }
            else
                tmpCostMatrix[i][j] = -1;

    QVector<QPair<int, int> > vector;
    double maxCoeff = findMaxMatrixElement(tmpCostMatrix, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (tmpCostMatrix[i][j] == maxCoeff)
                vector.append(QPair<int, int>(i, j));

    //FIXME: memory leak

    return vector;
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
