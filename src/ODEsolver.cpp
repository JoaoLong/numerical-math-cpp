#include "ODEsolver.h"
#include <iostream>

using namespace std;

//Constructor
ODEsolver::ODEsolver(const ODEpoint& a, std::vector<std::function<double(ODEpoint)>>& fi) : X0(a), f(fi) {;}

//Copy constructor
ODEsolver::ODEsolver(const ODEsolver& A) : X0(A.X0), f(A.f) {;}

//Predictor-corrector method solver
const std::vector<ODEpoint>& ODEsolver::PredictorCorrectorSolver(double step, double tmax) { 
    if (tmax+step <= X0.T()) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }

    vector<ODEpoint> a;
    
    int N = (tmax-X0.T())/step;
    a.resize(N);
    int m = X0.X().size();

    for (int i = 0; i < N; i++) {
        a[i].X().resize(m);
    }
    
    //Initial conditions
    a[0].T() = X0.T();
    for (int i = 0; i < m; i++) {
        a[0].X()[i] = X0.X()[i];
    }    

    for (int i = 0; i < N-1; i++) {
        a[i+1].T() = step + a[i].T();
        ODEpoint next(a[i]);
        next.T() += step;
        for (int j = 0; j < m; j++) {
            next.X()[j] = a[i].X()[j] + step * f[j](a[i]);
            a[i+1].X()[j] = a[i].X()[j] + 0.5*step * (f[j](a[i]) + f[j](next));
        }
    }

    MS["predictorcorrector"] = a;
    return MS["predictorcorrector"];
}

//Euler method solver
const std::vector<ODEpoint>& ODEsolver::EulerSolver(double step, double tmax) {
    if (tmax+step <= X0.T()) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }
    vector<ODEpoint> a;
    
    int N = (tmax-X0.T())/step;
    a.resize(N);
    int m = X0.X().size();

    for (int i = 0; i < N; i++) {
        a[i].X().resize(m);
    }
    
    //Initial conditions
    a[0].T() = X0.T();
    for (int i = 0; i < m; i++) {
        a[0].X()[i] = X0.X()[i];
    }    

    for (int i = 0; i < N-1; i++) {
        a[i+1].T() = step + a[i].T();
        for (int j = 0; j < m; j++) {
            a[i+1].X()[j] = a[i].X()[j] + step*f[j](a[i]);
        }
    }

    MS["euler"] = a;
    return MS["euler"];
}

//Euler-Cromer method solver
const std::vector<ODEpoint>& ODEsolver::EulerCromerSolver(double step, double tmax) { 
    if (tmax+step <= X0.T()) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }

    vector<ODEpoint> a;
    
    int N = (tmax-X0.T())/step;
    a.resize(N);
    int m = X0.X().size();

    for (int i = 0; i < N; i++) {
        a[i].X().resize(m);
    }
    
    //Initial conditions
    a[0].T() = X0.T();
    for (int i = 0; i < m; i++) {
        a[0].X()[i] = X0.X()[i];
    }    

    for (int i = 0; i < N-1; i++) { 
        a[i+1].T() = step + a[i].T();
        ODEpoint next(a[i]);
        next.T() += step;
        for (int j = 0; j < m; j++) {
            next.X()[j] = a[i].X()[j] + step * f[j](a[i]);
            a[i+1].X()[j] = a[i].X()[j] + step * f[j](next);
        }
    }

    MS["eulercromer"] = a;
    return MS["eulercromer"];
}
 
//Runge-Kutta 2 method solver
const std::vector<ODEpoint>& ODEsolver::RungeKutta2Solver(double step, double tmax) {
    if (tmax+step <= X0.T()) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }
    vector<ODEpoint> a; 
    vector<double> K1, K2;
    
    int N = (tmax-X0.T())/step;
    int m = X0.X().size();

    a.resize(N);
    K1.resize(m);
    K2.resize(m);

    for (int i = 0; i < N; i++) {
        a[i].X().resize(m);
    }
    
    //Initial conditions
    a[0].T() = X0.T();
    for (int i = 0; i < m; i++) {
        a[0].X()[i] = X0.X()[i];
    }    

    for (int i = 0; i < N-1; i++) { 
        a[i+1].T() = step + a[i].T();
        vector<double> v_aux;
        v_aux.resize(m);

        //K1        
        for (int j = 0; j < m; j++) {
            K1[j] = step*f[j](a[i]);
            v_aux[j] = a[i].X()[j] + K1[j]*0.5;
        } 
        
        //K2
        ODEpoint aux(a[i].T() + step/2, v_aux);
        for (int j = 0; j < m; j++) {
            K2[j] = step*f[j](aux);
        }
        
        for (int j = 0; j < m; j++) {
            //Points calculation
            a[i+1].X()[j] = a[i].X()[j] + K2[j];
        } 
    }

    MS["RK2"] = a;
    return MS["RK2"];
}

