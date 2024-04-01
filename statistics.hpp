#ifndef STATISTICS_HPP
#define STATISTICS_HPP

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

        // Calculate the covariance of a vector of values
        static double calculateCovariance(vector<double>& actual, vector<double> precedent, double m_act, double m_pre) {
            if (actual.size() != precedent.size()) {
                cerr << "Error: vectors have different lengths, they must be of same size";
                return 0.0;
            }
            float sum = 0;
            for (int i=0; i<actual.size(), i++) {
                sum += (actual[i] - m_act) * (precedent[i] - m_pre);
            }
            return sum / (actual.size() -1)
            
        }
};

#endif // STATISTICS_HPP