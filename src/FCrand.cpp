#include "FCrand.h"

using namespace std;

//Constructor
FCrand::FCrand(int seed) {
    gRandom = new TRandom3(0);
    gRandom->SetSeed(seed);
} 

//Destructor
FCrand::~FCrand() {
    delete gRandom;
} 

//Update seed
void FCrand::UpdateSeed(int seed) {
    gRandom->SetSeed(seed);
}

//Generate one random double between [0,1] 
double FCrand::GetRandom() {
    return gRandom->Rndm();
}

//Generate one random double between [min,max] 
double FCrand::GetRandom(double min, double max) {
    return GetRandom()*(max-min)+min;
}

//Generate one random double from distribution p(x)
double FCrand::GetRandomDistribution(double min, double max, std::function<double(double)> px) {
    std::function<double(double*, double*)> aux = [px](double* x, double* p) {
        return px(x[0]);
    };

    TF1* f = new TF1 ("f", aux, min, max, 0, 1);
    double r = f->GetRandom();
    return r;
}

//Generate N random doubles between [0,1]
double* FCrand::GetRandom(int N) {
    double *R = new double[N];
    for (int i = 0 ; i < N ; i++){
        R[i] = GetRandom();
    }
    return R;
}

//Generate N random doubles between [min,max]
double* FCrand::GetRandom(int N, double min, double max) {
    double *R = new double[N];
    for (int i = 0 ; i < N ; i++){
        R[i] = GetRandom()*(max-min)+min;
    }
    return R;  
}

//Generate N random doubles from distribution p(x)
double* FCrand::GetRandomDistribution(int N, double min, double max, std::function<double(double)> px) { 
    double* r = new double[N];
    std::function<double(double*, double*)> aux = [px](double* x, double* p) {
        return px(x[0]);
    };
    TF1* f = new TF1 ("f", aux, min, max, 0, 1);

    for (int i = 0; i < N; i++) {
        r[i] = f->GetRandom();
    }    
    return r;
} 