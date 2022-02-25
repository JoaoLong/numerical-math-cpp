#include "BVPsolver.h"
#include <iostream>

using namespace std;

//Constructor
BVPsolver::BVPsolver(const ODEpoint& a, std::vector<std::function<double(ODEpoint)>>& fi, std::vector<std::pair<int, std::pair<double, double>>> ci) 
                    : ODEsolver(a, fi), cfront(ci) {

    if (X0.X().size() <= cfront.size()) {
        cout << "\n There must be at least one initial condition." << endl;
        cout << "\n If you wish, define one of the boundary conditions as a initial condition, to have a starting point in time." << endl;
        exit(0);
    }
}

//Shooting method with guess as interval [guess.first, guess.second], for bisection method
const std::vector<ODEpoint>& BVPsolver::ShootingSolver(double step, double tmax, double error, pair<double, double> guess) {
    if (cfront.size() > 1) {
        cout << "\n Please use ShootingNDSolver method for more than one boundary condition." << endl;
        exit(0);
    }  

    if (tmax+step <= X0.T() || tmax+step <= cfront[0].second.first) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }

    int k = cfront[0].first;

    double a = guess.first;
    double b = guess.second;

    //Root-finding
    std::function<double(double)> g1 = [this, k, step, tmax](double init) {
        X0.X()[k] = init;
        sol = ODEsolver::RungeKutta4Solver(step, tmax);
        return ODEsolver::Evaluate(cfront[0].second.first, "RK4")[k] - cfront[0].second.second;
    };
    
    Functor* shooting = new Functor("shoot", g1);
    RootFinder* root = new RootFinder(*shooting);
    root->BisectionMethod(a, b, error);

    return sol;
}

//Multidimensional shooting method, guess for NewtonND and noninit - initial values to find (ex: x0 - boundary, y0, z0 - initial)
const std::vector<ODEpoint>& BVPsolver::ShootingNDSolver(double step, double tmax, double error, vector<int> noninit, vector<double> guess) {
    if (cfront.size() == 1) {
        cout << "\n Please use ShootingSolver method for only one boundary condition." << endl;
        exit(0);
    } 

    if (guess.size() != cfront.size() || guess.size() != noninit.size()) {
        cout << "\n Guess does not match boundary condition." << endl;
        exit(0);
    }

    for (int i = 0; i < guess.size(); i++) {
        if (tmax+step <= X0.T() || tmax+step <= cfront[i].second.first) {
            cout << "\n Cannot solve when tmax < tmin." << endl;
            exit(0);
        } 
    }    

    sort(noninit.begin(), noninit.end());
    vector<double> a(guess);  
    vector<int> ind;
    ind.resize(cfront.size());

    for (int i = 0; i < cfront.size(); i++) {
        ind[i] = cfront[i].first;
    }

    //Root-finding
    vector<function<double(vector<double>)>> gi(cfront.size());

    for (int i = 0; i < cfront.size(); i++) {
        gi[i] = [this, step, tmax, ind, noninit, i](vector<double> init) {
            vector<ODEpoint> c;
            init.resize(cfront.size());
            for (int j = 0; j < noninit.size(); j++) {
                X0.X()[noninit[j]] = init[j];
            }
            sol = ODEsolver::RungeKutta4Solver(step, tmax);
            return ODEsolver::Evaluate(cfront[i].second.first, "RK4")[ind[i]] - cfront[i].second.second;
        };
    }

    vector<FunctorND> func(gi.size());
    for (int i = 0; i < gi.size(); i++) {
        string s = "g" + to_string(i);
        func[i] = FunctorND(&s[0], cfront.size(), gi[i]);
    }

    RootFinderND root(func);

    root.NewtonNDNumerical(a, error);

    return sol;
}

//Draw graph of solution in [ti, tf]
void BVPsolver::Draw(double ti, double tf) {
    TApplication *app = new TApplication("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "Boundary value problem", 0, 0, 1280, 720);
    TRootCanvas *close = (TRootCanvas *)c->GetCanvasImp();
    close->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    int n = f.size();
    int nx = sqrt(n);
    int ny = sqrt(n);

    if (nx*ny < n){
        nx++;
    }
        
    if (nx*ny < n){
        ny++;
    } 
    
    if (n > 1) {
        c->Divide(nx, ny, 0.001, 0.001);
    }    

    vector<TMultiGraph*> mg;
    mg.resize(n);

    for (int i = 0; i < mg.size(); i++) {
        string num1 = to_string(i);
        string aux = "x";
        string axis_title = aux + num1 + "(t)";
        mg[i] = new TMultiGraph();
        mg[i]->SetTitle(&axis_title[0]);
    }

    TGraph *graph;

    for (int k = 0; k < n; k++) {
        if (n > 1) {
            c->cd(k+1);
        }    
        
        int num = sol.size(); 
        double_t t[num]; 
        double_t x[num];
        for (int j = 0; j < num; j++) {
            t[j] = sol[j].T();
            x[j] = sol[j].X()[k];
        }
        graph = new TGraph(num, t, x);
        graph->SetLineWidth(2);
        graph->SetMarkerSize(10);
        mg[k]->Add(graph);
        

        gStyle->SetPalette(kRainBow);
        mg[k]->GetXaxis()->SetLimits(ti, tf);
        mg[k]->GetXaxis()->SetTitle("t");
        string num1 = to_string(k);
        string aux = "x";
        string axis_title = aux + num1 + "(t)";
        mg[k]->GetYaxis()->SetTitle(&axis_title[0]);
        mg[k]->GetYaxis()->SetTitleOffset(1.3);
        mg[k]->Draw("APLC");
        
        TLegend* legend = new TLegend(.85, .85, .999, 1.);
        legend->SetFillColor(0);
        legend->AddEntry(graph, "shooting", "lpf");
        legend->Draw();
    }
  
    c->SetTitle("Boundary value problem");
    c->Modified();
    c->Update();
    c->SaveAs("bvpsolver.pdf");
    app->Run();
}

//Obtain value of solution at a point t
vector<double> BVPsolver::Evaluate(double t) {
    vector<double> a;
    a.resize(f.size());
    int o;
    
    //Determine interval [x(i), x(i+1)]
    for (int k = 0; k < sol.size(); k++) {
        if (t >= sol[k].T() && t <= sol[k+1].T()) {
            o = k;
            break;
        }
    }  
    
    //Linear interpolation
    for (int i = 0; i < a.size(); i++) {
        a[i] = (t-sol[o].T())*(sol[o+1].X()[i]-sol[o].X()[i])/(sol[o+1].T()-sol[o].T()) + sol[o].X()[i];  
    }

    return a;    
} 