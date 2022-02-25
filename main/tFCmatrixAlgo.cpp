#include "FCmatrixAlgo.h"
#include <iostream>

using namespace std;

//Test main of class FCmatrixAlgo

int main() {

    Eigen::MatrixXd C;
    C.resize(2, 2);

    C << 1, 1,
         1, 1;

    Eigen::MatrixXd D;
    D.resize(4, 4);
    D << 5, 6, 6, 8,
         2, 2, 2, 8,
         6, 6, 2, 8,
         2, 3, 6, 7;
    
    Eigen::MatrixXd E;
    E.resize(4, 4);
    E << 5, 0, 0, 1,
         0, 5, 0, 3,
         2, 0, 5, 4,
         3, 0, 5, 5;

    cout << "Determinant |C|: " << FCmatrixAlgo::Determinant(C) << endl;
    cout << "Inverse |C|: " << endl;
    FCmatrixAlgo::InverseMatrix(C);
    cout << C << endl;

    cout << "\n\n";

    cout << "Determinant |C|: " << FCmatrixAlgo::Determinant(D) << endl;
    cout << "Inverse |D|: " << endl;
    FCmatrixAlgo::InverseMatrix(D);
    cout << D << endl;

    cout << "\n\n";
    
    cout << "Determinant |E|: " << FCmatrixAlgo::Determinant(E) << endl;
    cout << "Inverse |E|: " << endl;
    FCmatrixAlgo::InverseMatrix(E);
    cout << E << endl;

    return 0;
}