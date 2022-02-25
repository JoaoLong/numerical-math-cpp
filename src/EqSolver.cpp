#include "EqSolver.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Constructor
EqSolver::EqSolver(const Eigen::MatrixXd& Ai, const Eigen::VectorXd& Bi) : A(Ai), B(Bi) { ; }

//Gaussian elimination solver, boolean for pivoting
const Eigen::VectorXd& EqSolver::GaussSolver(bool pivot) {
    int n = A.rows();

    if (pivot == false) {
        FCmatrixAlgo::GaussElimination(A, B);
    } else {
        FCmatrixAlgo::GaussEliminationPivot(A, B);
    }    

    Eigen::Matrix<double,Eigen::Dynamic,1> &X(B);

    for (int k = n-1; k >= 0; k--) {
        double sumB = 0.;
        for (int i = k+1; i < n; i++) {
            sumB += X[i]*A(k, i);
        }   
        X[k] = (B[k] - sumB)/A(k,k);
    }

    return X;
}

//LU decomposition solver, boolean for pivoting
const Eigen::VectorXd& EqSolver::LUSolver(bool pivot) {
    int n = A.rows();

    if (pivot == false) {
        FCmatrixAlgo::LUdecomposition(A);
    } else {
        FCmatrixAlgo::LUdecompositionPivot(A, B);
    }

    Eigen::Matrix<double,Eigen::Dynamic,1> &X(B);
    Eigen::Matrix<double,Eigen::Dynamic,1> &Y(B);

    // forward solution (Ly=b, y=Ux)
    Y[0] = B[0];
    for (int k = 0; k < n; k++) {
        double sumF = 0.;
        for (int i = 0; i < k; i++) {
            sumF += Y[i]*A(k, i);
        }
        Y[k] = B[k] - sumF;
    }

    // backward solution (Ux=y)
    for (int k = n-1; k >= 0; k--) {
        double sumB = 0.;
        for (int i = k+1; i < n; i++) {
            sumB += X[i]*A(k, i);
        }   
        X[k] = (Y[k] - sumB)/A(k,k);
    }

    return X;
}

//Jacobi method solver; only works if (matrix diagonal > sum other elements in row)
void EqSolver::IterativeJacobiSolver(Eigen::VectorXd& X, int itmax, double tol) { 
    bool btol = false;
    int it = 0; 
    int m = X.rows();

    int count = 0;

    for (int i = 0; i < m; i++) {
        if (X[i] == 0) {
            count += 1;
        }
    }

    if (count == m) {
        cout << "\n Jacobi iterative method only works if initial condition is not zero." << endl;
        return;
    }
    

    Eigen::Matrix<double, Eigen::Dynamic, 1> X_aux(m,1);

    while (!btol && (it < itmax)) {
        X_aux = X; 
        for (int i=0; i<A.rows(); i++) {
            X[i] = 0.;
            for (int j=0; j<m; j++) {
                if (i != j) {
                    X[i] += -A(i,j)*X_aux[j];
                }
            }    
            X[i] += B[i];
            X[i] /= A(i,i); 
                
            //Check convergence
            if (fabs(X[i] - X_aux[i]) < tol) {
                btol = true;
            } else { 
                btol = false;
            }
            
        }   
        it+=1; 
    }     
    cout << "\n" << "Jacobi iterations: " << it << endl;
}

//Gauss-Seidel method solver; only works if (matrix diagonal > sum other elements in row)
void EqSolver::IterativeGaussSeidelSolver(Eigen::VectorXd& X, int itmax, double tol) {
    bool btol = false;
    int it = 0; 
    int m = X.rows();
    
    Eigen::Matrix<double, Eigen::Dynamic, 1> X_aux(m,1);

    while (!btol && (it < itmax)) {
    //while (it < itmax) {
        X_aux = X; 
        for (int i = 0; i < A.rows(); i++) {
            X[i] = 0.;
            for (int j=0; j<m; j++) {
                if (i != j) {
                    X[i] += -A(i,j)*X[j];
                }
            }    
            X[i] += B[i];
            X[i] /= A(i,i); 
                
            //Check convergence
            if (fabs(X[i] - X_aux[i]) < tol) {
                btol = true;
            } else { 
                btol = false;
            }
            
        } 
        it+=1; 
    }     
    cout << "\n" << "Gauss-Seidel iterations: " << it << endl;
}