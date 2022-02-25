#include "EqSolver.h"
#include <iostream>

using namespace std;

//Test main of class EqSolver

int main() {

    Eigen::MatrixXd A;
    Eigen::VectorXd B;
    
    A.resize(10,10);
   
    A << -3.2, -0.8 ,   0  ,  0  ,  0  ,  0  ,  0 ,   0 ,   0 ,   0,
         -0.8 ,-3.2 ,-0.8 ,   0  ,  0   , 0  ,  0  ,  0 ,   0 ,   0,
            0, -0.8, -3.2 ,-0.8  ,  0  ,  0 ,   0  ,  0  ,  0 ,   0,
            0 ,   0, -0.8 ,-3.2 ,-0.8 ,   0  ,  0  ,  0  ,  0 ,   0,
            0 ,   0 ,   0 ,-0.8 ,-3.2 ,-0.8  ,  0 ,   0 ,   0 ,   0,
            0   , 0  ,  0  ,  0, -0.8, -3.2 ,-0.8  ,  0  ,  0 ,   0,
            0  ,  0  ,  0 ,   0 ,   0, -0.8 ,-3.2 ,-0.8  ,  0 ,   0,
            0  ,  0  ,  0  ,  0  ,  0 ,   0, -0.8, -3.2, -0.8  ,  0,
            0 ,   0  ,  0  ,  0  ,  0  ,  0 ,   0, -0.8, -3.2, -0.8,
            0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0 ,   0 ,-0.8, -3.2;

    B.resize(10,1);
    
    B << -6.1125,   
        -11.1,
        -5.325,
        7.6125,
        10.965,
        3.465,
        -8.8425,
        -10.6125,
        -1.4475,
        9.7725;  

    Eigen::VectorXd P(B);

    //Jacobi method
    EqSolver jacobi(A,B);
    Eigen::VectorXd X1;
    X1.resize(A.rows(), 1);
    X1 << 0.001, 0.001, 0.001, 0.001;
    jacobi.IterativeJacobiSolver(X1, 1000, 0.00000001);
    cout << "\n" << "Solution with Jacobi solver" << "\n" << X1 << "\n" << endl;
    for (int i = 0; i < 100; i++) {
        cout << "-";
    } 
    cout << "\n" << endl; 
   

    //Gauss-Seidel method
    EqSolver gaussseidel(A,B);
    Eigen::VectorXd X2;
    X2.resize(A.rows(), 1);
    X2 << 0,0,0,0;
    gaussseidel.IterativeGaussSeidelSolver(X2, 1000, 0.00000001);
    cout << "\n" << "Solution with Gauss-Seidel solver" << "\n" << X2 << "\n" << endl;
       

    //Gaussian elimination method
    for (int i = 0; i < 100; i++) {
        cout << "-";
    } 
    cout << "\n Solution with gaussian elimination solver:\n" << endl;
    EqSolver gauss(A,B);    
    cout <<"\n"<< gauss.GaussSolver(false) << "\n" << endl;

    //Gaussian elimination pivoting method
    for (int i = 0; i < 100; i++) {
        cout << "-";
    } 
    cout << "\n Solution with gaussian elimination pivoting solver:\n" << endl;
    EqSolver gaussp(A,B);    
    cout <<"\n"<< gaussp.GaussSolver(true) << "\n" << endl;
    

    //LU decomposition method
    for (int i = 0; i < 100; i++) {
        cout << "-";
    } 
    cout << "\n Solution with LU decomposition solver:\n" << endl;
    EqSolver LU(A,B);
    cout << LU.LUSolver(false) << "\n"<< endl; 


    //LU decomposition pivoting method
    for (int i = 0; i < 100; i++) {
        cout << "-";
    } 
    cout << "\n Solution with LU decomposition pivoting solver:\n" << endl;
    EqSolver LUp(A,B);
    cout << LUp.LUSolver(true) << "\n"<< endl; 

    return 0;
}