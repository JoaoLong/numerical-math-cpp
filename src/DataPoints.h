#ifndef __DATAPOINTS__
#define __DATAPOINTS__

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
#include <map>

#include "TCanvas.h" 
#include "TRootCanvas.h"
#include "TH2F.h" 
#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TStyle.h"

//Class to store points (xi, yi) and draw them in a graph

class DataPoints {
    public:
        //Constructors and destructor
        DataPoints() = default;
        DataPoints(int, double*, double*);
        DataPoints(const std::vector< std::pair<double,double> >&); 
        DataPoints(const std::vector< double>&, const std::vector< double>&); 
        virtual ~DataPoints();

        //Getters to members
        const std::vector< std::pair<double,double>>& GetPoints();
        const TGraph& GetGraph();

        //Draw points in a graph
        virtual void Draw(std::string);
        
        //Operator to write points coordinates quickly
        friend std::ostream& operator<< (std::ostream&, const DataPoints&);

    protected:
        std::vector<std::pair<double,double>> P; // points
        TGraph* graph;
};

#endif