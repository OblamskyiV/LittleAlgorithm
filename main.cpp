#include <QtCore/QCoreApplication>
#include "algorithmsolver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    const unsigned int size = 5;

    double** costMatrix = new double*[size];
    for (unsigned int i = 0; i < size; i++)
    {
        costMatrix[i] = new double[size];
    }

    costMatrix[0][0] = std::numeric_limits<double>::infinity();
    costMatrix[0][1] = 1;
    costMatrix[0][2] = 7;
    costMatrix[0][3] = 3;
    costMatrix[0][4] = 14;

    costMatrix[1][0] = 3;
    costMatrix[1][1] = std::numeric_limits<double>::infinity();
    costMatrix[1][2] = 6;
    costMatrix[1][3] = 9;
    costMatrix[1][4] = 1;

    costMatrix[2][0] = 6;
    costMatrix[2][1] = 14;
    costMatrix[2][2] = std::numeric_limits<double>::infinity();
    costMatrix[2][3] = 3;
    costMatrix[2][4] = 7;

    costMatrix[3][0] = 2;
    costMatrix[3][1] = 3;
    costMatrix[3][2] = 5;
    costMatrix[3][3] = std::numeric_limits<double>::infinity();
    costMatrix[3][4] = 9;

    costMatrix[4][0] = 15;
    costMatrix[4][1] = 7;
    costMatrix[4][2] = 11;
    costMatrix[4][3] = 2;
    costMatrix[4][4] = std::numeric_limits<double>::infinity();

    AlgorithmSolver *solver = new AlgorithmSolver(costMatrix, size);

    solver->printCostMatrix();
    std::cout << "==========================================================\n";

    solver->solve();
    //solver->printCostMatrix();

    return 0;
}
