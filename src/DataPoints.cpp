#include "DataPoints.h"
#include <iostream>

using namespace std;

//Constructor with C array
DataPoints::DataPoints(int N, double* x, double* y) {
    P.resize(N);
    for (int i = 0; i < N; i++) {
        P[i].first = x[i];
        P[i].second = y[i];
    }
    graph = new TGraph(P.size());
}

//Constructor with vector of pairs
DataPoints::DataPoints(const std::vector<std::pair<double,double>> &A) {
    P.resize(A.size());
    copy(A.begin(), A.end(), P.begin());
    graph = new TGraph(P.size());
}

//Constructor with two vectors of coordinates
DataPoints::DataPoints(const std::vector<double>& x, const std::vector<double>& y) {
    P.resize(x.size());
    for (int i = 0; i < P.size(); i++) {
        P[i] = make_pair(x[i], y[i]);
    }
    graph = new TGraph(P.size());
}

//Destructor
DataPoints::~DataPoints() {
    delete graph;
}

//Points getter
const std::vector<std::pair<double,double>>& DataPoints::GetPoints() {
    int N = P.size();

    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-i-1; j++) {
            if (P[j].first > P[j+1].first) {
                P[j].swap(P[j+1]);
            }
        }    
    }
    return P;
}

//Graph getter
const TGraph& DataPoints::GetGraph() {
    return *graph;    
}

//Plots the points in a graph
void DataPoints::Draw(string s) {
    for (int i = 0; i < P.size(); ++i) {
        graph->SetPoint(i, P[i].first, P[i].second);
    }

    graph->SetMarkerColor(kBlack);
    graph->SetMarkerStyle(kFullCircle);
    graph->SetMarkerSize(1.5);
    graph->GetXaxis()->SetTitle("x");
    graph->GetYaxis()->SetTitle("y");
    graph->GetXaxis()->SetLimits(GetPoints()[0].first*1.1, GetPoints()[GetPoints().size()-1].first*1.1);
    
    string title = "Data interpolation - " + s;
    graph->SetTitle(&title[0]);
    graph->Draw("AP");
}

//Operator <<, prints the number of points and their coordinates
std::ostream& operator<< (std::ostream& s, const DataPoints& data) {
    s << "Number of points: " << data.P.size() << endl;
    s << "Coordinates: \n" << endl; 
    for (int i = 0; i < data.P.size(); i++) {
        s << "x = " << data.P[i].first << "  |  " << "y = " << data.P[i].second << "\n" << endl;
    }    
    return s;
}