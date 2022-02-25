#include "FCrand.h"
#include <iostream>
#include <cmath>

using namespace std;

//Test main of class FCrand

int main() {
    int N = 5;
    double min = 10;
    double max = 12;

    FCrand num(time(0));

    cout << num.GetRandom() << endl;
    cout << num.GetRandom(min, max) << endl;

    cout << "\n\n";

    num.UpdateSeed(0);

    cout << num.GetRandom() << endl;
    cout << num.GetRandom(min, max) << endl;

    cout << "\n\n";

    for (int i = 0; i < N; i++) {
        cout << num.GetRandom(N)[i] << endl;
    }

    cout << "\n\n";

    for (int i = 0; i < N; i++) {
        cout << num.GetRandom(N, min, max)[i] << endl;
    }
}