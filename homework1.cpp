#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

double sum(vector<double>);
double mean(vector<double>);
double median(vector<double>);
double range(vector<double>);
double covariance(vector<double>, vector<double>);
double correlation(vector<double>, vector<double>);


int main(int argc, char** argv){
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    //try to open file
    cout << "opening boston.csv" << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()){
        cout << "couldn't open" << endl;
        return 1;
    }
    getline(inFS, line);

    int numObservations = 0;

    while(inFS.good()){
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }
    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "Sum of rm: " << sum(rm) << endl;
    cout << "Sum of medv: " << sum(medv) << endl;

    cout << "Mean of rm: " << mean(rm) << endl;
    cout << "Mean of medv: " << mean(medv) << endl;

    cout << "Median of rm: " << median(rm) << endl;
    cout << "Median of medv: " << median(medv) << endl;

    cout << "Range of rm: " << range(rm) << endl;
    cout << "Range of medv: " << range(medv) << endl;

    cout << "Covariance: " << covariance(rm, medv) << endl;

    cout << "Corralation: " << correlation(rm, medv) << endl;
}

//find sum of numeric vector
double sum(vector<double> v){
    double sum = 0;
    for (auto& n : v)
        sum += n;
    return sum;
}

//find mean
double mean(vector<double> v){
    double s = sum(v);

    return (s/506);
}

//find median
double median(vector<double> v){
    sort(v.begin(), v.end());

    if(v.size() % 2 == 0){
        return ((v[v.size()/2 - 1] + v[v.size()/2]) / 2);
    }
    else{
        return v[v.size()/2];
    }
}

double range(vector<double> v){
    sort(v.begin(), v.end());

    return (v.at(v.size()-1) - v.at(0));
}

//covariance
double covariance(vector<double> v1, vector<double> v2){
    double xMean = mean(v1);
    double x, y;
    double yMean = mean(v2);
    double sum = 0;

    for(int i = 0; i < v1.size(); i++){
        x = v1.at(i) - xMean;
        y = v2.at(i) - yMean; 
        
        sum = sum + (x * y);
    }

    return (sum / v1.size()-1);
}

//correlation
double correlation(vector<double> v1, vector<double> v2){
    double xMean = mean(v1);
    double x, y;
    double yMean = mean(v2);
    double sum = 0, xsum = 0, ysum = 0;

    //summation((xi - mean(x)(yi - mean(y)))
    for(int i = 0; i < v1.size(); i++){
        x = v1.at(i) - xMean;
        y = v2.at(i) - yMean; 
        
        sum = sum + (x * y);
        xsum += (x*x);
        ysum += (y*y);
    }

    double denom = sqrt(xsum * ysum);

    return (sum/denom);
}