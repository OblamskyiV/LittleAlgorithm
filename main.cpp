#include <QtCore/QCoreApplication>
#include "algorithmsolver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    const unsigned int size = 4;

    double** costMatrix = new double*[size];
    for (unsigned int i = 0; i < size; ++i)
    {
        costMatrix[i] = new double[size];
    }

    costMatrix[0][0] = std::numeric_limits<double>::infinity();
    costMatrix[0][1] = 88;
    costMatrix[0][2] = 5;
    costMatrix[0][3] = 7;

    costMatrix[1][0] = 2;
    costMatrix[1][1] = std::numeric_limits<double>::infinity();
    costMatrix[1][2] = 4;
    costMatrix[1][3] = 14;

    costMatrix[2][0] = 6;
    costMatrix[2][1] = 7;
    costMatrix[2][2] = std::numeric_limits<double>::infinity();
    costMatrix[2][3] = 9;

    costMatrix[3][0] = 1;
    costMatrix[3][1] = 3;
    costMatrix[3][2] = 5;
    costMatrix[3][3] = std::numeric_limits<double>::infinity();

    AlgorithmSolver *solver = new AlgorithmSolver(costMatrix, size);
    solver->print();
    std::cout << solver->findMinimalRowElement(1);

    return 0;
}
