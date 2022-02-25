#ifndef __XVAR__
#define __XVAR__

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
#include "TCanvas.h" 
#include "TRootCanvas.h"
#include "TH2F.h" 
#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

//Class to store dependent variables of point (t, x1(t), ..., xn(t)), solution of a system of ordinary differential equations

class Xvar {
    public:
        //Constructors and destructor
        Xvar() = default; 
        Xvar(int); 
        Xvar(std::vector<double>);
        Xvar(const std::initializer_list<double>&); 
        Xvar(const Xvar&); 
        ~Xvar() = default;

        //Assignment operator
        Xvar& operator=(const Xvar&); 
        
        //Sum operator
        Xvar operator+(const Xvar&); 

        //Access ith component of vector x
        double& operator[](int); 

        //Multiplication with scalar
        friend Xvar operator*(double, const Xvar&); 

        //Write dependent variables xi
        friend std::ostream& operator<< (std::ostream&, const Xvar&);
        
        //Accessor to x
        std::vector<double>& X(); 
    
    protected:
        //Dependent variables xi
        std::vector<double> x;
};

#endif