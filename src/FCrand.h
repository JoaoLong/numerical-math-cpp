#ifndef __FCRAND__
#define __FCRAND__

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip> 
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ostream>
#include <string>
#include <functional>

#include "TCanvas.h" 
#include "TRootCanvas.h"
#include "TH2F.h" 
#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#include "TRandom3.h"

//Class to generate random numbers with ROOT

class FCrand {
    public:
        //Constructor and destructor
        FCrand(int); 
        ~FCrand();

        //Update seed
        void UpdateSeed(int);

        //Generate one random between [0,1]
        double GetRandom();

        //Generate one random between [min,max]
        double GetRandom(double, double);

        //Generate N random numbers from distribution p(x)
        double GetRandomDistribution(double, double, std::function<double(double)>);
        
        //Generate N randoms between [0,1]
        double* GetRandom(int);

        //Generate N randoms between [min,max]
        double* GetRandom(int, double, double);

        //Generate N random numbers from distribution p(x)
        double* GetRandomDistribution(int, double, double, std::function<double(double)>);

    private:
        TRandom3* gRandom;
};

#endif