#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

double calculateMean(vector<double>& values) {
    double sum = accumulate(values.begin(), values.end(), 0.0);
    double mean =  sum / values.size();

    return mean;
}

double calculateVariance(vector<double>& values, double mean) {
    double sumSqDiff = 0.0;
    for(double val : values) {
        double diff = val - mean;
        sumSqDiff += diff * diff;
    }

    return sumSqDiff / values.size();
}

