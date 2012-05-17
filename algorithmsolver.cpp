#include "algorithmsolver.h"

AlgorithmSolver::AlgorithmSolver(double **matrix, const int size):
    size(size)
{   
    costMatrix = matrix;
    contour = QVector<QPair<int, int> >();
    bottomBoundary = std::numeric_limits<double>::infinity();
}

void AlgorithmSolver::solve()
{
    Node node;
    node.parent = NULL;
    node.path = QVector<QPair<QPair<int, int>, int> >();
    node.mark = 0;
    node.left = NULL;
    node.right = NULL;
    node.costMatrix = copyMatrix(costMatrix, size);

    node.mark = substractMinFromAllRows(node.costMatrix, size, node.mark);
    node.mark = substractMinFromAllCols(node.costMatrix, size, node.mark);
    QVector<QPair<QPair<int, int>, int> > chains = findChainWithMaxCoeff(node.costMatrix, size);
//    node.path.append(chains.at(0));

    Node* bottomNode = divaricate(&node);

    //TOOD: next actions
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

//double AlgorithmSolver::findMinimalRowElement(int row)
//{
//    double min = std::numeric_limits<double>::infinity();
//    for (int j = 0; j < size; j++) {
//        if (costMatrix[row][j] >= 0 && costMatrix[row][j] < min)
//            min = costMatrix[row][j];
//    }
//    return min;
//}

double AlgorithmSolver::findMinimalRowElement(double** matrix, int matrixSize, int row,
                                              QPair<int, int> excludedChain)
{

    //    for (int i = 0; i < size; i++) {
    //        printf("\n");
    //        for (int j = 0; j < size; j++)
    //            printf("%6.2f   ", matrix[i][j]);

    //    }

    double min = std::numeric_limits<double>::infinity();
    for (int j = 0; j < matrixSize; j++) {
        if (matrix[row][j] >= 0 && matrix[row][j] < min
                && !(j == excludedChain.second && excludedChain.first == row))
            min = matrix[row][j];
    }

    if (min == std::numeric_limits<double>::infinity())
        min = 0;
    return min;
}

//double AlgorithmSolver::findMinimalColElement(int col)
//{
//    double min = std::numeric_limits<double>::infinity();
//    for (int i = 0; i < size; i++) {
//        if (costMatrix[i][col] >= 0 && costMatrix[i][col] < min)
//            min = costMatrix[i][col];
//    }
//    return min;
//}

double AlgorithmSolver::findMinimalColElement(double** matrix, int matrixSize, int col,
                                              QPair<int, int> excludedChain)
{
    double min = std::numeric_limits<double>::infinity();
    for (int i = 0; i < matrixSize; i++) {
        if (matrix[i][col] >= 0
                && matrix[i][col] < min
                && !(i == excludedChain.first && col == excludedChain.second))
            min = matrix[i][col];
    }

    if (min == std::numeric_limits<double>::infinity())
        min = 0;
    return min;
}

double AlgorithmSolver::substractMinFromAllRows(double** matrix, int matrixSize, double currentMark)
{
    for (int i = 0; i < matrixSize; i++)
    {
        double min = findMinimalRowElement(matrix, matrixSize, i, QPair<int, int>(-1, -1));
        currentMark += min;

        if (min > 0 && min < std::numeric_limits<double>::infinity())
            for (int j = 0; j < matrixSize; j++)
            {
                matrix[i][j] -= min;
            }
    }
    return currentMark;
}

double AlgorithmSolver::substractMinFromAllCols(double** matrix, int matrixSize, double currentMark)
{
    for (int j = 0; j < matrixSize; j++)
    {
        double min = findMinimalColElement(matrix, matrixSize, j, QPair<int, int>(-1, -1));
        currentMark += min;

        if (min > 0 && min < std::numeric_limits<double>::infinity())
            for (int i = 0; i < matrixSize; i++)
            {
                matrix[i][j] -= min;
            }
    }
    return currentMark;
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

QVector<QPair<QPair<int, int>, int> > AlgorithmSolver::findChainWithMaxCoeff(double** matrix, int size)
{
    // create temporary matrix
    double** tmpCostMatrix = new double*[size];
    for (int i = 0; i < size; ++i)
    {
        tmpCostMatrix[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix[i][j] == 0) {

                tmpCostMatrix[i][j] = findMinimalRowElement(matrix, size, i,
                                                            QPair<int, int>(i, j))
                        + findMinimalColElement(matrix, size, j,
                                                QPair<int, int>(i, j));
            }
            else
                tmpCostMatrix[i][j] = -1;

    QVector<QPair<QPair<int, int>, int> > vector = QVector<QPair<QPair<int, int>, int> >();
    double maxCoeff = findMaxMatrixElement(tmpCostMatrix, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (tmpCostMatrix[i][j] == maxCoeff)
                vector.append(QPair<QPair<int, int>, int>(QPair<int, int>(i, j), maxCoeff));

    //FIXME: memory leak

    return vector;
}

void AlgorithmSolver::removeRowAndCol(double** matrix, int size, int row, int col)
{
    for (int i = 0; i < size; i++)
    {
        matrix[i][col] = std::numeric_limits<double>::infinity();
    }

    for (int j = 0; j < size; j++)
    {
        matrix[row][j] = std::numeric_limits<double>::infinity();
    }

    matrix[row][col] = -1;
}

int AlgorithmSolver::findRank(double **matrix, int size)
{
    int rank = size;

    for (int i = 0; i < size; i++)
        if (matrix[0][i] == -1)
            rank--;

    return rank;
}

double** AlgorithmSolver::copyMatrix(double** matrix, int size)
{
    double** copy = new double*[size];
    for (int i = 0; i < size; i++) {
        copy[i] = new double[size];
        for (int j = 0; j < size; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

double** AlgorithmSolver::checkMatrixRank(double** matrix, int size, int** x, int** y)
{
    int matrixSize = 0;

    double** twoOnTwoMatrix = new double*[2];
    for (unsigned int i = 0; i < 2; i++)
    {
        twoOnTwoMatrix[i] = new double[2];
    }

    for (int i = 0; i < size; i++) {

        int elementsInRow = 0;
        for(int j = 0; j < size; j++) {
            bool freeFlag = false;
            // check if there any -1 in current row or column
            for (int m = 0; m < size; m++)
                if (matrix[i][m] == -1) {
                    freeFlag = true;
                    break;
                }
                else if (matrix[m][j] == -1) {
                    freeFlag = true;
                    break;
                }

            if (freeFlag == false)
                elementsInRow++;

            if (elementsInRow > 2)
                return NULL;
            else if (elementsInRow > 0 && freeFlag == false) {
                x[matrixSize][elementsInRow - 1] = i;
                y[matrixSize][elementsInRow - 1] = j;
                twoOnTwoMatrix[matrixSize][elementsInRow - 1] = matrix[i][j];
            }
        }
        if (elementsInRow == 2)
            matrixSize++;
    }

    return twoOnTwoMatrix;
}

Node* AlgorithmSolver::divaricate(Node* node)
{
    int** rows = new int*[2];
    for (unsigned int i = 0; i < 2; i++)
    {
        rows[i] = new int[2];
    }
    int** cols = new int*[2];
    for (unsigned int i = 0; i < 2; i++)
    {
        cols[i] = new int[2];
    }
    double** m = checkMatrixRank(node->costMatrix, size, rows, cols);

    if (m != NULL) {


        node->mark = substractMinFromAllRows(m, 2, node->mark);
        node->mark = substractMinFromAllCols(m, 2, node->mark);

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (m[i][j] == 0)
                    node->path.append(QPair<QPair<int, int>, int>(QPair<int, int>
                                                                  (rows[i][j], cols[i][j]), 0));



        std::cout << "mark is " << node->mark << "\n";
        for (int i = 0; i < node->path.size(); i++)
            std::cout << node->path.at(i).first.first << "; "
                      << node->path.at(i).first.second << " -> ";
        std::cout << "\n";
        return node;
    }

    // left
    node->left = new Node;
    node->left->costMatrix = copyMatrix(node->costMatrix, size);
    node->left->mark = node->mark;
    node->left->parent = node;
    node->left->path = node->path;

    node->left->mark = substractMinFromAllRows(node->left->costMatrix, size, node->left->mark);
    node->left->mark = substractMinFromAllCols(node->left->costMatrix, size, node->left->mark);

    QVector<QPair<QPair<int, int>, int> > chains =
            findChainWithMaxCoeff(node->left->costMatrix, size);
    node->left->path.append(chains.at(0));

    node->left->costMatrix[chains.at(0).first.second][chains.at(0).first.first]
            = std::numeric_limits<double>::infinity();

    removeRowAndCol(node->left->costMatrix, size,
                    chains.at(0).first.first, chains.at(0).first.second);

    std::cout << node->left->mark << " | " << chains.at(0).first.first << " ; " << chains.at(0).first.second <<  " ||| ";


    // right
    node->right = new Node;
    node->right->costMatrix = copyMatrix(node->costMatrix, size);
    node->right->mark = node->mark;
    node->right->parent = node;
    node->right->path = node->path;

    node->right->mark = substractMinFromAllRows(node->right->costMatrix, size, node->right->mark);
    node->right->mark = substractMinFromAllCols(node->right->costMatrix, size, node->right->mark);

    chains = findChainWithMaxCoeff(node->right->costMatrix, size);
    //node->right->path.append(chains.at(0));

    node->right->costMatrix[chains.at(0).first.first][chains.at(0).first.second]
            = std::numeric_limits<double>::infinity();

    node->right->mark += chains.at(0).second;

    std::cout << node->right->mark << " | " << chains.at(0).first.first << " ; " << chains.at(0).first.second << "\n";

    if (node->left->mark <= node->right->mark)
        return divaricate(node->left);
    else
        return divaricate(node->right);
}
