//
//  main.cpp
//  Lab3_Euler
//
//  Created by MacBook on 11/4/20.
//
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define eps 0.001

const double alpha = 0.4;
const double betta = 0.01;
const double tgama = 0.3;
const double tetta = 0.0005;

double f1(vector<double> a){
    return (alpha - betta * a[1])*a[0];
}

double f2(vector<double> a){
    return (- tgama + tetta * a[0]) * a[1];
}

void write(ofstream &out, vector<double> A, double delta){
    cout << "Weeks have passed" << delta << "Hares: " << A[0] << "Foxes: " << A[1] << '\n';
    
}

double f1us(vector<double> a, double t){
    return -a[0] * a[1] + sin(t)/t;
}

double f2us(vector<double> a, double t){
    return -(a[0] * a[1]) + 2.5 * t/(1 + t * t);
}

void eulerEmlicit(vector<function<double(vector<double>)>> f, vector<double> A){
    ofstream oOut;
    oOut.open("res1.txt");
    write(oOut, A, 0);
    
    vector<double> delta(A.size());
    for(double i = 0.15; i < 52; i+=0.15){
        for(int k = 0; k < A.size(); k++ ){
            delta[k] = f[k](A);
        }
        for(int k = 0; k < A.size(); k++){
            A[k] = A[k] + (delta[k] * 0.15);
        }
        write(oOut, A, i);
    }
}

void eulerEmplicit2(vector<function<double(vector<double>, double t)>> f, vector<double> A){
    
    ofstream oOut;
    oOut.open("res2.txt");
    double t1 = 0, t2 = 1, h = 0.1;
    vector<double> delta (A.size());
    vector<vector<double>> ans(A.size(), vector<double> (A.size()));
    for(double i = t1 + h; i < t2; i += h){
        for(int k = 0; k < A.size(); k++){
            delta[k] = f[k](A, i);
        }
        for(int k = 0; k < A.size(); k++){
            A[k] = A[k] + (delta[k] * h);
        }
        for(int k = 0; k < A.size(); k++){
            oOut << A[k] << " ";
        }
        oOut << '\n';
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    vector<double> Animals = {70,50};
    vector<function<double(vector<double>)>> functions = {f1,f2};
    eulerEmlicit(functions, Animals);
    vector<double> y = {0,0};
    vector<function<double(vector<double>,double t)>> functions2 = {f1us,f2us};
    vector<vector<double>> ans(y.size(), vector<double> (y.size()));
    eulerEmplicit2(functions2, y);
    return 0;
}
