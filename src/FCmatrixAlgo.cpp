#include "FCmatrixAlgo.h"
#include <iostream>

using namespace std;

//Gaussian elimination without pivoting
void FCmatrixAlgo::GaussElimination(Eigen::MatrixXd& A, Eigen::VectorXd& B) {
    int n;
    double lambda;
    n=A.rows(); 
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j<n; j++) {
            lambda = A(j,i)/A(i,i);
            A.row(j)=A.row(j)-lambda*A.row(i);
            B.row(j)=B.row(j)-lambda*B.row(i);
        }
    }
    for (int r = 1; r < n; r++){
        for (int k = 0; k < r; k++){
            A(r,k) = 0;
        }
    }
} 

//Gaussian elimination with pivoting
void FCmatrixAlgo::GaussEliminationPivot(Eigen::MatrixXd& A, Eigen::VectorXd& B) { 
    int n;
    double lambda;
    Eigen::VectorXd P(B);
    n = A.rows();

    //Maximum of each row
    for (int i = 0; i < n; i++) {
        if (fabs(A.row(i).maxCoeff()) >= fabs(A.row(i).minCoeff())) {
            P[i] = A.row(i).maxCoeff();
        } else {
            P[i] = fabs(A.row(i).minCoeff());
        }            
    }


    for (int i = 0; i < n-1; i++) {
        //Line swap for the best pivot
        for (int j = i+1; j < n; j++) {
             if (fabs(A(i,i)/P[i]) < fabs(A(j,i)/P[j])) {
                 A.row(i).swap(A.row(j));
                 B.row(i).swap(B.row(j));
             }
        }

        //Gaussian elimination
        for (int k = i+1; k < n; k++) {
            lambda = A(k,i)/A(i,i);
            A.row(k)=A.row(k)-lambda*A.row(i);
            B.row(k)=B.row(k)-lambda*B.row(i);
        }
    }
    for (int r = 1; r < n; r++){
        for (int k = 0; k < r; k++){
            A(r,k) = 0;
        }
    }
}

//LU decomposition (Doolittle) without pivoting
void FCmatrixAlgo::LUdecomposition(Eigen::MatrixXd& A) {
    int n;
    double lambda;
    n = A.rows();

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> L(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> U(n, n);

    for (int i = 0; i < n; ++i) {
        L(i,i)= 1;
    }

    //Matrix U --> A
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            lambda = A(j,i)/A(i,i);
            A.row(j) = A.row(j)-lambda*A.row(i);
            L(j,i) = lambda;
        }  
    } 

    U = A;
    A = A+L;
    for (int i=0; i < n; ++i) {  
        A(i,i) -= 1;
    }
}

//LU decomposition (Doolittle) with pivoting
void FCmatrixAlgo::LUdecompositionPivot(Eigen::MatrixXd& A, Eigen::VectorXd& B) { 
    int n;
    double lambda = 0.;
    n = A.rows();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> L(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> U(n, n);
    Eigen::VectorXd P(B);

    for (int i = 0; i < n; ++i) {
        L(i,i)= 1;
        P(i) = 0;
    }

    //Maximum of each row
    for (int i = 0; i < n; i++) {
        if (fabs(A.row(i).maxCoeff()) >= fabs(A.row(i).minCoeff())) {
            P[i] = A.row(i).maxCoeff();
        } else {
            P[i] = fabs(A.row(i).minCoeff());
        }            
    }


    for (int i = 0; i < n-1; i++) {
        //Line swap for best pivot
        for (int j = i+1; j < n; j++) {
             if (fabs(A(i,i)/P[i]) < fabs(A(j,i)/P[j])) {
                 A.row(i).swap(A.row(j));
                 B.row(i).swap(B.row(j));
             }
        }

        //Gaussian elimination
        for (int k = i+1; k < n; k++) {
            lambda = A(k,i)/A(i,i);
            A.row(k)=A.row(k)-lambda*A.row(i);
            L(k,i) = lambda;
        }
    }

    U = A;
    A = A+L;

    for (int i=0; i < n; ++i) {  
        A(i,i) -= 1.;
    }
} 

//Inverse matrix, solving system for all columns
void FCmatrixAlgo::InverseMatrix(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& A) {
    if (A.rows() != A.cols()) {
        cout << "\n There is no inverse for non square matrix" << endl;
        return;
    } else if (Determinant(A) == 0) {
        cout << "\n There is no inverse for singular matrix" << endl;
        return;
    }
    
    int n = A.rows();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> I(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Aux(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> X(n, n);
    I.setIdentity();
    for (int i = 0; i < n; i++) {
        Aux = A;
        EqSolver inverse(Aux, I.col(i));
        X.col(i) = inverse.GaussSolver(true);
    }
    A = X;
}

//Determinant with gaussian elimination with pivoting
double FCmatrixAlgo::Determinant(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& A) {
    if (A.rows() != A.cols()) {
        cout << "\n There is no determinant for non square matrices" << endl;
        return 0;
    } 

    int n = A.rows();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Aux(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, 1> P(n, 1);
    Aux=A;
    P = A.col(1);
    double determinant = 1.;        
    double lambda;
    double swap = 1;

    //Maximum of each row
    for (int i = 0; i < n; i++) {
        if (fabs(Aux.row(i).maxCoeff()) >= fabs(Aux.row(i).minCoeff())) {
            P[i] = Aux.row(i).maxCoeff();
        } else {
            P[i] = fabs(Aux.row(i).minCoeff());
        }            
    }

    for (int i = 0; i < n-1; i++) {
        //Line swap for best pivot
        for (int j = i+1; j < n; j++) {
             if (fabs(Aux(i,i)/P[i]) < fabs(Aux(j,i)/P[j])) {
                 Aux.row(i).swap(Aux.row(j));
                 swap *= -1;
             }
        }

        //Gaussian elimination
        for (int k = i+1; k < n; k++) {
            lambda = Aux(k,i)/Aux(i,i);
            Aux.row(k)=Aux.row(k)-lambda*Aux.row(i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        determinant *= Aux(i,i);
    }
    
    return swap*determinant;
}