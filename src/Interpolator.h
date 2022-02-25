#ifndef __INTERPOLATOR__
#define __INTERPOLATOR__

#include "EqSolver.h"
#include "DataPoints.h"

//Class to interpolate points (xi, yi) 

class Interpolator : public DataPoints {
    public:
        //Constructors and destructor
        Interpolator() = default;
        Interpolator(int, double*, double*); 
        Interpolator(const std::vector< std::pair<double,double> >&);
        Interpolator(const std::vector< double>&, const std::vector< double>&);
        virtual ~Interpolator() = default;

        //Polynomial Lagrange interpolation
        double InterpolateLagrange(double); 

        //Polynomial Newton interpolation
        double InterpolateNewton(double); 

        //Polynomial Neville interpolation
        double InterpolateNeville(double); 

        //Cubic spline interpolation
        double InterpolateSpline3(double); 

        //Trigonometric interpolation
        double InterpolateTrigonometric(double); 

        //Draw points and interpolated curve, with string "Lagrange", "Newton", "Spline3", "Trigonometric", "All", "Points"
        void Draw(std::string);

        //Getter for interpolated functions
        const TF1& GetFunction(std::string); 

    private:
        //Map of interpolated functions, with key = "Lagrange", "Newton", "Neville", "Spline3", "Ttrigonometric"  
        std::map<std::string, TF1*> MI; 
};

#endif