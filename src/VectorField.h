#ifndef __VECTORFIELD__
#define __VECTORFIELD__

#include <string>
#include "FunctorND.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TRootCanvas.h"
#include "TH2F.h"
#include "TApplication.h"
#include "TGraph2D.h"
#include "TLatex.h"
#include "TStyle.h"

//Class to define an N dimensional vector field (f1(x1, ..., xn), ..., fn(x1, ..., xn))

class VectorField {
    public:
        //Constructors and destructor
        VectorField() = default;
        VectorField(std::vector<FunctorND>&);
        ~VectorField() = default;

        //Operator to access ith component of field, F[i]
        FunctorND& operator[](int i);

        //Calculate value of vector field at a point, (f1(x1, ..., xn), ..., fn(x1, ..., xn))
        std::vector<double> operator() (std::vector<double>);

        /*
        //Draw vector field in 2D or 3D (TO IMPLEMENT)
        void Draw(int, double, double, double, double, int, int, std::string, std::string, std::string);
        */
        
        //Getter for dimension
        int GetDimension();

    private:
        //Vector field (f1, ..., fn)
        std::vector<FunctorND>& F;
};

#endif
