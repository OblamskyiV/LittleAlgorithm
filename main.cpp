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
    costMatrix[0][1] = 4;
    costMatrix[0][2] = 18;
    costMatrix[0][3] = 11;
    costMatrix[0][4] = 27;

    costMatrix[1][0] = 28;
    costMatrix[1][1] = std::numeric_limits<double>::infinity();
    costMatrix[1][2] = 3;
    costMatrix[1][3] = 20;
    costMatrix[1][4] = 2;

    costMatrix[2][0] = 7;
    costMatrix[2][1] = 19;
    costMatrix[2][2] = std::numeric_limits<double>::infinity();
    costMatrix[2][3] = 5;
    costMatrix[2][4] = 13;

    costMatrix[3][0] = 2;
    costMatrix[3][1] = 22;
    costMatrix[3][2] = 9;
    costMatrix[3][3] = std::numeric_limits<double>::infinity();
    costMatrix[3][4] = 24;

    costMatrix[4][0] = 18;
    costMatrix[4][1] = 10;
    costMatrix[4][2] = 29;
    costMatrix[4][3] = 20;
    costMatrix[4][4] = std::numeric_limits<double>::infinity();

    AlgorithmSolver *solver = new AlgorithmSolver(costMatrix, size);

    solver->printCostMatrix();
    std::cout << "==========================================================\n";

    solver->solve();
    //solver->printCostMatrix();

    return 0;
}
