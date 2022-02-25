#include "VectorField.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
VectorField::VectorField(vector<FunctorND>& Fi) : F(Fi) {
    if (Fi.size() == 1) {
        cout << "\n A 1-dimensional vector field is just a function. Please use Functor class." << endl;
        exit(0);
    }

    for (int i = 0; i < Fi.size(); i++) {
        if (Fi[i].GetDimension() != Fi.size()) {
            cout << "\n A vector field must be R^n -> R^n." << endl;
            exit(0); 
        }
    }    
}

//Operator to access ith component of field, F[i]
FunctorND& VectorField::operator[](int i) {
    if (i >= F.size()) {
        cout << "\n The vector field is " << F.size() << " dimensional." << endl;
        exit(0);
    }
    return F[i];
}

//Calculate value of vector field at a point, (f1(x1, ..., xn), ..., fn(x1, ..., xn))
vector<double> VectorField::operator() (vector<double> x) {
    int N = F.size();
    if (x.size() != N) {
        cout << "\n The vector field is " << N << " dimensional." << endl;
        exit(0);
    }
    vector<double> v;
    v.resize(N);
    for (int i = 0; i < N; i++) {
        v[i] = F[i](x);
    }

    return v; 
}

/*
//Draw vector field in 2D or 3D (TO IMPLEMENT)
void VectorField::Draw(int i, double xi, double xf, double yi, double yf, int nx, int ny, std::string xtitle, std::string ytitle, std::string ztitle) {
    if (dim == 2) {    
        TApplication *app = new TApplication("app", nullptr, nullptr);
        TCanvas *c = new TCanvas("c", "Graph of the points in class DataPoints", 0, 0, 1920, 1080);
        TRootCanvas *close = (TRootCanvas *)c->GetCanvasImp();
        close->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

        double dx = (xf-xi)/(nx-1);
        double dy = (yf-yi)/(ny-1);

        TGraph2D *graph = new TGraph2D(nx*ny);
        graph->SetLineColor(kBlue);
        graph->SetLineWidth(3);
        graph->SetName("Graph");
        graph->SetMarkerStyle(kFullCircle);
        graph->SetMarkerSize(.1);
        graph->SetMarkerColor(kBlack);
        graph->SetFillColor(68);
       
        string title = "Grafico de f(x,y) = " + this->name;
        graph->SetTitle(&title[0]);

        vector<double> v;
        v.resize(2);

        for (int i = 0; i < nx; i++) {
            v[0] = xi+i*dx;
            for (int j = 0; j < ny; j++) {
                v[1] = yi+j*dy;
                graph->SetPoint(nx*i+j, v[0], v[1], operator()(v));
            }    
        }
        gStyle->SetPalette(kRainBow);
        graph->GetXaxis()->SetTitle(&xtitle[0]);
        graph->GetYaxis()->SetTitle(ytitle.c_str());
        graph->GetZaxis()->SetTitle(ztitle.c_str());
        graph->Draw("surf2");
        c->Update();
        c->SaveAs("functorND.pdf");
        app->Run();

    } else {
        cout << "There is no draw for more than 3 dimensions." << endl;
    }    
}
*/

//Getter for dimension
int VectorField::GetDimension() {
    return F.size();
}