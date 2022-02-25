#ifndef __FCMATRIXALGO__
#define __FCMATRIXALGO__

#include <Eigen/Core>
#include <Eigen/Dense>
#include "EqSolver.h"

//Class with matrix algorithms

class FCmatrixAlgo {
    public:
        //Constructor and destructor (no members, all methods static)
        FCmatrixAlgo() = default; 
        ~FCmatrixAlgo() = default;

        //Gaussian elimination without pivoting
        static void GaussElimination(Eigen::MatrixXd&, Eigen::VectorXd&);

        //Gaussian elimination with pivoting
        static void GaussEliminationPivot(Eigen::MatrixXd&, Eigen::VectorXd&);
        
        //LU decomposition (Doolittle) without pivoting
        static void LUdecomposition(Eigen::MatrixXd&);

        //LU decomposition (Doolittle) with pivoting
        static void LUdecompositionPivot(Eigen::MatrixXd&, Eigen::VectorXd&); 

        //Inverse matrix calculator
        static void InverseMatrix(Eigen::MatrixXd&);

        //Determinant calculator
        static double Determinant(Eigen::MatrixXd&);
};

#endif