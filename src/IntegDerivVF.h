#ifndef __INTEGDERIVVF__
#define __INTEGDERIVVF__

#include "VectorField.h"
#include "IntegDerivND.h"

//Class to differentiate and integrate N dimensional vector fields (f1(x1, ..., xn), ..., fn(x1, ..., xn))

class IntegDerivVF {
    public:
        //Constructor and destructor
        IntegDerivVF() = default;
        IntegDerivVF(VectorField&);
        ~IntegDerivVF() = default;

        //Jacobian matrix
        Eigen::MatrixXd JacobianMatrix(double, std::vector<double>);

        //Divergence
        double Divergence(double, std::vector<double>);

        //Curl
        Eigen::VectorXd Curl(double, std::vector<double>);

        //Laplacian
        Eigen::VectorXd Laplacian(double, std::vector<double>);

        //Integrals (?)
        
    private:
        //Vector field to differentiate and integrate
        VectorField& F;
};

#endif  