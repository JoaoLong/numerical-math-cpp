#ifndef __EQSOLVER__
#define __EQSOLVER__

#include "FCmatrixAlgo.h"

using namespace std;

//Class to solve systems of linear equations with linear algebra methods

class EqSolver {
    public:

      //Constructors and destructor
      EqSolver() = default;
      EqSolver(const Eigen::MatrixXd&, const Eigen::VectorXd&); 
      ~EqSolver() = default;

      //Solve with gaussian elimination (pivoting available)
      const Eigen::VectorXd& GaussSolver(bool);

      //Solve with LU decomposition (pivoting available)
      const Eigen::VectorXd& LUSolver(bool);

      //Solve with iterative Jacobi method
      void IterativeJacobiSolver(Eigen::VectorXd&, int, double); 

      //Solve with iterative Gauss-Seidel method
      void IterativeGaussSeidelSolver(Eigen::VectorXd&, int, double);

    private:
      //For system Ax = B
      Eigen::MatrixXd A; 
      Eigen::VectorXd B; 
};

#endif