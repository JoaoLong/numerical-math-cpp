#ifndef __PDEPOINT__
#define __PDEPOINT__

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip> 
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ostream>
#include <string>
#include <list>
#include <initializer_list>
#include <cmath>
#include "TLatex.h"
#include "TCanvas.h" // include class TCanvas from ROOT library
#include "TRootCanvas.h"
#include "TH2F.h" // histogram 2D
#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

//Class to store point (x1, ..., xn, y(x1, ..., xn)), solution of a partial differential equation

class PDEpoint {
    public:
        //Constructors and destructor
        PDEpoint() = default;
        PDEpoint(const std::vector<double>&, double);
        virtual ~PDEpoint() = default;

        //Setter for x and y
        void SetPDEpoint(std::vector<double>&, double);
        
        //Accessor to independent variables
        std::vector<double>& X(); 

        //Acessor to dependent variable, y(x1, ..., xn)
        double& Y(); 

        //Write independent variables xi and dependent variable y
        friend std::ostream& operator<< (std::ostream&, const PDEpoint&);

    private:
        //Independent variable
        std::vector<double> x; 

        //Dependent variable
        double y;  

        //Dimension of function solution, y(x1, ..., xn), = number of independent variables
        int dim;
};

#endif