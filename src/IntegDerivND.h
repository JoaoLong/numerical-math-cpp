#ifndef __INTEGDERIVND__
#define __INTEGDERIVND__

#include "FunctorND.h"
#include "FCrand.h"
#include "FCmatrixAlgo.h"

//Class to differentiate and integrate N dimensional functions f(x1, ..., xn)

class IntegDerivND {
    public:
        //Constructor and destructor
        IntegDerivND() = default;
        IntegDerivND(FunctorND&);
        ~IntegDerivND() = default;

        //Monte Carlo multiple integral on an interval [x1i, x1f] x ... x [xni, xnf]
        double IntegrateIntervalMC(std::vector<std::pair<double, double>>, double&, int&);

        //Monte Carlo multiple integral on a general region
        double IntegrateRegionMC(std::function<int(std::vector<double>)>, std::vector<std::pair<double, double>>, double&, int&);   

        //First partial derivative methods, ∂f/∂xi
        double D1backward(int, double, std::vector<double>);
        double D1central(int, double, std::vector<double>);
        double D1forward(int, double, std::vector<double>);
        double D1fivepoint(int, double, std::vector<double>);

        //Second partial derivative methods, ∂²f/∂xi²
        double D2backward(int, double, std::vector<double>);
        double D2central(int, double, std::vector<double>);
        double D2forward(int, double, std::vector<double>);
        double D2fivepoint(int, double, std::vector<double>);

        //Second mixed partial derivative methods, ∂²f/∂xi∂xj
        double D2mixedcentral(int, int, double, double, std::vector<double>);
        double D2mixedfivepoint(int, int, double, double, std::vector<double>);
         
        //Gradient, hessian matrix, and laplacian
        Eigen::VectorXd Gradient(double, std::vector<double>);
        Eigen::MatrixXd Hessian(double, double, std::vector<double>);
        double Laplacian(double, std::vector<double>);
        
    private:
        //Function to differentiate and integrate
        FunctorND& F;
};

#endif  