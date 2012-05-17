#include <QtCore/QCoreApplication>
#include "algorithmsolver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    const unsigned int size = 6;

    double** costMatrix = new double*[size];
    for (unsigned int i = 0; i < size; i++)
    {
        costMatrix[i] = new double[size];
    }

    costMatrix[0][0] = std::numeric_limits<double>::infinity();
    costMatrix[0][1] = 6;
    costMatrix[0][2] = 4;
    costMatrix[0][3] = 8;
    costMatrix[0][4] = 7;
    costMatrix[0][5] = 14;

    costMatrix[1][0] = 6;
    costMatrix[1][1] = std::numeric_limits<double>::infinity();
    costMatrix[1][2] = 7;
    costMatrix[1][3] = 11;
    costMatrix[1][4] = 7;
    costMatrix[1][5] = 10;

    costMatrix[2][0] = 4;
    costMatrix[2][1] = 7;
    costMatrix[2][2] = std::numeric_limits<double>::infinity();
    costMatrix[2][3] = 4;
    costMatrix[2][4] = 3;
    costMatrix[2][5] = 10;

    costMatrix[3][0] = 8;
    costMatrix[3][1] = 11;
    costMatrix[3][2] = 4;
    costMatrix[3][3] = std::numeric_limits<double>::infinity();
    costMatrix[3][4] = 5;
    costMatrix[3][5] = 11;

    costMatrix[4][0] = 7;
    costMatrix[4][1] = 7;
    costMatrix[4][2] = 3;
    costMatrix[4][3] = 5;
    costMatrix[4][4] = std::numeric_limits<double>::infinity();
    costMatrix[4][5] = 7;

    costMatrix[5][0] = 14;
    costMatrix[5][1] = 10;
    costMatrix[5][2] = 10;
    costMatrix[5][3] = 11;
    costMatrix[5][4] = 7;
    costMatrix[5][5] = std::numeric_limits<double>::infinity();

    AlgorithmSolver *solver = new AlgorithmSolver(costMatrix, size);

    solver->printCostMatrix();
    std::cout << "==========================================================\n";

    solver->solve();
    solver->printCostMatrix();

    return 0;
}