//Runge-Kutta 4 method solver
const std::vector<ODEpoint>& ODEsolver::RungeKutta4Solver(double step, double tmax) {
    if (tmax+step <= X0.T()) {
        cout << "\n Cannot solve when tmax < tmin." << endl;
        exit(0);
    }
    vector<ODEpoint> a; 
    vector<double> K1, K2, K3, K4;
    
    int N = (tmax-X0.T())/step;
    int m = X0.X().size();

    a.resize(N);
    K1.resize(m);
    K2.resize(m);
    K3.resize(m);
    K4.resize(m);

    for (int i = 0; i < N; i++) {
        a[i].X().resize(m);
    }
    
    //Initial conditions
    a[0].T() = X0.T();
    for (int i = 0; i < m; i++) {
        a[0].X()[i] = X0.X()[i];
    }    

    for (int i = 0; i < N-1; i++) { 
        a[i+1].T() = step + a[i].T();
        vector<double> v_aux, v_aux2, v_aux3;
        v_aux.resize(m);
        v_aux2.resize(m);
        v_aux3.resize(m);

        //K1        
        for (int j = 0; j < m; j++) {
            K1[j] = step*f[j](a[i]);
            v_aux[j] = a[i].X()[j] + K1[j]*0.5;
        } 
        
        //K2
        ODEpoint aux(a[i].T() + step/2, v_aux);
        for (int j = 0; j < m; j++) {
            K2[j] = step*f[j](aux);
            v_aux2[j] = a[i].X()[j] + K2[j]*0.5;
        }

        //K3
        ODEpoint aux2(a[i].T() + step/2, v_aux2);
        for (int j = 0; j < m; j++) {
            K3[j] = step*f[j](aux2);  
            v_aux3[j] = a[i].X()[j] + K3[j];
        }

        //K4
        ODEpoint aux3(a[i].T() + step, v_aux3);
        for (int j = 0; j < m; j++) {
            K4[j] = step*f[j](aux3); 
        }
        
        for (int j = 0; j < m; j++) {
            //Points calculation
            a[i+1].X()[j] = a[i].X()[j] + (K1[j]+2*K2[j]+2*K3[j]+K4[j])/6;
        } 
    }

    MS["RK4"] = a;
    return MS["RK4"];
} 

//Draw graph of solution in [ti, tf], string for the key of map
void ODEsolver::Draw(std::vector<std::string> s, double ti, double tf) {
    TApplication *app = new TApplication("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "Solutions of the pendulum differential equation", 0, 0, 1280, 720);
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
        mg[i] = new TMultiGraph();
        string num1 = to_string(i);
        string aux = "x";
        string axis_title = aux + num1 + "(t)";
        mg[i]->SetTitle(&axis_title[0]);
    }

    TGraph *graph[s.size()];

    for (int k = 0; k < n; k++) {
        if (n > 1) {
            c->cd(k+1);
        }    
        for (int i = 0; i < s.size(); i++) {
            int num = MS[s[i]].size(); 
            double_t t[num];
            double_t x[num];
            for (int j = 0; j < num; j++) {
                t[j] = MS[s[i]][j].T();
                x[j] = MS[s[i]][j].X()[k];
            }
            graph[i] = new TGraph(num, t, x);
            graph[i]->SetLineWidth(2);
            graph[i]->SetMarkerSize(10);
            mg[k]->Add(graph[i]);
        }    

        gStyle->SetPalette(kRainBow);
        mg[k]->GetXaxis()->SetLimits(ti, tf);
        mg[k]->GetXaxis()->SetTitle("t");
        string num = to_string(k);
        string aux = "x";
        string axis_title = aux + num + "(t)";
        mg[k]->GetYaxis()->SetTitle(&axis_title[0]);
        mg[k]->GetYaxis()->SetTitleOffset(1.3);
        mg[k]->SetTitle("System of differential equations");
        mg[k]->Draw("APLC");
        
        TLegend* legend = new TLegend(.85, .85, .999, 1.);
        legend->SetFillColor(0);
        for (int j = 0; j < s.size(); j++) {
            legend->AddEntry(graph[j], &s[j][0], "lpf");
        }
        legend->Draw();
    }
  
    c->SetTitle("System of differential equations");
    c->Modified();
    c->Update();
    c->SaveAs("odesolver.pdf");
    app->Run();
}

//Obtain value of solution at a point t 
vector<double> ODEsolver::Evaluate(double x, string s) {
    //Determine interval [x(i), x(i+1)]
    vector<double> a;
    a.resize(f.size());
    int o;
    
    for (int k = 0; k < MS[s].size(); k++) {
        if (x >= MS[s][k].T() && x <= MS[s][k+1].T()) {
            o = k;
            break;
        }
    }  
    
    //Linear interpolation
    for (int i = 0; i < a.size(); i++) {
        a[i] = (x-MS[s][o].T())*(MS[s][o+1].X()[i]-MS[s][o].X()[i])/(MS[s][o+1].T()-MS[s][o].T()) + MS[s][o].X()[i];  
    }

    return a;    
}