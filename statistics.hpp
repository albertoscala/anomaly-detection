#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class Statistics {
    public:
        // Calculate the mean of a vector of values
        static double calculateMean(vector<double>& values) {
            double sum = accumulate(values.begin(), values.end(), 0.0);
            double mean =  sum / values.size();

            return mean;
        }

        // Calculate the variance of a vector of values
        static double calculateVariance(vector<double>& values, double mean) {
            double sumSqDiff = 0.0;
            for(double val : values) {
                double diff = val - mean;
                sumSqDiff += diff * diff;
            }

            return sumSqDiff / values.size();
        }
};  