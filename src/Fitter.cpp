#include "Fitter.h"

using namespace std;

//Constructor with two vectors of pair, points and errors
Fitter::Fitter(vector<pair<double,double>> p, vector<pair<double,double>> e, TF1* fi) { //Constructor
    points.resize(p.size());
    copy(p.begin(), p.end(), points.begin());

    errors.resize(e.size());
    copy(e.begin(), e.end(), errors.begin());
    f = fi;
} 

//Constructor reading from file with 2-4 columns (x, y, ex, ey)
Fitter::Fitter(string filename, TF1* fi) {
    string line;
    ifstream infile;
    double x=0, y=0, ex=0, ey=0;
    int n = 0;

    infile.open(filename); 
    if (infile.fail()) {
        cout << "File opening failed" << endl;
    }

    while (getline(infile, line)) {
        stringstream s(line);
        if (s >> x >> y >> ex >> ey) {
            points.push_back(make_pair(x, y));
            errors.push_back(make_pair(ex, ey));
        }
        n++;
    }

    infile.close();
    f = fi;
}

//Destructor
Fitter::~Fitter() {
    delete f;
}

//Setter for points
void Fitter::SetPoints(vector<pair<double,double>> p) { 
    for (int i = 0 ; i < p.size(); i++){
        points[i] = make_pair(p[i].first, p[i].second);
    }
} 

//Setter for errors
void Fitter::SetErrors(vector<pair<double,double>> e) { 
    for (int i = 0 ; i < e.size(); i++){
        errors[i] = make_pair(e[i].first, e[i].second);
    }
} 

//Getter for points
vector<pair<double,double>> Fitter::GetPoints() {
    return points;
}

//Setter for points
vector<pair<double,double>> Fitter::GetErrors() {
    return errors;
}

//Setter for function to fit
void Fitter::SetFitFunction(TF1* F1) { 
    f = F1;
} 

//Getter for function to fit
TF1* Fitter::GetFitFunction() { 
    return f;
} 

//Draw points
void Fitter::DrawPoints() { 
    TApplication app("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1","Graph of the points in class DataPoints", 100, 100, 800, 600);
    TRootCanvas *rc = (TRootCanvas *)c1->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TGraphErrors *graph = new TGraphErrors(); 
    
    for (int i = 0; i < points.size(); ++i) {
        graph->SetPoint(i, points[i].first, points[i].second);
        graph->SetPointError(i, errors[i].first, errors[i].second);
    }

    c1->SetGrid();
    graph->SetMarkerColor(kBlue);
    graph->SetLineWidth(1);
    graph->SetMarkerStyle(kFullCircle);
    graph->Draw("AP");

    c1->Update();
    c1->SaveAs("fitterpoints.pdf");
    
    app.Run();
} 

//Draw points and fitted curve
void Fitter::DrawFit() { 

    TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", "Graph of the points in class DataPoints", 0, 0, 1920, 1080);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TGraphErrors *graph1 = new TGraphErrors(points.size());

    for (int i = 0; i < points.size(); ++i) {
        graph1->SetPoint(i, points[i].first, points[i].second);
        graph1->SetPointError(i, errors[i].first, errors[i].second);
    }

    f->SetLineColor(kBlue);
    f->SetLineWidth(3);
    c1->SetGrid();
    graph1->SetMarkerStyle(kFullCircle);
    graph1->SetMarkerSize(0.5);
    graph1->SetLineWidth(1);

    //SetParameters, SetRange
    //v - verbose, q - quiet, R - range 
    graph1->Fit(f, "R");
    graph1->SetTitle("Refraction Index vs. Wavelength;Wavelength [#mu#m];Refraction Index");
    graph1->Draw("AP");

    c1->Update();
    c1->SaveAs("fitterfit.pdf");

    app1.Run();
} 

//Print points and error values
void Fitter::Print() { 
    for (int i = 0; i < points.size(); i++) {
        cout << "X = (" << points[i].first << " +/- " << errors[i].first << " ) [um]" << endl;
        cout << "Y = (" << points[i].second << " +/- " << errors[i].second << " ) [um]" << endl;
        cout << "\n\n";
    } 
} 